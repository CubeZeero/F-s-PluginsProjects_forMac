
#pragma once
#ifndef NFs_TARGET_H
#define NFs_TARGET_H

// Version header (resolved via REZ_SEARCH_PATHS)
#include "NFsVersion.h"


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
//#define FS_CATEGORY "NF's Plugins-Channel"
//#define FS_CATEGORY "NF's Plugins-Colorize"
//#define FS_CATEGORY "NF's Plugins-Draw"
//#define FS_CATEGORY "NF's Plugins-Filter"
//#define FS_CATEGORY "NF's Plugins-Noise"
//#define FS_CATEGORY "NF's Plugins-expression"
//#define FS_CATEGORY "NF's Plugins-{Legacy}"

//-----------------------------------------------------------
#define SUPPORT_SMARTFX			// Enable SmartFX and Float_Color support


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

//#define NFS_OUT_FLAGS	33556032	// Standard setting
#define NFS_OUT_FLAGS	33556036	// Always render with NON_PARAM_VARY flag for dynamic parameter changes
//#define NFS_OUT_FLAGS	1600		// 8-bit only

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
#define NFS_OUT_FLAGS2	134222921
#else
#define NFS_OUT_FLAGS2	73
#endif


//-----------------------------------------------------------------------------------
#endif
