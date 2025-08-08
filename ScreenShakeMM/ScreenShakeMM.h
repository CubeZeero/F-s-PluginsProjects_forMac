//-----------------------------------------------------------------------------------
/*
	PluginSkeleton for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef ScreenShakeMM_H
#define ScreenShakeMM_H

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
#include "FsScreenShake.h"



#define	STR_MM				"Magnitude (mm)"

#define	STR_VALUE_RND		"Magnitude Random (%)"
#define	STR_DIR				"Direction (deg)"
#define	STR_DIR_RND			"Direction Random (deg)"
#define	STR_RANDOMSEED		"Random Seed"
#define	STR_EDGE_STATUS1	"Edge Handling"
#define	STR_EDGE_STATUS2	"None|Clamp|Repeat|Mirror"
#define	STR_DPI				"Resolution (dpi)"



#ifdef TEST_MODE
	#define	STR_TEST_TIME_CB1	"Time Disp"
	#define	STR_TEST_TIME_CB2	"ON"
#endif


enum {
	ID_INPUT = 0,	// default input layer 
    ID_MM,		// Magnitude
	ID_VALUE_RND,
    ID_DIR,			// Direction
    ID_DIR_RND,		// Direction random
	ID_RANDOMSEED,
	ID_EDGE_STATUS,
	ID_DPI,
	ID_NUM_PARAMS
	};


enum {
	edge_none =1,
	edge_fill,
	edge_rep,
	edge_mirror
};

// Parameters used during rendering
typedef struct{
	//PF_Fixed			dpi;
	//PF_Fixed			mm;
	PF_Fixed			value;
	A_long				value_rand;
	PF_Fixed			dir;
	PF_Fixed			dir_rand;
	A_long				randomseed;
	A_long				edge_status;

	PF_Fixed			shiftX;
	PF_Fixed			shiftY;
	getPixelPrm			gp;
} ParamInfo;



//-------------------------------------------------------

extern "C" {

DllExport	PF_Err 
EntryPointFunc (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP);

}
//-----------------------------------------------------------------------------------

#endif // ScreenShakeMM_H
