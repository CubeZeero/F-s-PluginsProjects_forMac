//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#pragma once
#ifndef Fs_TARGET_H
#define Fs_TARGET_H


//-----------------------------------------------------------------------------------
//Plugin name used in After Effects
#define FS_NAME			"F's NoiseHiLo_Alpha"

//-----------------------------------------------------------------------------------
//Plugin description used in After Effects
#define FS_DESCRIPTION	"Add noise to alpha channel with high/low threshold"

//-----------------------------------------------------------------------------------
//Category displayed in After Effects

//#define FS_CATEGORY "NF's Plugins-Cell"
//#define FS_CATEGORY "NF's Plugins-Channel"
//#define FS_CATEGORY "NF's Plugins-Colorize"
//#define FS_CATEGORY "NF's Plugins-Draw"
//#define FS_CATEGORY "NF's Plugins-Filter"
//#define FS_CATEGORY "NF's Plugins-Noise"
//#define FS_CATEGORY "NF's Plugins-expression"
#define FS_CATEGORY "NF's Plugins-{Legacy}"

//-----------------------------------------------------------
#define SUPPORT_SMARTFX			//Support for SmartFX+Float_Color in After Effects
//#define NO_USE_FSGRAPHICS	//Disable FsGraphics related code in After Effects

//-----------------------------------------------------------------------------------
// Version settings
#define FS_VERSION	1572864
#define MAJOR_VERSION	1
#define MINOR_VERSION	0


//-----------------------------------------------------------------------------------
//out_flags
/*
out_data->out_flags
	PF_OutFlag_PIX_INDEPENDENT		1024
	PF_OutFlag_NON_PARAM_VARY			4
	PF_OutFlag_DEEP_COLOR_AWARE		33554432
	PF_OutFlag_USE_OUTPUT_EXTENT	64
	PF_OutFlag_I_EXPAND_BUFFER		512
	PF_OutFlag_I_DO_DIALOG				32
*/

//#define FS_OUT_FLAGS	33556032	//Normal setting
#define FS_OUT_FLAGS	33556036	//When used in After Effects, it draws in non-parametric mode. NON_PARAM_VARY is set to true for compatibility
//#define FS_OUT_FLAGS	1600		//8bit setting

//-----------------------------------------------------------------------------------
//out_flags2
/*
out_data->out_flags2
	PF_OutFlag2_FLOAT_COLOR_AWARE
	PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG
	PF_OutFlag2_SUPPORTS_SMART_RENDER
	PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS
	PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS;
*/
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif


//-----------------------------------------------------------------------------------
#endif
