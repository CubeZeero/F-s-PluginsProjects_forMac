//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#pragma once

#ifndef FS_TARGET_H
#define FS_TARGET_H


//-----------------------------------------------------------------------------------
// Plugin name used in the interface
#define FS_NAME			"F's LineDetection"

//-----------------------------------------------------------------------------------
// Description used for the plugin
#define FS_DESCRIPTION	"Line detection filter"

//-----------------------------------------------------------------------------------
// Plugin category (choose one)
//#define FS_CATEGORY "F's Plugins-Cell"
//#define FS_CATEGORY "F's Plugins-Channel"
//#define FS_CATEGORY "F's Plugins-Colorize"
//#define FS_CATEGORY "F's Plugins-Draw"
#define FS_CATEGORY "F's Plugins-Filter"
//#define FS_CATEGORY "F's Plugins-Noise"
//#define FS_CATEGORY "F's Plugins-expression"
//#define FS_CATEGORY "F's Plugins-{Legacy}"

//-----------------------------------------------------------------------------------
// Support SmartFX+Float_Color when enabled
#define SUPPORT_SMARTFX
//#define NO_USE_FSGRAPHICS	// Do not include FsGraphics related when enabled

//-----------------------------------------------------------------------------------
// Version information
#define MAJOR_VERSION	1
#define MINOR_VERSION	0
#define FS_MAJOR_VERSION	1
#define FS_MINOR_VERSION	0
#define FS_BUG_VERSION	    0
#define FS_STAGE_VERSION	PF_Stage_DEVELOP
#define FS_BUILD_VERSION	0

//-----------------------------------------------------------------------------------
// Version value for plugin
#define FS_VERSION	1572864

//-----------------------------------------------------------------------------------
// out_flags
/*
out_data->out_flags
	PF_OutFlag_PIX_INDEPENDENT		1	Pixel processing does not refer to neighboring pixels
	PF_OutFlag_NON_PARAM_VARY		2	Input parameters do not change during processing
	PF_OutFlag_I_DO_DIALOG			32	Dialog to set parameters
	PF_OutFlag_USE_OUTPUT_EXTENT	64	Output area is used
	PF_OutFlag_I_EXPAND_BUFFER		512	Buffer extension is used
	PF_OutFlag_I_DO_DIALOG				32
*/

//These flags will set PF_OutFlag_PIX_INDEPENDENT
#define FS_OUT_FLAGS	33556032	//Normal processing
//#define FS_OUT_FLAGS	33556036	//Enable when processing frame by frame with a key. Switch NON_PARAM_VARY during operation
//#define FS_OUT_FLAGS	1600		//For 8bit only

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
#define FS_OUT_FLAGS2	1097
#endif


//-----------------------------------------------------------------------------------
#endif
