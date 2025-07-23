//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#pragma once
#ifndef Fs_TARGET_H
#define Fs_TARGET_H


//-----------------------------------------------------------------------------------
// Plugin name used in the interface
#define FS_NAME			"F's IroTore"

//-----------------------------------------------------------------------------------
// Description used for the plugin
#define FS_DESCRIPTION	"Color extraction by adjacent color"

//-----------------------------------------------------------------------------------
// Plugin category (choose one)
#define FS_CATEGORY "NF's Plugins-Cell"
//#define FS_CATEGORY "F's Plugins-Channel"
//#define FS_CATEGORY "F's Plugins-Colorize"
//#define FS_CATEGORY "F's Plugins-Draw"
//#define FS_CATEGORY "F's Plugins-Filter"
//#define FS_CATEGORY "F's Plugins-Noise"
//#define FS_CATEGORY "F's Plugins-expression"
//#define FS_CATEGORY "F's Plugins-{Legacy}"

//-----------------------------------------------------------
#define SUPPORT_SMARTFX			// Enable SmartFX + Float_Color support
//#define NO_USE_FSGRAPHICS	// Disable FsGraphics include if not needed

//-----------------------------------------------------------------------------------
// Version information
#define MAJOR_VERSION    1
#define MINOR_VERSION    5
#define FS_VERSION       ((MAJOR_VERSION << 20) | MINOR_VERSION)  // 1572864

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

#define FS_OUT_FLAGS	33556032	//ʏ͂
//#define FS_OUT_FLAGS	33556036	//LɂƖt[Ƃɕ`悷BNON_PARAM_VARY𓮍쒆ɐ؂ւƂ
//#define FS_OUT_FLAGS	1600		//8bit̂

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
//#define FS_OUT_FLAGS2 134222921
#define FS_OUT_FLAGS2	1097
#else
#define FS_OUT_FLAGS2 134217801
#endif


//-----------------------------------------------------------------------------------
#endif
