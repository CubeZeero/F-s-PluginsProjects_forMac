
//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "LineDetection.h"


//-------------------------------------------------------------------------------------------------
//AfterEffexts�Ƀp�����[�^��ʒB����
//Param_Utils.h���Q�Ƃ̂���
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_DELTA_CB,
					STR_CB,
					TRUE,
					0,
					ID_DELTA_CB
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_DELTA_OPACITY,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					500,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					300,			//�X���C�_�[�̍ő�l
					100,			//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_DELTA_OPACITY
					);
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_ALPHA_CB,
					STR_CB,
					FALSE,
					0,
					ID_ALPHA_CB
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_ALPHA_OPACITY,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					500,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					300,			//�X���C�_�[�̍ő�l
					100,			//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_ALPHA_OPACITY
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_LINE_COLOR, 
					0x0,
					0x0,
					0x0,
					ID_LINE_COLOR
					);
	/*
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);	
	def.flags 	= 	PF_ParamFlag_START_COLLAPSED;
	PF_ADD_TOPIC(STR_TOPIC, ID_TOPIC);
	//****************************************************************
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR_OPACITY,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					300,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					100,			//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR_OPACITY
					);
	//****************************************************************
	//0
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR0_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR0_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR0, 
					0x10,
					0x10,
					0x10,
					ID_COLOR0
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR0_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR0_LEVEL
					);
	//****************************************************************
	//1
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR1_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR1_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR1, 
					0xFF,
					0x0,
					0x0,
					ID_COLOR1
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR1_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR1_LEVEL
					);
	//****************************************************************
	//2
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR2_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR2_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR2, 
					0x0,
					0xFF,
					0x0,
					ID_COLOR2
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR2_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR2_LEVEL
					);
	//****************************************************************
	//3
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR3_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR3_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR3, 
					0x0,
					0x0,
					0xFF,
					ID_COLOR1
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR3_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR3_LEVEL
					);
	//****************************************************************
	//4
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR4_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR4_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR4, 
					0xFF,
					0xFF,
					0x0,
					ID_COLOR4
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR4_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR4_LEVEL
					);
	//****************************************************************
	//5
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR5_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR5_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR5, 
					0xFF,
					0x0,
					0xFF,
					ID_COLOR6
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR5_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR5_LEVEL
					);
	//****************************************************************
	//6
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR6_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR6_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR6, 
					0x0,
					0xFF,
					0xFF,
					ID_COLOR6
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR6_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR6_LEVEL
					);
	//****************************************************************
	//7
	//----------------------------------------------------------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR7_CB,
					STR_CB,
					FALSE,
					0,
					ID_COLOR7_CB
					);
	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	STR_COLOR7, 
					0xFF,
					0xFF,
					0xFF,
					ID_COLOR7
					);
	//----------------------------------------------------------------
	//�Œ菬���̃X���C�_�[�o�[
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	STR_COLOR7_LEVEL,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					1,				//���l�\���Ɋւ���t���O 
					0,
					0,
					ID_COLOR7_LEVEL
					);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_TOPIC_END);
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	*/
	out_data->num_params = 	ID_NUM_PARAMS; 

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err
HandleChangedParam(
	PF_InData					*in_data,
	PF_OutData					*out_data,
	PF_ParamDef					*params[],
	PF_LayerDef					*outputP,
	PF_UserChangedParamExtra	*extraP)
{
	PF_Err				err					= PF_Err_NONE,
						err2				= PF_Err_NONE;

	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err
QueryDynamicFlags(	
	PF_InData		*in_data,	
	PF_OutData		*out_data,	
	PF_ParamDef		*params[],	
	void			*extra)	
{
	PF_Err 	err 	= PF_Err_NONE,
			err2 	= PF_Err_NONE;
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;
	ERR(ae->GetCHECKBOX(ID_DELTA_CB,&infoP->delta_flg));
	ERR(ae->GetFIXED_PER2ONE(ID_DELTA_OPACITY,&infoP->delta_opacity));
	
	ERR(ae->GetCHECKBOX(ID_ALPHA_CB,&infoP->alpha_flg));
	ERR(ae->GetFIXED_PER2ONE(ID_ALPHA_OPACITY,&infoP->alpha_opacity));
	
	ERR(ae->GetCOLOR(ID_LINE_COLOR,&infoP->line_color));

	/*
	ERR(ae->GetFIXED_PER2ONE(ID_COLOR_OPACITY,&infoP->color_opacity));
	
	//-----------------------
	infoP->tbl_count =0;
	for (A_long i=0; i<7; i++){
		PF_Pixel c;
		PF_Fixed f;
		PF_Boolean b;
		A_long idx = ID_COLOR0_CB +i*3;
		ERR(ae->GetCHECKBOX(idx + 0,&b));
		if (!err){
			if ( b==TRUE){
				ERR(ae->GetCOLOR(idx + 1,&c));
				ERR(ae->GetFIXED_PER2ONE(idx + 2,&f));
				if ( !err){
					infoP->color_tbl[infoP->tbl_count] = c;
					infoP->level_tbl[infoP->tbl_count] = f;
					infoP->tbl_count++;
				}
			}
		}
	}
	*/
	
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	if ( (infoP->delta_flg==FALSE)&&(infoP->alpha_flg==FALSE) ){
		ERR(ae->CopyInToOut());
		return err;
	}
	switch(ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		FindTargetDelta32(ae,infoP);
		//FindTarget32(ae,infoP);
		break;
	case PF_PixelFormat_ARGB64:
		FindTargetDelta16(ae,infoP);
		//FindTarget16(ae,infoP);
		break;
	case PF_PixelFormat_ARGB32:
		FindTargetDelta8(ae,infoP);
		//FindTarget8(ae,infoP);
		break;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
//�����_�����O�̃��C��
static PF_Err Render (
	PF_InData			*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err = PF_Err_NONE;
	PF_Handle		pixelTable = NULL;
	
	CFsAE ae(in_data,out_data,params,output,ID_NUM_PARAMS);
	err =ae.resultErr();
	if (!err){
		ParamInfo info;
		ERR(GetParams(&ae,&info));
		ERR(Exec(&ae,&info));
	}
	return err;
}
//-----------------------------------------------------------------------------------
/*
	SmartFX�Ή��̏ꍇ�A�܂����̊֐����Ă΂�ăp�����[�^�̊l�����s��
*/
#if defined(SUPPORT_SMARTFX)
static PF_Err
PreRender(
	PF_InData			*in_data,
	PF_OutData			*out_data,
	PF_PreRenderExtra	*extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	CFsAE ae(in_data,out_data,extraP,sizeof(ParamInfo),ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){

		ParamInfo *infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
		if (infoP){
			ae.SetHostPreRenderData();
			ERR(GetParams(&ae,infoP));
			ERR(ae.UnSetPreRenderData());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}
#endif
//-----------------------------------------------------------------------------------
#if defined(SUPPORT_SMARTFX)
static PF_Err
SmartRender(
	PF_InData				*in_data,
	PF_OutData				*out_data,
	PF_SmartRenderExtra		*extraP)
{
	PF_Err			err		= PF_Err_NONE,
					err2 	= PF_Err_NONE;

	CFsAE ae(in_data,out_data,extraP,ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err){
		ParamInfo *infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
		if (infoP){
			ERR(Exec(&ae,infoP));
			ERR2(ae.UnsetSmartRender());
			ae.UnlockPreRenderData();
		}else{
			err = PF_Err_OUT_OF_MEMORY;
		}
	}
	return err;
}
#endif

#include "Fs_Entry.h"