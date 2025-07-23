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
	ID_Y,		// �m�C�Y��
	ID_SIZEMAX,		// ���U�C�N�̑傫��(�ő�l)
	ID_SIZEMIN,		// ���U�C�N�̑傫��(�ŏ��l)
	ID_ASPECT,		// ���U�C�N�̍��E
	ID_RANDCOLOR,	// �F�̂΂��
	ID_NUM_PARAMS
};

#define STR_Y		"��"
#define STR_SIZEMAX		"�T�C�Y(�ő�)"
#define STR_SIZEMIN		"�T�C�Y(�ŏ�)"
#define STR_ASPECT		"�c���̂΂��"
#define STR_RANDOMCOLOR	"���邳�̂΂��"



extern "C" {
DllExport
PF_Err 
EffectMain (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP);
}

#endif // RandomMosaic