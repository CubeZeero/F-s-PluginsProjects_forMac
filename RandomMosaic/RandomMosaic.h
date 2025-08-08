//-----------------------------------------------------------------------------------
/*
	PluginSkeleton for VS2010
*/
//-----------------------------------------------------------------------------------
#pragma once

#ifndef RandomMosaic_H
#define RandomMosaic_H


#include "Fs_Target.h"
#include "AEConfig.h"
#include "entry.h"

//#include "PrSDKAESupport.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"

#if defined(PF_AE100_PLUG_IN_VERSION)
	#include "AEFX_SuiteHelper.h"
	#define refconType void*
#else
	#include "PF_Suite_Helper.h"
	#define refconType A_long
#endif

#ifdef AE_OS_WIN
	#include <Windows.h>
#endif

#include "../FsLibrary/FsAE.h"
//#include "FsAE.h"

typedef struct ParamInfo{
	A_long		value;
	A_long		sizeMax;
	A_long		sizeMin;
	A_long		aspect;
	A_long		randomColor;
} ParamInfo;

enum {
	ID_INPUT = 0,	// default input layer 
	ID_Y,		// Vertical size
	ID_SIZEMAX,		// Mosaic size (maximum value)
	ID_SIZEMIN,		// Mosaic size (minimum value)
	ID_ASPECT,		// Mosaic aspect ratio
	ID_RANDCOLOR,	// Random color
	ID_NUM_PARAMS
};

#define STR_Y		"Vertical"
#define STR_SIZEMAX		"Size (Max)"
#define STR_SIZEMIN		"Size (Min)"
#define STR_ASPECT		"Random aspect ratio"
#define STR_RANDOMCOLOR	"Random color"



extern "C" {
DllExport
PF_Err 
EntryPointFunc (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP);
}

#endif // RandomMosaic