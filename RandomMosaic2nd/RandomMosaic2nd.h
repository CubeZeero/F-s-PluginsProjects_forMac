//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------
#pragma once

#ifndef RandomMosaic2nd_H
#define RandomMosaic2nd_H


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


typedef struct ParamInfo{
	PF_Fixed	value;
	A_long		strangth;
	A_long		sizeX;
	A_long		sizeY;
} ParamInfo;

enum {
	ID_INPUT = 0,			// default input layer 
	ID_Y,				//���U�C�N�̗�(%)
	ID_STRENGTH,			//���U�C�N�̋���
	ID_SIZEX,				// ���U�C�N�̑傫��
	ID_SIZEY,				// ���U�C�N�̑傫��
	ID_NUM_PARAMS
};

#define STR_Y		"Rate(%)"
#define STR_STRENGTH	"Strength"
#define STR_SIZEX		"Width Size"
#define STR_SIZEY		"Height Size"

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



#endif // RandomMosaic2nd
