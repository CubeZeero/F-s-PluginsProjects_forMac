//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "ExpsPos.h"


//-------------------------------------------------------------------------------------------------
//Register parameters in AfterEffects
//See Param_Utils.h for reference
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_ON,
		STR_ON2,
		TRUE,
		0,
		ID_ON
	);

	//----------------------------------------------------------------
	//Position settings
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos0", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS0);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos1", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS1);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos2", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS2);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos3", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS3);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos4", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS4);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos5", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS5);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos6", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS6);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos7", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS7);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos8", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS8);
	AEFX_CLR_STRUCT(def); PF_ADD_FLOAT_SLIDERX("pos9", 0, 100, 0, 100, 0, PF_Precision_INTEGER, PF_ParamFlag_NONE, PF_ParamFlag_NONE, ID_POS9);

	//----------------------------------------------------------------
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
	PF_Err				err = PF_Err_NONE;
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
	PF_Err 	err = PF_Err_NONE;
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->GetCHECKBOX(ID_ON, &infoP->on));

	ERR(ae->GetFLOAT(ID_POS0, &infoP->pos[0]));
	ERR(ae->GetFLOAT(ID_POS1, &infoP->pos[1]));
	ERR(ae->GetFLOAT(ID_POS2, &infoP->pos[2]));
	ERR(ae->GetFLOAT(ID_POS3, &infoP->pos[3]));
	ERR(ae->GetFLOAT(ID_POS4, &infoP->pos[4]));
	ERR(ae->GetFLOAT(ID_POS5, &infoP->pos[5]));
	ERR(ae->GetFLOAT(ID_POS6, &infoP->pos[6]));
	ERR(ae->GetFLOAT(ID_POS7, &infoP->pos[7]));
	ERR(ae->GetFLOAT(ID_POS8, &infoP->pos[8]));
	ERR(ae->GetFLOAT(ID_POS9, &infoP->pos[9]));
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	//Skip if off
	if (infoP->on == TRUE) {
		ERR(ae->CopyInToOut());
	}
	else {
		ERR(ae->out->clear());
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
//�����_�����O�̃��C��
/*
	SmartFX�ɑΉ����Ă��Ȃ��z�X�g(After Effects7�ȑO�̂���)�͂��̊֐����Ăяo����ĕ`�悷��
	���̊֐��������Ă����Έꉞv6.5�Ή��ɂȂ�
*/
static PF_Err 
Render ( 
	PF_InData		*in_data,
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
