//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#pragma once

#ifndef CCplus_H
#define CCplus_H

#include "Fs_Target.h"


#include "AEConfig.h"
#include "entry.h"
#include "AE_PluginData.h"
#include "AE_GeneralPlug.h"

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


#define COLOR_TABLE_LENGTH8		(PF_MAX_CHAN8+1)
#define COLOR_TABLE_LENGTH16	(PF_MAX_CHAN16+1)

#define COLOR_TABLE_SIZE8		((COLOR_TABLE_LENGTH8)  * sizeof(PF_Pixel))
#define COLOR_TABLE_SIZE16		((COLOR_TABLE_LENGTH16) * sizeof(PF_Pixel16))


#define	StrName					"CCplus"
#define	StrDescription			"CCplus bry-ful AfterEffects EffectPlugin"
#define	StrMADEBY				"bry-ful"

#define	StrORG_REV1				"original_reverce"	//PF_Pixel
#define	StrORG_REV2				"on"	//PF_Pixel

#define	StrCOLOR_START			"start_color"
#define	StrCOLOR_CENTER			"center_color"//PF_Pixel
#define	StrCOLOR_END			"end_color"//PF_Pixel
#define	StrCOLOR_CENTER_POS		"center_color_pos(%)"

#define	StrALPHA_START			"start_alpha(%)"	//�����ɂ���
#define	StrALPHA_END			"end_alpha(%)"//�����ɂ���

#define	StrNOISE_VALUE			"noise_value"//�m�C�Y������

#define	StrERR_getFsAEParams	"�摜�o�b�t�@�[�T�C�Y�G���[�ł��B��ƂȂ����B"
#define	StrERR_getParams		"�p�����[�^�G���[�ł��B��ƂȂ����B"




//AfterEffects�̏����܂Ƃ߂��\����
typedef struct{
	PF_InData		*in_data;
	PF_OutData		*out_data;

	PF_EffectWorld 	*input;
	PF_EffectWorld	*output;
	PF_PixelPtr  	inData;			//���͉摜�̃A�h���X	
	PF_PixelPtr  	outData;		//�o�͉摜�̃A�h���X	
	A_long			width;					//�Ώۉ摜�̉���(pixel)
	A_long			height;					//�Ώۉ摜�̏c	��(pixel)
	
	A_long			inWidth;				//���͉摜�̉����̎��T�C�Ypixel)
	A_long			outWidth;				//�o�͉摜�̉����̎��T�C�Ypixel)
	A_long			offsetInWidth;	// inWidth - width	�␳�T�C�Y	
	A_long			offsetOutWidth;	// outWidth - width
	A_long			Frame;					//�`�撆�̃t���[���i�O�X�^�[�g�j
	PF_Boolean		is16Bit;		//���[�h��16Bit�Ȃ�TRUE
	A_u_char		reserve1;
	A_u_short		reserve2;
	A_long			reserve3;
	A_long			reserve4;
	/* �������64byte�ɂ���*/
} FsAEParams;

//���[�U�[�C���^�[�t�F�[�X��ID
//ParamsSetup�֐���Render�֐���params�p�����[�^��ID�ɂȂ�
enum {
	ID_INPUT = 0,	// default input layer 

	ID_ORG_REV,		//���G�𔒍����]

	ID_COLOR_START,		//PF_Pixel
	ID_COLOR_CENTER,	//PF_Pixel
	ID_COLOR_END,		//PF_Pixel
	ID_COLOR_CENTER_POS,

	ID_ALPHA_START,		//�����ɂ���
	ID_ALPHA_END,		//�����ɂ���

	ID_NOISE_VALUE,		//�m�C�Y�̗�
	ID_NUM_PARAMS

	};
/*
//�v���O�C���Ǝ��̃p�����[�^���W�߂��\����
typedef struct{
	PF_Boolean		org_rev;
	
	PF_Pixel  		color_start;
	PF_Pixel  		color_center;
	PF_Pixel  		color_end;
	PF_Fixed		color_center_pos;

	PF_Fixed		alpha_start;
	PF_Fixed		alpha_end;

	A_long			noise_value;

	PF_PixelPtr		colorTbl;
	PF_Handle		colorTblH;
		
} ID_Params;
*/
typedef struct CCPInfo{
	PF_Boolean		org_rev;
	PF_Pixel		color_start;
	PF_Pixel		color_center;
	PF_Pixel		color_end;
	
	A_u_char		color_border;
	A_long			alpha_start;
	A_long			alpha_end;
	A_long			noise_value;
	PF_Pixel		*colorTbl;
} CCPInfo, *CCPInfoP, **CCPInfoH;

typedef struct CCPInfo16{
	PF_Boolean		org_rev;
	PF_Pixel16		color_start;
	PF_Pixel16		color_center;
	PF_Pixel16		color_end;
	
	A_u_short		color_border;
	A_long			alpha_start;
	A_long			alpha_end;
	A_long			noise_value;
	PF_Pixel16		*colorTbl;
} CCPInfo16, *CCPInfo16P, **CCPInfo16H;


typedef struct CCPInfo32{
	PF_Boolean		org_rev;
	PF_PixelFloat	color_start;
	PF_PixelFloat	color_center;
	PF_PixelFloat	color_end;
	
	PF_FpShort		color_border;

	PF_FpShort		alpha_start;
	PF_FpShort		alpha_end;
	A_long			noise_value;
	PF_PixelFloat	colorTbl;
} CCPInfo32, *CCPInfo32P, **CCPInfo32H;

typedef struct {
	PF_Fixed	value;
	PF_ProgPtr	ref;
	PF_SampPB	samp_pb;
	PF_InData	*in_data;
} CCplusInfo;



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
// FsAEParams�\���̂��쐬����
PF_Err getFsAEParams (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	FsAEParams		*aeprm
	);

#endif // CCplus_H
