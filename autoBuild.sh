#!/bin/bash

# =============================================================================
# F's Plugins Auto Build Script for Mac
# Usage: ./autoBuild.sh --name PluginName [--clean] [--no-sign] [--help]
# =============================================================================

set -e  # Exit on any error

# Default values
PLUGIN_NAME=""
CLEAN_BUILD=false
NO_SIGN=false
VERBOSE=false
BUILD_CONFIG="Debug"
DATE_SUFFIX="20250721"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show usage
show_help() {
    cat << EOF
F's Plugins Auto Build Script for Mac

USAGE:
    ./autoBuild.sh --name PLUGIN_NAME [OPTIONS]

OPTIONS:
    --name PLUGIN_NAME    Specify the plugin name to build (required)
    --clean              Clean build (removes build files and old distribution files)
    --no-sign            Skip code signing step
    --release            Build in Release configuration (default: Debug)
    --verbose            Show verbose output
    --help               Show this help message

EXAMPLES:
    ./autoBuild.sh --name AlphaFix
    ./autoBuild.sh --name IroTore --clean
    ./autoBuild.sh --name CCplus --release --no-sign
    ./autoBuild.sh --name RandomLineNoise --clean --no-sign

NOTES:
    - The script expects the plugin to have a Mac folder with an Xcode project
    - Built plugins will be copied to Build_out with naming: F's_PLUGIN_${DATE_SUFFIX}.plugin
    - Universal Binary (arm64 + x86_64) will be generated
    - Plugins will be automatically code signed unless --no-sign is specified
    - --clean removes build files and old distribution files for the specified plugin

EOF
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --name)
            PLUGIN_NAME="$2"
            shift 2
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        --no-sign)
            NO_SIGN=true
            shift
            ;;
        --release)
            BUILD_CONFIG="Release"
            shift
            ;;
        --verbose)
            VERBOSE=true
            shift
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

# Validate required arguments
if [[ -z "$PLUGIN_NAME" ]]; then
    print_error "Plugin name is required. Use --name to specify it."
    show_help
    exit 1
fi

# Set verbose output if requested
if [[ "$VERBOSE" == true ]]; then
    set -x
fi

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR"

print_info "Starting auto build for plugin: $PLUGIN_NAME"
print_info "Build configuration: $BUILD_CONFIG"
print_info "Clean build: $CLEAN_BUILD"
print_info "Code signing: $([ "$NO_SIGN" == true ] && echo "disabled" || echo "enabled")"

# Check if plugin directory exists
PLUGIN_DIR="$PROJECT_ROOT/$PLUGIN_NAME"
if [[ ! -d "$PLUGIN_DIR" ]]; then
    print_error "Plugin directory not found: $PLUGIN_DIR"
    exit 1
fi

# Check if Mac subdirectory exists
MAC_DIR="$PLUGIN_DIR/Mac"
if [[ ! -d "$MAC_DIR" ]]; then
    print_error "Mac directory not found: $MAC_DIR"
    print_warning "This plugin may not be migrated to Mac yet."
    exit 1
fi

# Check if Xcode project exists
XCODE_PROJECT="$MAC_DIR/${PLUGIN_NAME}.xcodeproj"
if [[ ! -d "$XCODE_PROJECT" ]]; then
    print_error "Xcode project not found: $XCODE_PROJECT"
    exit 1
fi

print_success "Plugin validation passed"

# Navigate to Mac directory
cd "$MAC_DIR"
print_info "Working directory: $(pwd)"

# Function to clean build files
clean_build_files() {
    local plugin_name="$1"
    print_info "Cleaning build files for $plugin_name..."
    
    # Clean Xcode build
    xcodebuild clean -project "${plugin_name}.xcodeproj" -configuration "$BUILD_CONFIG" 2>/dev/null || true
    
    # Remove build directory
    if [[ -d "build/" ]]; then
        print_info "Removing build directory..."
        rm -rf build/
        print_success "Build directory removed"
    else
        print_info "No build directory to remove"
    fi
}

