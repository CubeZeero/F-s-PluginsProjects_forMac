//-----------------------------------------------------------------------------------
/*
	Scanline for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef Scanline_H
#define Scanline_H

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

// Use shared FsLibrary include path via project search paths
#include "FsAE.h"

// UI parameter IDs
// Used by ParamsSetup and Render functions
enum {
	ID_INPUT = 0,	// default input layer

	ID_HEIGHT,
	ID_LEVEL0,
	ID_OPACITY0,
	ID_LEVEL1,
	ID_OPACITY1,
	ID_DIR,

	ID_NUM_PARAMS
};

// UI strings
#define STR_HEIGHT     "Line Height (px)"
#define STR_LEVEL0     "Light Lines Brightness (%)"
#define STR_OPACITY0   "Light Lines Opacity (%)"
#define STR_LEVEL1     "Dark Lines Brightness (%)"
#define STR_OPACITY1   "Dark Lines Opacity (%)"
#define STR_DIR        "Direction"
#define STR_DIRSTR     "Horizontal|Vertical"

//UI�̃p�����[�^
typedef struct ParamInfo {
	A_long		height;

	PF_FpLong	level0;
	PF_FpLong	level1;
	PF_FpLong	opacity0;
	PF_FpLong	opacity1;

	A_long		dir;

} ParamInfo, *ParamInfoP, **ParamInfoH;

//-------------------------------------------------------


//-----------------------------------------------------------------------------------
extern "C" {

DllExport 
PF_Err 
EntryPointFunc (	
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // Scanline_H
