//-----------------------------------------------------------------------------------
/*
	PluginSkeleton for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef sputteringRect_H
#define sputteringRect_H
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
#include "FsAE.h"
#include "../FsLibrary/FsSputtering.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//ParamsSetup�p�̒萔
enum {
	ID_INPUT = 0,

	ID_SEED,		//�����̊
	ID_Y,		//��
	ID_OPACITY_RAND,		//��

	ID_TOPLEFT,		//�͈�
	ID_BOTTOMRIGHT,		

	ID_POINT_VALUE,	//���̕`��őł_�̐�
	ID_POINT_LENGTH,	//�_�̋���


	ID_SIZE,

	ID_COLOR1,
	ID_COLOR_TOPIC,
	ID_COLOR_MAX,
	ID_COLOR2,
	ID_COLOR3,
	ID_COLOR4,
	ID_COLOR_TOPIC_END,

	ID_ORG,

	ID_NUM_PARAMS
};
//-----------------------------------------------------------------------------
//�p�����[�^UI�p�̕�����
#define UI_SEED			"seed"
#define UI_VALUE		"value"
#define UI_OPA_RND		"opacity_rand"

#define UI_TOPLEFT		"TopLeft"
#define UI_BOTTOMRIGHT	"BottomRight"

#define UI_POINT_VALUE	"PointValue"
#define UI_POINT_LENGTH	"PointLength"

#define UI_SIZE1		"size"
#define UI_SIZE2		"very_small|small|medium|large|very_large"
#define UI_SIZE_COUNT	5
#define UI_SIZE_DFLT	2

#define UI_COLOR1		"Color1"
#define UI_COLOR_TOPIC	"ExtraColors"
#define UI_COLOR_MAX	"ColorMax"
#define UI_COLOR_MAX_V	4
#define UI_COLOR2		"Color2"
#define UI_COLOR3		"Color3"
#define UI_COLOR4		"Color4"

#define UI_ORG1			"Blend with original"
#define UI_ORG2			"ON"


//-----------------------------------------------------------------------------

typedef struct
{
	A_long		seed;
	A_long		value;
	PF_Fixed	opa;
	A_Rect		rect;
	A_long		point_value;
	A_long		point_length;
	A_long		size;
	A_long		color_max;
	PF_Pixel	colors[UI_COLOR_MAX_V];
	A_u_char	*sputRandTable;
	PF_Boolean	org;
} ParamInfo;


//-----------------------------------------------------------------------------
//�֐��̐錾
PF_Err MainRender8 (CFsAE *ae, ParamInfo *infoP);
PF_Err MainRender16 (CFsAE *ae, ParamInfo *infoP);
PF_Err MainRender32 (CFsAE *ae, ParamInfo *infoP);

//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

#endif // sputteringRect_H