//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef FS_TARGET_H
#define FS_TARGET_H

//-----------------------------------------------------------------------------------
//Plugin name used in the interface
#define	FS_NAME			"F's CreateAlpha"
//-----------------------------------------------------------------------------------
//Plugin description used in the interface
#define FS_DESCRIPTION	"Unmult equivalent"

//-----------------------------------------------------------------------------------
//Category displayed in the plugin menu

//#define FS_CATEGORY "NF's Plugins-Cell"
#define FS_CATEGORY "NF's Plugins-Channel"
//#define FS_CATEGORY "NF's Plugins-Colorize"
//#define FS_CATEGORY "NF's Plugins-Draw"
//#define FS_CATEGORY "NF's Plugins-Filter"
//#define FS_CATEGORY "NF's Plugins-Noise"
//#define FS_CATEGORY "NF's Plugins-expression"
//#define FS_CATEGORY "NF's Plugins-{Legacy}"

//-----------------------------------------------------------
#define SUPPORT_SMARTFX			//Support for SmartFX+Float_Color in After Effects
//#define NO_USE_FSGRAPHICS	//Comment out FsGraphics related code in After Effects

//-----------------------------------------------------------------------------------
//#include "../FsLibrary/FsVersion.h"

//-----------------------------------------------------------------------------------
//Version definitions
#define MAJOR_VERSION	1
#define MINOR_VERSION	0
#define FS_VERSION		((MAJOR_VERSION << 16) | MINOR_VERSION)

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

#define FS_OUT_FLAGS	33556032	//Normal output
//#define FS_OUT_FLAGS	33556036	//When using After Effects, it is drawn in the preview window. NON_PARAM_VARY is returned immediately when the parameter is changed
//#define FS_OUT_FLAGS	1600		//8bit output

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
