//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef ColorChange_H
#define ColorChange_H

#include "Fs_Target.h"

#include "AE_PluginData.h"
#include "AE_GeneralPlug.h"

#include "AEConfig.h"
#include "entry.h"

/*
	For CS5 compilation, enable TARGETCS5 define.
	Exclude Supporting code from CS4only build, enable CS5only build.
	
	Change platform properties to x64.
*/


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
	#define CONVERT16TO8(A)		( (((long)(A) * PF_MAX_CHAN8) + PF_HALF_CHAN16) / PF_MAX_CHAN16)
	#define	FLOAT_2_FIX(F)			((PF_Fixed)((F) * 65536 + (((F) < 0) ? -0.5 : 0.5)))
#else
	#include "PF_Suite_Helper.h"
	#define refconType A_long
#endif

#ifdef AE_OS_WIN
	#include <Windows.h>
#endif

#include "../FsLibrary/FsAE.h"

#define ColorChangeCount 8

enum {
	ID_INPUT = 0,		// default input layer 
	ID_LEVEL,

	ID_ENABLE,

	ID_TARGET0,
	ID_SRCCOL0,
	ID_DSTCOL0,

	ID_TARGET1,
	ID_SRCCOL1,
	ID_DSTCOL1,

	ID_TARGET2,
	ID_SRCCOL2,
	ID_DSTCOL2,

	ID_TARGET3,
	ID_SRCCOL3,
	ID_DSTCOL3,

	ID_TARGET4,
	ID_SRCCOL4,
	ID_DSTCOL4,

	ID_TARGET5,
	ID_SRCCOL5,
	ID_DSTCOL5,

	ID_TARGET6,
	ID_SRCCOL6,
	ID_DSTCOL6,

	ID_TARGET7,
	ID_SRCCOL7,
	ID_DSTCOL7,

	ID_NUM_PARAMS
};


#define STR_LV		"Level"
#define STR_MODE1	"Mode"
#define STR_EXEC	"Execute"

#define STR_TARGET0	"Target0"
#define STR_SRCCOL0	"Source Color 0"
#define STR_DSTCOL0	"Destination Color 0"

#define STR_TARGET1	"Target1"
#define STR_SRCCOL1	"Source Color 1"
#define STR_DSTCOL1	"Destination Color 1"

#define STR_TARGET2	"Target2"
#define STR_SRCCOL2	"Source Color 2"
#define STR_DSTCOL2	"Destination Color 2"

#define STR_TARGET3	"Target3"
#define STR_SRCCOL3	"Source Color 3"
#define STR_DSTCOL3	"Destination Color 3"

#define STR_TARGET4	"Target4"
#define STR_SRCCOL4	"Source Color 4"
#define STR_DSTCOL4	"Destination Color 4"

#define STR_TARGET5	"Target5"
#define STR_SRCCOL5	"Source Color 5"
#define STR_DSTCOL5	"Destination Color 5"

#define STR_TARGET6	"Target6"
#define STR_SRCCOL6	"Source Color 6"
#define STR_DSTCOL6	"Destination Color 6"

#define STR_TARGET7	"Target7"
#define STR_SRCCOL7	"Source Color 7"
#define STR_DSTCOL7	"Destination Color 7"


typedef struct ParamInfo{
	PF_Boolean	enabled;
	A_u_char		Lv;
	A_long			count;
	PF_Pixel		Src[ColorChangeCount];
	PF_Pixel		Dst[ColorChangeCount];
	PF_Pixel16		Dst16[ColorChangeCount];
	PF_PixelFloat	Dst32[ColorChangeCount];
} ParamInfo,*ParamInfoP,**ParamInfoH;



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



#endif // ColorChange_H