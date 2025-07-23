//-----------------------------------------------------------------------------------
/*
	F's Plugins-cs4 for VS2008
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef LineDetection_H
#define LineDetection_H

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


#define STR_CB				"ON"

#define STR_DELTA_CB		"RGB�������o"
#define STR_DELTA_OPACITY	"RGB�������o�̔Z�x"

#define STR_ALPHA_CB		"Alpha�������o"
#define STR_ALPHA_OPACITY	"Alpha�������o�̔Z�x"

#define STR_LINE_COLOR		"���o�������̐F"

/*
#define STR_TOPIC			"Extra Colors"
#define STR_COLOR_OPACITY	"�J���[���o�̔Z�x"
#define STR_COLOR0_CB		"Color0_Enabled"
#define STR_COLOR0			"Color0"
#define STR_COLOR0_LEVEL	"Color0_Range"
#define STR_COLOR1_CB		"Color1_Enable"
#define STR_COLOR1			"Color1"
#define STR_COLOR1_LEVEL	"Color1_Range"
#define STR_COLOR2_CB		"Color2_Enable"
#define STR_COLOR2			"Color2"
#define STR_COLOR2_LEVEL	"Color2_Range"
#define STR_COLOR3_CB		"Color3_Enable"
#define STR_COLOR3			"Color3"
#define STR_COLOR3_LEVEL	"Color3_Range"
#define STR_COLOR4_CB		"Color4_Enable"
#define STR_COLOR4			"Color4"
#define STR_COLOR4_LEVEL	"Color4_Range"
#define STR_COLOR5_CB		"Color5_Enable"
#define STR_COLOR5			"Color5"
#define STR_COLOR5_LEVEL	"Color5_Range"
#define STR_COLOR6_CB		"Color6_Enable"
#define STR_COLOR6			"Color6"
#define STR_COLOR6_LEVEL	"Color6_Range"
#define STR_COLOR7_CB		"Color7_Enable"
#define STR_COLOR7			"Color7"
#define STR_COLOR7_LEVEL	"Color7_Range"
*/



//AfterEffects�̏����܂Ƃ߂��\����
typedef struct{
	PF_InData		*in_data;
	PF_OutData		*out_data;

	PF_EffectWorld 	*input;
	PF_EffectWorld	*output;
	PF_PixelPtr  	inData;			//���͉摜�̃A�h���X	
	PF_PixelPtr  	outData;		//�o�͉摜�̃A�h���X	
	long			width;					//�Ώۉ摜�̉���(pixel)
	long			height;					//�Ώۉ摜�̏c	��(pixel)
	
	long			inWidth;				//���͉摜�̉����̎��T�C�Ypixel)
	long			outWidth;				//�o�͉摜�̉����̎��T�C�Ypixel)
	long			offsetInWidth;	// inWidth - width	�␳�T�C�Y	
	long			offsetOutWidth;	// outWidth - width
	long			Frame;					//�`�撆�̃t���[���i�O�X�^�[�g�j
	PF_Boolean		is16Bit;		//���[�h��16Bit�Ȃ�TRUE
	unsigned char	reserve1;
	unsigned short	reserve2;
	long			reserve3;
	long			reserve4;
	/* �������64byte�ɂ���*/
} FsAEParams;

//���[�U�[�C���^�[�t�F�[�X��ID
//ParamsSetup�֐���Render�֐���params�p�����[�^��ID�ɂȂ�
enum {
	ID_INPUT = 0,	// default input layer 

	ID_DELTA_CB,
	ID_DELTA_OPACITY,

	ID_ALPHA_CB,
	ID_ALPHA_OPACITY,

	
	ID_LINE_COLOR,

	/*
	ID_TOPIC,

	ID_COLOR_OPACITY,

	ID_COLOR0_CB,
	ID_COLOR0,	//�^�[�Q�b�g�̐F
	ID_COLOR0_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR1_CB,
	ID_COLOR1,	//�^�[�Q�b�g�̐F
	ID_COLOR1_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR2_CB,
	ID_COLOR2,	//�^�[�Q�b�g�̐F
	ID_COLOR2_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR3_CB,
	ID_COLOR3,	//�^�[�Q�b�g�̐F
	ID_COLOR3_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR4_CB,
	ID_COLOR4,	//�^�[�Q�b�g�̐F
	ID_COLOR4_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR5_CB,
	ID_COLOR5,	//�^�[�Q�b�g�̐F
	ID_COLOR5_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR6_CB,
	ID_COLOR6,	//�^�[�Q�b�g�̐F
	ID_COLOR6_LEVEL,	//�^�[�Q�b�g�̐F

	ID_COLOR7_CB,
	ID_COLOR7,	//�^�[�Q�b�g�̐F
	ID_COLOR7_LEVEL,	//�^�[�Q�b�g�̐F

	ID_TOPIC_END,
	*/
	ID_NUM_PARAMS
	};

#define COLOR_COUNT 8
//�v���O�C���Ǝ��̃p�����[�^���W�߂��\����
typedef struct{
	PF_Boolean		delta_flg;
	PF_Fixed		delta_opacity;
	PF_Boolean		alpha_flg;
	PF_Fixed		alpha_opacity;
	//PF_Fixed		color_opacity;
	PF_Pixel		line_color;
	/*
	long			tbl_count;
	PF_Pixel		color_tbl[COLOR_COUNT];
	PF_Fixed		level_tbl[COLOR_COUNT];
	*/
} ParamInfo;

typedef struct {
	PF_PixelPtr		data;
	long			width;
	long			height;
	long			widthTrue;
	long			widthOffset;
	PF_FixedPoint	pos;
	PF_Fixed		opacity;
} PsetPrm; 

typedef struct {
	PF_PixelPtr		data;
	long			width;
	long			height;
	long			widthTrue;
	long			widthOffset;
	long			x;
	long			y;
	long			w;
	long			h;
} BlockPrm; 

typedef struct {
	PsetPrm			pp;
	PF_FixedPoint	start;
	PF_FixedPoint	center;
	PF_Fixed		length_i;
	PF_Fixed		length_o;
	PF_Fixed		opacity;
} LineDetectionInfo;

typedef struct {
	PF_PixelPtr		data;
	long			width;
	long			height;
	long			widthTrue;
	long			widthOffset;
	long			x;
	long			y;
	long			adr;
} PointPrm; 



//-------------------------------------------------------
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
//-------------------------------------------------------
// Create FsAEParams structure
PF_Err getFsAEParams (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	FsAEParams		*aeprm
	);
//-------------------------------------------------------
PF_Err getParams (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	ParamInfo		*prm
	);


void FindTarget8(CFsAE *ae , ParamInfo *infoP);
void FindTargetDelta8(CFsAE *ae , ParamInfo *infoP);

void FindTarget16(CFsAE *ae , ParamInfo *infoP);
void FindTargetDelta16(CFsAE *ae , ParamInfo *infoP);

void FindTarget32(CFsAE *ae , ParamInfo *infoP);
void FindTargetDelta32(CFsAE *ae , ParamInfo *infoP);


#endif // LineDetection_H
