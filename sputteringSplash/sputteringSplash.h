//-----------------------------------------------------------------------------------
/*
	PluginSkeleton for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once

#ifndef sputteringSplash_H
#define sputteringSplash_H

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
//ParamsSetup�p�̒萔
enum {
	ID_INPUT = 0,

	ID_SEED,		//�����̊
	ID_Y,		//��
	ID_DIR,		//����
	ID_OPACITY_RAND,		//��
	
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
#define UI_VALUE		"value(%)"
#define UI_DIR1			"direction"
#define UI_DIR2		"east(0)|southeast(45)|south(90)|southwest(135)|west(180)|northwest(235)|north(270)|northeast(315)"
#define UI_DIR_COUNT	8
#define UI_DIR_DFLT	1
#define UI_OPA_RND		"opacity_rand"

#define UI_POINT_VALUE	"PointValue"
#define UI_POINT_LENGTH	"PointLength"
#define UI_POINT_LEN_SYSNC1	"Point_length_sysnc"
#define UI_POINT_LEN_SYSNC2	"ON"

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


#define EDGE_BORDER8 (PF_MAX_CHAN8 * 9 /10)
#define EDGE_BORDER16 (PF_MAX_CHAN16 * 9 /10)
#define EDGE_BORDER32 (0.9)

#define TARGET_EDGE		(PF_MAX_CHAN8)
#define TARGET_SOLID	(PF_HALF_CHAN8)

typedef struct
{
	A_long		seed;
	PF_Fixed	value;
	A_long		dir;
	PF_Fixed	opa;

	A_long		point_value;
	A_long		point_length;
	A_long		size;
	A_long		color_max;
	PF_Pixel	colors[UI_COLOR_MAX_V];
	A_u_char	*sputRandTable;
	A_u_char	*buf;
	PF_Boolean	org;
} ParamInfo;


//-----------------------------------------------------------------------------
//�֐��̐錾
PF_Err MainRender8 (CFsAE *ae, ParamInfo *prm);
PF_Err MainRender16 (CFsAE *ae, ParamInfo *prm);
PF_Err MainRender32 (CFsAE *ae, ParamInfo *prm);

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

#endif // sputteringSplash_H