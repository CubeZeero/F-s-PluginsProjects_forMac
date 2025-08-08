//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once

#ifndef RgbToAlpha_H
#define RgbToAlpha_H


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
//#include "FsAE.h"


//Parameter ID definitions
//ParamsSetup function and Render function use params parameter ID
enum {
	ID_INPUT = 0,	// default input layer 
	ID_POP,
	ID_COLOR,
	ID_CB,
	ID_NUM_PARAMS
	};

#define STR_POP1	"Color Mode:"
#define STR_POP2	"White|Black|Select Color:"
#define STR_POP		3
#define STR_POP_DEF	1

#define STR_COLOR	"Select Color"
#define STR_REV1	"Invert Alpha"
#define STR_REV2	"Rev"

typedef struct ParamInfo8{
	PF_Pixel8	col;
	PF_Boolean	rev;
} ParamInfo8,*ParamInfo8P,**ParamInfo8H;

typedef struct ParamInfo16{
	PF_Pixel16	col;
	PF_Boolean	rev;
} ParamInfo16,*ParamInfo16P,**ParamInfo16H;

typedef struct ParamInfo32{
	PF_PixelFloat	col;
	PF_Boolean	rev;
} ParamInfo32,*ParamInfo32P,**ParamInfo32H;

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
#endif // RgbToAlpha_H
