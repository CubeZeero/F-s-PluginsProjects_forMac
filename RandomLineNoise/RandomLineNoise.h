//-----------------------------------------------------------------------------------
/*
	PluginSkeleton for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once

#ifndef RandomLineNoise_H
#define RandomLineNoise_H

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

// Parameter IDs for user interface
// These IDs are used in ParamsSetup and Render functions
enum {
	ID_INPUT = 0, // default input layer
	ID_Y,         // Noise Y
	ID_STRONG,    // Noise Strength (%)
	ID_LENGTH_MIN, // Minimum Noise Length
	ID_LENGTH_MAX, // Maximum Noise Length
	ID_COLOR,     // Noise Color
	ID_WEIGHT,    // Noise Weight
	ID_VERTUAL,   // Vertical flag
	ID_NUM_PARAMS // Number of parameters
};

#define STR_Y           "Noise Y"
#define STR_STRONG      "Noise Strength (%)"
#define STR_LENGTH_MIN  "Noise Length (Min)"
#define STR_LENGTH_MAX  "Noise Length (Max)"
#define STR_COLOR1      "Noise Color"
#define STR_COLOR2      "Color"
#define STR_WEIGHT      "Noise Weight"
#define STR_VERTUAL1    "Vertical"
#define STR_VERTUAL2    "V"

typedef struct ParamInfo{
	A_long      value;
	PF_Fixed    strong;
	A_long      lengthMin;
	A_long      lengthMax;
	PF_Boolean  color;
	PF_Boolean  vertualFlag;
	A_long      weight;
	A_long      x;
	A_long      y;
}ParamInfo;
typedef struct LineDrawParam{
	A_long      x0;
	A_long      x1;
	A_long      y0;
	A_long      y1;

	A_long      r;
	A_long      g;
	A_long      b;

	PF_PixelPtr data;
	A_long      width;
	A_long      widthTrue;
	A_long      height;
}LineDrawParam;
//-----------------------------------------------------------------
extern "C" {
DllExport
PF_Err 
EffectMain (
	PF_Cmd         cmd,
	PF_InData      *in_data,
	PF_OutData     *out_data,
	PF_ParamDef    *params[],
	PF_LayerDef    *output,
	void           *extraP);
}
//-------------------------------------------------------

#endif // RandomLineNoise_H