# Function to clean distribution files
clean_distribution_files() {
    local plugin_name="$1"
    local build_out_dir="$2"
    
    print_info "Cleaning distribution files for $plugin_name..."
    
    # Find and remove old distribution files for this plugin
    local old_files=$(find "$build_out_dir" -name "F's_${plugin_name}_*.plugin" 2>/dev/null || true)
    
    if [[ -n "$old_files" ]]; then
        echo "$old_files" | while read -r file; do
            if [[ -d "$file" ]]; then
                print_info "Removing old distribution file: $(basename "$file")"
                rm -rf "$file"
            fi
        done
        print_success "Old distribution files removed"
    else
        print_info "No old distribution files found for $plugin_name"
    fi
}

# Prepare Build_out directory early for cleaning
BUILD_OUT_DIR="$PROJECT_ROOT/Build_out"
mkdir -p "$BUILD_OUT_DIR"

# Perform cleaning operations
if [[ "$CLEAN_BUILD" == true ]]; then
    clean_build_files "$PLUGIN_NAME"
    clean_distribution_files "$PLUGIN_NAME" "$BUILD_OUT_DIR"
    print_success "Clean completed"
fi

# Build the plugin
print_info "Building $PLUGIN_NAME (Universal Binary: arm64 + x86_64)..."
xcodebuild \
    -project "${PLUGIN_NAME}.xcodeproj" \
    -configuration "$BUILD_CONFIG" \
    -arch arm64 \
    -arch x86_64 \
    ONLY_ACTIVE_ARCH=NO

# Check if build was successful
BUILD_OUTPUT="$MAC_DIR/build/$BUILD_CONFIG/${PLUGIN_NAME}.plugin"
if [[ ! -d "$BUILD_OUTPUT" ]]; then
    print_error "Build failed: Plugin not found at $BUILD_OUTPUT"
    exit 1
fi

print_success "Build completed successfully"

# Verify Universal Binary
print_info "Verifying Universal Binary..."
BINARY_PATH="$BUILD_OUTPUT/Contents/MacOS/$PLUGIN_NAME"
if [[ -f "$BINARY_PATH" ]]; then
    file "$BINARY_PATH"
    if file "$BINARY_PATH" | grep -q "universal"; then
        print_success "Universal Binary verification passed"
    else
        print_warning "Binary may not be universal"
    fi
else
    print_warning "Binary file not found for verification"
fi

# This section is moved above to support cleaning operations

# Copy to Build_out with proper naming
OUTPUT_NAME="F's_${PLUGIN_NAME}_${DATE_SUFFIX}.plugin"
OUTPUT_PATH="$BUILD_OUT_DIR/$OUTPUT_NAME"

print_info "Copying plugin to Build_out folder..."

# Remove existing copy if it exists
if [[ -d "$OUTPUT_PATH" ]]; then
    print_warning "Removing existing plugin: $OUTPUT_NAME"
    rm -rf "$OUTPUT_PATH"
fi

# Copy the plugin
cp -r "$BUILD_OUTPUT" "$OUTPUT_PATH"

if [[ ! -d "$OUTPUT_PATH" ]]; then
    print_error "Copy failed: Plugin not found at $OUTPUT_PATH"
    exit 1
fi

print_success "Plugin copied to: $OUTPUT_NAME"

# Code signing
if [[ "$NO_SIGN" != true ]]; then
    print_info "Applying code signature..."
    codesign --force --deep --sign - "$OUTPUT_PATH"
    
    # Verify signature
    print_info "Verifying code signature..."
    codesign -d -v "$OUTPUT_PATH" 2>&1 | head -5
    print_success "Code signing completed"
else
    print_warning "Code signing skipped"
fi

# Final verification
print_info "Final plugin information:"
echo "  Name: $OUTPUT_NAME"
echo "  Path: $OUTPUT_PATH"
echo "  Size: $(du -sh "$OUTPUT_PATH" | cut -f1)"

# Build summary
print_success "Auto build completed successfully!"
echo
echo "=== BUILD SUMMARY ==="
echo "Plugin Name:     $PLUGIN_NAME"
echo "Configuration:   $BUILD_CONFIG"
echo "Output:          $OUTPUT_NAME"
echo "Location:        Build_out/"
echo "Universal:       arm64 + x86_64"
echo "Signed:          $([ "$NO_SIGN" == true ] && echo "No" || echo "Yes")"
echo "===================="
echo

# Optional: Show installation instruction
print_info "To install this plugin:"
echo "  1. Copy '$OUTPUT_NAME' to your After Effects Plug-ins folder"
echo "  2. Restart After Effects"
echo "  3. Look for 'F's $PLUGIN_NAME' in the Effects menu" 