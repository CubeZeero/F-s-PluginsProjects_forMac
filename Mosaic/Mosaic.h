//-----------------------------------------------------------------------------------
/*
	F's Plugins-cs4 for VS2008
*/
//-----------------------------------------------------------------------------------
#pragma once

#ifndef Mosaic_H
#define Mosaic_H

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

enum {
	ID_INPUT = 0,	// default input layer 
	ID_SIZE,		// ���U�C�N�̑傫��
	ID_POS,			//�ʒu
	ID_RAND,		//�����̃`���c�L
	ID_RAND_GRAY,		//�����̃`���c�L
	ID_FRAME_RAND_ON,
	ID_NUM_PARAMS
};

#define STR_SIZE		"Size"
#define STR_POS			"Position"
#define STR_RAND		"Random amount"
#define STR_RAND_GRAY	"Random grayscale"
#define STR_FRAME_RAND_ON	"Random per frame"
#define STR_ON			"On"

//UI�̃p�����[�^
typedef struct ParamInfo {
	A_long			size;	//���U�C�N�̑傫��
	PF_FixedPoint	pos;	//���U�C�N��
	PF_FpShort		rand;
	PF_Boolean		rand_gray;
	PF_Boolean		frameRandOn;
} ParamInfo, *ParamInfoP, **ParamInfoH;

//-----------------------------------------------------------------

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