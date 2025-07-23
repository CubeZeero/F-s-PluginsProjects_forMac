//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010 and VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef FS_TAGET_H
#define FS_TAGET_H

#define FS_NAME			"F's AlphaFix"
#define FS_DESCRIPTION	"Restores transparency values."

//-----------------------------------------------------------------------------------
// Menu category where the plugin will be displayed

//#define FS_CATEGORY "NF's Plugins-Cell"
#define FS_CATEGORY "NF's Plugins-Channel"
//#define FS_CATEGORY "NF's Plugins-Colorize"
//#define FS_CATEGORY "NF's Plugins-Draw"
//#define FS_CATEGORY "NF's Plugins-Filter"
//#define FS_CATEGORY "NF's Plugins-Noise"
//#define FS_CATEGORY "NF's Plugins-expression"
//#define FS_CATEGORY "NF's Plugins-{Legacy}"


//-----------------------------------------------------------
#ifndef SUPPORT_SMARTFX			// Prevent double registration
#define SUPPORT_SMARTFX			// Enable this to support SmartFX+Float_Color
#endif
//#define NO_USE_FSGRAPHICS	// Enable this to not include FsGraphics related code


//-----------------------------------------------------------------------------------
//out_flags
/*
	out_data->out_flags	  =	
		PF_OutFlag_PIX_INDEPENDENT
		//| PF_OutFlag_NON_PARAM_VARY	
		| PF_OutFlag_DEEP_COLOR_AWARE
		| PF_OutFlag_USE_OUTPUT_EXTENT
		| PF_OutFlag_I_EXPAND_BUFFER;
		//33556032	
		//33556036 +PF_OutFlag_NON_PARAM_VARY
*/
#define FS_OUT_FLAGS 33556032
//#define Fs_OUTFLAGS 33556036

//-----------------------------------------------------------------------------------
//out_flags2
/*
	out_data->out_flags2  =	PF_OutFlag2_FLOAT_COLOR_AWARE
						  | PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG
						  | PF_OutFlag2_SUPPORTS_SMART_RENDER
						  | PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS
						  | PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS
						  | PF_OutFlag2_SUPPORTS_THREADED_RENDERING;		// PF_Cmd_GLOBAL_SETUP

						//5193
						//134222921
*/
#if defined(SUPPORT_SMARTFX)
//#define FS_OUT_FLAGS2 134222921
#define FS_OUT_FLAGS2	134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif

//-----------------------------------------------------------------------------------
// Version definitions (from FsVersion.h to avoid Rez compile issues)
#define	MAJOR_VERSION		3
#define	MINOR_VERSION		0
#define	BUG_VERSION			0
#define	STAGE_VERSION		PF_Stage_RELEASE
#define	BUILD_VERSION		0
#define FS_VERSION	1572864
//-----------------------------------------------------------------------------------

#endif
