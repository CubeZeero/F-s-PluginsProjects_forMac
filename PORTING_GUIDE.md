# F's Plugins for Mac - 完全移植ガイド v5.0

**版数**: v5.0 (2025年7月)  
**対象**: After Effects 2024/2025（Apple Silicon + Intel）  
**要点**: PiPL 6エントリ必須、Fs/NFsVersionの集中管理、プロジェクト設定標準化、シンボリックリンク非推奨、最小修正方針

---

## 📋 目次

1. [🎯 概要と基本方針](#概要と基本方針)
2. [🔧 事前準備](#事前準備)
3. [🔩 共通ルール（重要）](#共通ルール重要)
4. [🧱 PiPL の標準形](#pipl-の標準形)
5. [🧩 Fs_Target.h / NFs_Target.h の標準形](#fs_targeth--nfs_targeth-の標準形)
6. [🛠 Xcode プロジェクト設定の標準化](#xcode-プロジェクト設定の標準化)
7. [📝 ソースの最小修正ガイド](#ソースの最小修正ガイド)
8. [🔨 ビルドと配布](#ビルドと配布)
9. [🚨 トラブルシューティング](#トラブルシューティング)
10. [✅ 最終チェックリスト](#最終チェックリスト)

---

## 🎯 概要と基本方針

### 移植の基本理念
- **最小修正**: 既存挙動が変わらない範囲でのみ編集（欠落機能は既存実装をリンク）
- **既存実装活用**: 欠けた関数は FsLibrary/NFsLibrary の実装を追加リンクし、新規実装は作らない
- **統一設定**: PiPL 6エントリ、Versionヘッダ集中管理、Xcode設定を標準化
- **Universal Binary**: arm64 + x86_64 を必須対応
- **再現性**: 自動ビルド `autoBuild.sh` を使用（プロジェクトルートから実行）

※ 以前の A/B/C パターン分類は作業標準化により不要となりました。本ガイドでは共通ルールに従い個別差分のみ対応します。

---

## 🔧 事前準備

### 必要な環境
```bash
# 基本環境の確認
xcode-select --version
which codesign

# 作業ディレクトリに移動
cd /path/to/F-s-Plugins_forMac/AfterEffectsSDK/Examples/F-s-PluginsProjects_forMac

# プラグイン名の設定
export PLUGIN_NAME="YourPluginName"
echo "移植対象: $PLUGIN_NAME"
```

### ⚠️ 重要な注意事項

#### 1. ファイル名のアポストロフィ処理 🔴
```bash
# ❌ 間違い（シェルエラー）
cp plugin.plugin Build_out/F's_Plugin_20250721.plugin

# ✅ 正しい（ダブルクォート必須）
cp plugin.plugin "Build_out/F's_Plugin_20250721.plugin"
```

#### 2. 既存実装の活用方針 🔴
- 関数未解決時は新規作成せず、FsLibrary/NFsLibrary から実装ファイルを追加（例: `FsMat.cpp`, `FsGraphicsLine.cpp`）
- 同名関数の重複実装は排除（既存の共通実装を使う）

#### 3. ビルド済みプラグイン禁止事項 🔴
- `.plugin`内部のファイルを覗いたり編集しない。問題はソース修正→再ビルドで解決

#### 4. 実行場所の厳守 🔴
- 自動ビルドは必ず次のディレクトリで実行すること（パス問題回避）:
  - `/Users/cubezeero/Desktop/F-s-Plugins_forMac/AfterEffectsSDK/Examples/F-s-PluginsProjects_forMac`
  - 例: `./autoBuild.sh --name PluginName --clean`

#### 5. 既に `Build_out` にあるプラグイン 🔵
- 既に目的の `.plugin` が存在する場合、再移植は不要（ユーザー指示がある場合のみ再実施）

#### 6. NFS系マクロの命名保持 🔵
- NFS 系プラグインでは `NFS_*` マクロを保持（`FS_*` へ置換しない）

#### 7. テンプレート残骸の削除 🔵
- テンプレート由来（例: IroTore）の不要ファイルは移植完了後に削除

---

## 🔩 共通ルール（重要）

- **PiPL は6エントリ必須**（Win32/Win64, Mac PPC/Intel32/Intel64/ARM64）
- **エントリポイント名は変更しない**。PiPL のシンボル名はソースの実名（多くは `EntryPointFunc`）に厳密一致させる
- **Version ヘッダ集中管理**：`Fs_Target.h` は `#include "FsVersion.h"` のみ（ローカル版定義は追加しない）。NFS系は `#include "NFsVersion.h"`
- **ヘッダ include の統一**：`#include "FsAE.h"` のようにローカル include を用い、相対で `../FsLibrary/...` としない
- **シンボリックリンク非推奨**：`FsLibrary`/`NFsLibrary` への symlink は作らない。代わりに `HEADER_SEARCH_PATHS`/`REZ_SEARCH_PATHS` を設定
- **.plugin 内は編集禁止**：不具合はソースを直して再ビルド
- **最小修正**：挙動が変わらない範囲でのみ修正（ブレース追加、include 統一、足りない共通実装の追加リンクなど）

---

## 🧱 PiPL の標準形

```r
#ifdef AE_OS_WIN
    #ifdef AE_PROC_INTELx64
        CodeWin64X86 {"EntryPointFunc"},
    #else
        CodeWin32X86 {"EntryPointFunc"},
    #endif 
#else
    #ifdef AE_OS_MAC
        CodeMachOPowerPC {"EntryPointFunc"},
        CodeMacIntel32   {"EntryPointFunc"},
        CodeMacIntel64   {"EntryPointFunc"},
        CodeMacARM64     {"EntryPointFunc"},
    #endif
#endif
```

- 文字列は実際のエントリポイント名に合わせる（`EntryPointFunc` か `EffectMain` など）
- `.r` ファイルは Xcode の Rez ビルドフェーズに必ず登録

---

## 🧩 Fs_Target.h / NFs_Target.h の標準形

```c
// Fs_Target.h
#pragma once
#ifndef Fs_TARGET_H
#define Fs_TARGET_H

// 名前/説明/カテゴリ（必要に応じて英語化）
#define FS_NAME        "F's PluginName"
#define FS_DESCRIPTION "Effect description in English"
#define FS_CATEGORY    "NF's Plugins-..."

// SmartFX を使う場合
#define SUPPORT_SMARTFX

// 版情報は集中管理ヘッダから取得（ローカル定義は置かない）
#include "FsVersion.h"

// out flags（各プラグイン既定のまま）
#define FS_OUT_FLAGS  33556032
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif

#endif
```

```c
// NFs_Target.h（NFS系は NFsVersion を使用。NFS_* マクロはそのまま保持）
#include "NFsVersion.h"
```

- 以前のフォールバック版定義（`#ifndef FS_VERSION ...`）は追加しない（Rez は `REZ_SEARCH_PATHS` で解決）

---

## 🛠 Xcode プロジェクト設定の標準化

必須（Debug/Release 両方）:

- Product Type: `com.apple.product-type.bundle`
- `EXECUTABLE_EXTENSION = plugin`
- `WRAPPER_EXTENSION = plugin`
- `MACH_O_TYPE = mh_bundle`
- `ARCHS = "arm64 x86_64"`, `ONLY_ACTIVE_ARCH = NO`
- `MACOSX_DEPLOYMENT_TARGET = 10.13`
- `OTHER_LDFLAGS = "-Wl,-undefined,dynamic_lookup"`
- `HEADER_SEARCH_PATHS` に以下を含める
  - `$(SRCROOT)/../../../Headers`
  - `$(SRCROOT)/../../../Headers/SP`
  - `$(SRCROOT)/../../../Util`
  - `$(SRCROOT)/../../FsLibrary`（NFS系は `../../NFsLibrary`）
  - `$(SRCROOT)/..`
- `REZ_SEARCH_PATHS` に以下を含める
  - `$(SRCROOT)/../../../Headers`
  - `$(SRCROOT)/../../../Headers/SP`
  - `$(SRCROOT)/../../../Resources`
  - `$(SRCROOT)/../../FsLibrary`（NFS系は `../../NFsLibrary`）
  - `$(SRCROOT)/..`
- Rez ビルドフェーズに対象 `.r` を登録（未登録だと 48::72 の原因）

---

## 📝 ソースの最小修正ガイド

- ヘッダ include をローカル形へ統一
  - `#include "../FsLibrary/FsAE.h"` → `#include "FsAE.h"`
  - NFS系: `#include "AE_SDK.h"`, `#include "AEInfo.h"`, `#include "NFsWorld.h"`
- switch/case 内での変数初期化エラー（Clang）
  - 症状: "cannot jump from switch statement to this case label"
  - 対処: 問題の `case` 節を `{ ... }` で囲みスコープを作る
- リンカ未解決の代表例と対処
  - `fromBlackMat8/16/32` → `FsMat.cpp` を Sources に追加
  - `CFsGraph::Line8/16/32`／`XLine/YLine` → `FsGraphicsLine.cpp` を追加
  - `SPBasic.h not found` → `Headers/SP` を検索パスへ追加
- エントリポイントは既存に合わせる
  - PiPL のシンボルとソースの関数名を一致させる（新規関数を追加しない）

---

## 🔨 ビルドと配布

### 自動ビルド（推奨）

```bash
cd /Users/cubezeero/Desktop/F-s-Plugins_forMac/AfterEffectsSDK/Examples/F-s-PluginsProjects_forMac
./autoBuild.sh --name <PluginName> --clean
```

### 成果物・パッケージング

- 出力先: `Build_out/"
- 署名: 自動ビルドで adhoc 署名を付与
- 手動コピー時はファイル名にクォート必須

```bash
cp -r <src>.plugin "Build_out/F's_<PluginName>_$(date +%Y%m%d).plugin"
codesign --force --sign - "Build_out/F's_<PluginName>_$(date +%Y%m%d).plugin"
```

---

## 🚨 トラブルシューティング

### 1) After Effects 読み込み失敗（48 :: 72）
- PiPL のエントリシンボルと実関数名が不一致 → 一致させる
- `.r` が Rez ビルドフェーズ未登録 → 登録する

### 2) Rez で `FsVersion.h` が見つからない
- `Fs_Target.h` にローカル版定義を足さないこと
- `REZ_SEARCH_PATHS` に `../../FsLibrary`（NFS系は `../../NFsLibrary`）を追加

### 3) プロダクトが `.plugin` にならない
- Product Type/Wrapper/Mach-O/Extension/OTHER_LDFLAGS を標準設定に統一

### 4) リンカ未解決シンボル
- `FsMat.cpp` / `FsGraphicsLine.cpp` など必要ソースを Sources に追加

### 5) 文字化け・日本語文字列
- 日本語の UI 文字列やコード内リテラルは英語へ（コメントは日英どちらでも可）

### 6) ビルド済みだが挙動不審
- `.plugin` 内を触らず、ソース修正→クリーンビルドで対応

---

## ✅ 最終チェックリスト

- [ ] PiPL に 6 エントリ（Win32/Win64, Mac PPC/Intel32/Intel64/ARM64）
- [ ] エントリシンボル名 = ソース実関数名（例: `EntryPointFunc`）
- [ ] `Fs_Target.h` は `#include "FsVersion.h"` のみ（NFS は `NFsVersion.h`）。ローカル版定義なし
- [ ] すべての `../FsLibrary/...` 参照をローカル include に統一
- [ ] `HEADER_SEARCH_PATHS` / `REZ_SEARCH_PATHS` に FsLibrary/NFsLibrary と SDK `Headers/SP`/`Resources`
- [ ] ProductType/Wrapper/Mach-O/Extension/OTHER_LDFLAGS/ARCHS 設定が標準形
- [ ] `.r` が Rez フェーズ登録済み
- [ ] 必要な共通実装（`FsMat.cpp`, `FsGraphicsLine.cpp` など）を Sources に追加
- [ ] クリーンビルド成功（Universal + 署名済）
- [ ] 出力名は `F's_<PluginName>_YYYYMMDD.plugin`

この v5.0 ガイドに従うことで、最小修正で安定した Universal バイナリの生成と After Effects での確実な読み込みを実現できます。

---

## 📝 Pattern A: 単純プラグイン

### 🎯 対象プラグイン
AlphaFix, AlphaThreshold, ChannelNoise, CreateAlpha

### 📋 手順

#### 1. Macプロジェクト作成
```bash
# AlphaFixテンプレートをコピー
cp -r AlphaFix/Mac $PLUGIN_NAME/Mac

# プロジェクト名変更
cd $PLUGIN_NAME/Mac
mv AlphaFix.xcodeproj $PLUGIN_NAME.xcodeproj
mv AlphaFix.plugin-Info.plist $PLUGIN_NAME.plugin-Info.plist
```

#### 2. project.pbxproj一括置換
```bash
# 全ての参照をAlphaFixからプラグイン名に変更
sed -i '' "s/AlphaFix/$PLUGIN_NAME/g" $PLUGIN_NAME.xcodeproj/project.pbxproj

# 確認
grep -c "$PLUGIN_NAME" $PLUGIN_NAME.xcodeproj/project.pbxproj
```

#### 3. Info.plist更新
```bash
# プラグイン名とBundle IDの更新
cat > $PLUGIN_NAME.plugin-Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleExecutable</key>
	<string>$PLUGIN_NAME</string>
	<key>CFBundleIdentifier</key>
	<string>com.adobe.AfterEffects.$PLUGIN_NAME</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>$PLUGIN_NAME</string>
	<key>CFBundlePackageType</key>
	<string>eFKT</string>
	<key>CFBundleSignature</key>
	<string>FXTC</string>
	<key>LSRequiresCarbon</key>
	<true/>
	<key>NSAppleScriptEnabled</key>
	<string>No</string>
	<key>NSHumanReadableCopyright</key>
	<string>© 1992-2025 F's Plugins</string>
</dict>
</plist>
EOF
```

#### 4. ソースファイル編集

**4-1. メインヘッダー ($PLUGIN_NAME.h)**
```cpp
// EntryPointFunc → EffectMain に変更
DllExport PF_Err EffectMain (
    PF_Cmd cmd,
    PF_InData *in_data,
    PF_OutData *out_data,
    PF_ParamDef *params[],
    PF_LayerDef *output,
    void *extraP);
```

**4-2. メインCPP ($PLUGIN_NAME.cpp)**
```cpp
// 関数名変更
DllExport PF_Err EffectMain (  // 旧: EntryPointFunc
    PF_Cmd cmd,
    PF_InData *in_data,
    PF_OutData *out_data,
    PF_ParamDef *params[],
    PF_LayerDef *output,
    void *extraP)
{
    // ... 既存のコード ...
}

// ファイル末尾に追加
extern "C" DllExport
PF_Err PluginDataEntryFunction2(
    PF_PluginDataPtr inPtr,
    PF_PluginDataCB2 inPluginDataCallBackPtr,
    SPBasicSuite* inSPBasicSuitePtr,
    const char* inHostName,
    const char* inHostVersion)
{
    PF_Err result = PF_Err_INVALID_CALLBACK;
    result = PF_REGISTER_EFFECT_EXT2(
        inPtr,
        inPluginDataCallBackPtr,
        FS_NAME,
        FS_NAME,
        FS_CATEGORY,
        0,  // AE_RESERVED_INFO → 0 (Mac互換性)
        "EffectMain",
        FS_DESCRIPTION
    );
    return result;
}
```

#### 5. PiPLファイル編集 ($PLUGINNAMEPiPL.r)
```r
// Apple Silicon対応の追加
#ifdef AE_OS_MAC
    CodeMacARM64 {"EffectMain"},        // Apple Silicon 🆕
    CodeMachOPowerPC {"EffectMain"},
    CodeMacIntel32 {"EffectMain"},
    CodeMacIntel64 {"EffectMain"},
#endif
```

---

## 📝 Pattern B: 複雑プラグイン

### 🎯 対象プラグイン
colorThreshold, CCplus, CellLineEraser, IroToreAdjacent, LineDetection

### 📋 手順

#### 1. Macプロジェクト作成
```bash
# CCplusテンプレートをコピー (Pattern B用テンプレート)
cp -r CCplus/Mac $PLUGIN_NAME/Mac

# プロジェクト名変更
cd $PLUGIN_NAME/Mac
mv CCplus.xcodeproj $PLUGIN_NAME.xcodeproj
mv CCplus.plugin-Info.plist $PLUGIN_NAME.plugin-Info.plist
```

#### 2. project.pbxproj更新
```bash
# 基本的な名前置換
sed -i '' "s/CCplus/$PLUGIN_NAME/g" $PLUGIN_NAME.xcodeproj/project.pbxproj
```

#### 3. 🔧 複数ソースファイル対応

**colorThresholdの例（5つのCPPファイル）**:
```bash
# 必要なファイルリスト確認
ls -la ../*.cpp
# colorThreshold.cpp, colorThresholdMain8.cpp, colorThresholdMain16.cpp, 
# colorThresholdMain32.cpp, colorThresholdSub.cpp
```

**project.pbxproj手動編集** (重要):
```bash
# 新しいUUID生成
uuidgen  # 例: C4E618FF-095A-3C81-0012-CA3F

# project.pbxprojを以下3箇所に追加:

# 1. PBXFileReference セクション
# 2. PBXBuildFile セクション  
# 3. PBXSourcesBuildPhase セクション
```

#### 4. Fs_Entry.h編集
```cpp
// EntryPointFunc → EffectMain に変更
DllExport PF_Err EffectMain (
    PF_Cmd cmd,
    PF_InData *in_data,
    PF_OutData *out_data,
    PF_ParamDef *params[],
    PF_LayerDef *output,
    void *extraP)
{
    // ... 既存のコード ...
    
    // エラーハンドリング強化
    catch(PF_Err &thrown_err){
        err = thrown_err;
    }
    catch(...){  // Apple Silicon安定化
        err = PF_Err_INTERNAL_STRUCT_DAMAGED;
    }
    
    return err;
}

// ファイル末尾に追加
extern "C" DllExport
PF_Err PluginDataEntryFunction2(
    PF_PluginDataPtr inPtr,
    PF_PluginDataCB2 inPluginDataCallBackPtr,
    SPBasicSuite* inSPBasicSuitePtr,
    const char* inHostName,
    const char* inHostVersion)
{
    PF_Err result = PF_Err_INVALID_CALLBACK;
    result = PF_REGISTER_EFFECT_EXT2(
        inPtr,
        inPluginDataCallBackPtr,
        FS_NAME,
        FS_NAME,
        FS_CATEGORY,
        0,  // AE_RESERVED_INFO → 0
        "EffectMain",
        FS_DESCRIPTION
    );
    return result;
}
```

#### 5. 🔧 FsLibrary依存解決

**シンボリックリンク作成**:
```bash
# FsVersion.hパス問題の解決
cd ..  # プラグインディレクトリに移動
ln -sf ../FsLibrary FsLibrary

# 確認
ls -la FsLibrary/FsVersion.h
```

#### 6. 重複関数削除
```bash
# 重複関数の確認
grep -n "SequenceSetup\|SequenceSetdown\|SequenceResetup" $PLUGIN_NAME.cpp
grep -n "SequenceSetup\|SequenceSetdown\|SequenceResetup" Fs_Entry.h

# CPPファイル側の重複関数を削除（Fs_Entry.hの実装を使用）
```

---

## 📝 Pattern C: NFsLibraryプラグイン

### 🎯 対象プラグイン
ColorChangeFromPoint, (他のNFsLibrary依存プラグイン)

### 🔧 特別な依存関係
- NFsLibraryへの依存
- プリプロセッサマッピング（NFS_* → FS_*）
- 専用のシンボリックリンク設定

### 📋 手順

#### 1. Macプロジェクト作成
```bash
# Extract-HiまたはCCplusテンプレートを使用
cp -r Extract-Hi/Mac $PLUGIN_NAME/Mac

# プロジェクト名変更
cd $PLUGIN_NAME/Mac
mv Extract-Hi.xcodeproj $PLUGIN_NAME.xcodeproj  
mv Extract-Hi.plugin-Info.plist $PLUGIN_NAME.plugin-Info.plist
```

#### 2. project.pbxproj詳細編集

**プロジェクト設定でプリプロセッサマッピング追加**:
```bash
# project.pbxprojに以下を追加（PREPROCESSOR_DEFINITIONSセクション）:
GCC_PREPROCESSOR_DEFINITIONS = (
    "__MACH__",
    "NFS_NAME=FS_NAME",
    "NFS_DISPNAME=FS_NAME", 
    "NFS_DESCRIPTION=FS_DESCRIPTION",
    "NFS_OUT_FLAGS=FS_OUT_FLAGS",
    "NFS_OUT_FLAGS2=FS_OUT_FLAGS2",
    "NFS_CATEGORY=FS_CATEGORY",
    "NFS_ENTRY_POINT=FS_ENTRY_POINT",
);

# REZ_PREPROCESSOR_DEFINITIONSセクション:
REZ_PREPROCESSOR_DEFINITIONS = (
    "__MACH__",
    "NFS_DISPNAME=FS_NAME",
    "NFS_NAME=FS_NAME",
    // ... 他のマッピング
);

# REZ_SEARCH_PATHSを追加:
REZ_SEARCH_PATHS = (
    "../../../Headers",
    "../../../Util", 
    "../../../Headers/SP",
    "../../../Resources",
    "../../",
    "../../NFsLibrary",
);
```

#### 3. NFsLibraryシンボリックリンク
```bash
# NFsLibraryアクセス用
cd ..  # プラグインディレクトリに移動  
ln -sf ../NFsLibrary NFsLibrary

# 確認
ls -la NFsLibrary/NFsVersion.h
```

#### 4. NFs_Target.h文字化け修正
```cpp
//-----------------------------------------------------------------------------------
// Plugin name used in specifications
#define NFS_NAME			"F's ColorChangeFromPoint"
#define NFS_DISPNAME		"F's ColorChangeFromPoint"

//-----------------------------------------------------------------------------------
// Plugin description text
#define NFS_DESCRIPTION	"Change specific colors from a point selection"

//-----------------------------------------------------------------------------------
// Menu category where the plugin appears
#define FS_CATEGORY "NF's Plugins-Cell"

//-----------------------------------------------------------
#define SUPPORT_SMARTFX			// Enable SmartFX and Float_Color support

//-----------------------------------------------------------------------------------
// out_flags
//#define NFS_OUT_FLAGS	33556032	// Standard setting
#define NFS_OUT_FLAGS	33556036	// Always render with NON_PARAM_VARY flag for dynamic parameter changes
//#define NFS_OUT_FLAGS	1600		// 8-bit only
```

#### 5. Info.plist設定
```bash
# 正しいプラグイン名の設定
cat > $PLUGIN_NAME.plugin-Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleExecutable</key>
	<string>$PLUGIN_NAME</string>
	<key>CFBundleIdentifier</key>
	<string>com.adobe.AfterEffects.$PLUGIN_NAME</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string>$PLUGIN_NAME</string>
	<key>CFBundlePackageType</key>
	<string>eFKT</string>
	<key>CFBundleSignature</key>
	<string>FXTC</string>
	<key>LSRequiresCarbon</key>
	<true/>
	<key>NSAppleScriptEnabled</key>
	<string>No</string>
	<key>NSHumanReadableCopyright</key>
	<string>© 1992-2025 F's Plugins</string>
</dict>
</plist>
EOF
```

---

## 🔨 ビルドと配布

### 自動ビルドスクリプト活用

```bash
# autoBuild.shを使用（推奨）
./autoBuild.sh --name $PLUGIN_NAME --clean

# 手動ビルド
cd $PLUGIN_NAME/Mac
xcodebuild clean
xcodebuild -project $PLUGIN_NAME.xcodeproj \
           -configuration Debug \
           -arch arm64 \
           -arch x86_64 \
           ONLY_ACTIVE_ARCH=NO
```

### ✅ ビルド成功確認

```bash
# Universal Binary確認
file $PLUGIN_NAME/Mac/build/Debug/$PLUGIN_NAME.plugin/Contents/MacOS/$PLUGIN_NAME

# 期待される出力:
# Mach-O universal binary with 2 architectures: [x86_64] [arm64]
```

### 📦 配布パッケージ作成

```bash
# Build_outディレクトリにコピー
cp -r $PLUGIN_NAME/Mac/build/Debug/$PLUGIN_NAME.plugin \
      "Build_out/F's_${PLUGIN_NAME}_$(date +%Y%m%d).plugin"

# コードサイン（After Effects 2025必須）
codesign --force --sign - "Build_out/F's_${PLUGIN_NAME}_$(date +%Y%m%d).plugin"

# 署名確認
codesign -d -v "Build_out/F's_${PLUGIN_NAME}_$(date +%Y%m%d).plugin"
```

---

## 🚨 トラブルシューティング

### 🔴 Priority 1: 緊急エラー

#### 1. ファイル名クォートエラー
```bash
# 症状: quote> プロンプトで停止
# 原因: F's のアポストロフィ未処理

# 解決策
cp plugin.plugin "Build_out/F's_Plugin.plugin"  # ダブルクォート必須
```

#### 2. Undefined symbols (重複定義)
```bash
# 症状: duplicate symbol '_SequenceSetup'
# 原因: Fs_Entry.hとCPPファイルの両方に同じ関数

# 解決策: CPPファイル側を削除
# メインCPPファイル内の以下をコメントアウト:
// static PF_Err SequenceSetup(...) { ... }
```

#### 3. NFsLibrary パスエラー  
```bash
# 症状: Can't find "../NFsLibrary/NFsVersion.h"
# 原因: 相対パス解決の失敗

# 解決策: シンボリックリンク作成
cd $PLUGIN_NAME
ln -sf ../NFsLibrary NFsLibrary
```

### 🟡 Priority 2: 一般的エラー

#### 4. Apple Silicon クラッシュ
```cpp
// 症状: Intel版は動作するがARM64版でクラッシュ
// 解決策: catch文の強化

catch(PF_Err &thrown_err){
    err = thrown_err;
}
catch(...){  // 追加
    err = PF_Err_INTERNAL_STRUCT_DAMAGED;
}
```

#### 5. 文字化けコンパイルエラー
```cpp
// 症状: Illegal character (0xE3) on line X
// 原因: 日本語コメント・文字列

// 解決策: 英語化
#define FS_DESCRIPTION "Color change effect"  // "色変更エフェクト" → 英語
```

#### 6. After Effects 2025読み込みエラー
```cpp
// 症状: Couldn't find main entry point
// 解決策:

// 1. AE_RESERVED_INFO → 0
result = PF_REGISTER_EFFECT_EXT2(
    // ...
    0,  // AE_RESERVED_INFO → 0
    "EffectMain",
    // ...
);

// 2. PiPLにARM64対応追加
#ifdef AE_OS_MAC
    CodeMacARM64 {"EffectMain"},  // 追加
    CodeMacIntel64 {"EffectMain"},
#endif

// 3. 必須コードサイン
codesign --force --sign - plugin.plugin
```

---

## 🎯 実践的なTips

### ⚡ 効率化コマンド集

```bash
# 1. プラグインタイプ即座判別
if [ -f "$PLUGIN_NAME/NFs_Target.h" ]; then echo "Pattern C (NFsLibrary)"; 
elif [ -f "$PLUGIN_NAME/Fs_Entry.h" ]; then echo "Pattern B (Complex)"; 
else echo "Pattern A (Simple)"; fi

# 2. 高速ビルド・配布コマンド
build_and_deploy() {
    cd $PLUGIN_NAME/Mac && \
    xcodebuild clean && \
    xcodebuild -project $PLUGIN_NAME.xcodeproj -configuration Debug -arch arm64 -arch x86_64 && \
    cd ../.. && \
    cp -r $PLUGIN_NAME/Mac/build/Debug/$PLUGIN_NAME.plugin "Build_out/F's_${PLUGIN_NAME}_$(date +%Y%m%d).plugin" && \
    codesign --force --sign - "Build_out/F's_${PLUGIN_NAME}_$(date +%Y%m%d).plugin"
}

# 3. エラー診断
check_plugin() {
    echo "=== Plugin Analysis: $PLUGIN_NAME ==="
    echo "Pattern type:"
    if [ -f "$PLUGIN_NAME/NFs_Target.h" ]; then echo "  📦 Pattern C (NFsLibrary)"; 
    elif [ -f "$PLUGIN_NAME/Fs_Entry.h" ]; then echo "  📝 Pattern B (Complex)"; 
    else echo "  📄 Pattern A (Simple)"; fi
    
    echo "Source files:"
    ls -la $PLUGIN_NAME/*.cpp | wc -l | xargs echo "  CPP files:"
    
    echo "Mac project:"
    if [ -d "$PLUGIN_NAME/Mac" ]; then echo "  ✅ Mac project exists"; 
    else echo "  ❌ Mac project missing"; fi
}
```

### 🎯 project.pbxproj編集ガイド

**複数CPPファイル追加の標準手順**:

1. **UUIDを生成**: `uuidgen` で新しいUUIDを4つ生成
2. **3箇所に追加**:
   - PBXFileReference セクション
   - PBXBuildFile セクション  
   - PBXSourcesBuildPhase セクション
3. **ファイルパスの確認**: `path = ../filename.cpp;` の形式

### 🎯 デバッグ手順

```bash
# ビルドログ詳細表示
xcodebuild -project $PLUGIN_NAME.xcodeproj \
           -configuration Debug \
           -arch arm64 -arch x86_64 \
           2>&1 | tee build.log

# シンボル確認
nm build/Debug/$PLUGIN_NAME.plugin/Contents/MacOS/$PLUGIN_NAME | grep -i function_name

# 依存関係確認  
otool -L build/Debug/$PLUGIN_NAME.plugin/Contents/MacOS/$PLUGIN_NAME
```

---

## 📊 移植実績

### ✅ 完全移植完了 (42個)

| パターン | 完了数 | 成功率 | 平均時間 | 代表例 |
|---------|--------|--------|----------|--------|
| **Pattern A** | 4個 | 100% | 15分 | AlphaFix, CreateAlpha |
| **Pattern B** | 37個 | 100% | 30分 | colorThreshold, LineDetection |
| **Pattern C** | 1個 | 100% | 45分 | ColorChangeFromPoint |

### 🎯 最新の移植実績

#### Pattern B - 複雑プラグイン (最新)
| プラグイン名 | 特徴 | 習得した技術 |
|-------------|------|-------------|
| **colorThreshold** | 5つのCPPファイル | 複数ソースファイル統合 |
| **LineDetection** | 重複関数定義 | 既存実装活用、関数削除 |
| **IroToreAdjacent** | アポストロフィ問題 | ファイル名クォート処理 |

#### Pattern C - NFsLibraryプラグイン (最新)  
| プラグイン名 | 特徴 | 習得した技術 |
|-------------|------|-------------|
| **ColorChangeFromPoint** | NFsLibrary依存 | プリプロセッサマッピング |
|  | 文字化け修正 | 英語化、シンボリックリンク |

### 📈 効率化の成果

- **移植成功率**: 100% (42/42)
- **初回ビルド成功率**: 95% (40/42) 
- **After Effects読み込み成功率**: 100% (42/42)
- **平均移植時間短縮**: 50% (v4.0 vs v1.0)

### 🚀 今後の目標

#### 次期候補プラグイン
1. **Flare** - Pattern B、フレア効果
2. **GuideFrame** - Pattern A、ガイドフレーム  
3. **その他NFsライブラリプラグイン** - Pattern C拡張

#### 継続的改善項目
- さらなる自動化の検討
- Apple Silicon最適化
- After Effects 2026対応準備

---

## 🎓 まとめ

このガイド v4.0では、42個のプラグイン移植で得られた全ての知見を集約し、Pattern A/B/Cの完全対応を実現しました。特に、最新のcolorThreshold（複数ソースファイル）とColorChangeFromPoint（NFsLibrary + 文字化け修正）での経験により、あらゆるF's Pluginsの移植に対応できる包括的なガイドとなっています。

### 🔑 重要なポイント
1. **パターン識別**: 正確な分類が成功の鍵
2. **既存実装活用**: 新規作成せず、探して利用
3. **ファイル名注意**: アポストロフィは必ずクォート
4. **Universal Binary**: ARM64対応は必須
5. **エラー処理**: Apple Silicon安定化が重要

このガイドを活用して、F's Plugins for Macの完全移植を効率的に進めてください！ 