//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#include "sputteringAlpha.h"

//-----------------------------------------------------------------------------
static PF_Err 
ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;
	
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	UI_SEED,		//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					32000,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					144,			//�X���C�_�[�̍ő�l
					0,				//�f�t�H���g�̒l
					ID_SEED
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	UI_VALUE,		//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					100,			//�X���C�_�[�̍ő�l
					10,				//�f�t�H���g�̒l
					1,				//�\������鏬���̌���
					0,
					0,
					ID_Y
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	UI_EDGE_VALUE,	//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					200,			//�X���C�_�[�̍ő�l
					15,				//�f�t�H���g�̒l
					1,				//�\������鏬���̌���
					0,
					0,
					ID_EDGE_VALUE
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED(	UI_OPA_RND,		//�p�����[�^�̖��O
					0, 				//���l���͂���ꍇ�̍ŏ��l
					5,				//���l���͂���ꍇ�̍ő�l
					0,				//�X���C�_�[�̍ŏ��l 
					2,				//�X���C�_�[�̍ő�l
					1,				//�f�t�H���g�̒l
					2,				//�\������鏬���̌���
					0,
					0,
					ID_OPACITY_RAND
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	UI_POINT_VALUE,		//�p�����[�^�̖��O
					1, 				//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					1,				//�X���C�_�[�̍ŏ��l 
					50,			//�X���C�_�[�̍ő�l
					20,				//�f�t�H���g�̒l
					ID_POINT_VALUE
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	UI_POINT_LENGTH,		//�p�����[�^�̖��O
					1, 			//���l���͂���ꍇ�̍ŏ��l
					1000,			//���l���͂���ꍇ�̍ő�l
					5,				//�X���C�_�[�̍ŏ��l 
					200,			//�X���C�_�[�̍ő�l
					100,				//�f�t�H���g�̒l
					ID_POINT_LENGTH
					);
	//-----------------
	//�|�b�v�A�b�v
	AEFX_CLR_STRUCT(def);	
	PF_ADD_POPUP(	UI_SIZE1, 
					UI_SIZE_COUNT,	//���j���[�̐�
					UI_SIZE_DFLT,	//�f�t�H���g
					UI_SIZE2,
					ID_SIZE
					);

	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	UI_COLOR1, 
					PF_MAX_CHAN8,	// Red
					PF_MAX_CHAN8,	//Green
					PF_MAX_CHAN8,	//Blue
					ID_COLOR1
					);
	
	//-----------------
	//�g�s�b�N�\���̊J�n
	AEFX_CLR_STRUCT(def);	
	def.flags 	= 	PF_ParamFlag_START_COLLAPSED;	//
	PF_ADD_TOPIC(	UI_COLOR_TOPIC,
					ID_COLOR_TOPIC
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	UI_COLOR_MAX,		//�p�����[�^�̖��O
					1, 				//���l���͂���ꍇ�̍ŏ��l
					UI_COLOR_MAX_V,			//���l���͂���ꍇ�̍ő�l
					1,				//�X���C�_�[�̍ŏ��l 
					UI_COLOR_MAX_V,			//�X���C�_�[�̍ő�l
					20,				//�f�t�H���g�̒l
					ID_COLOR_MAX
					);

	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	UI_COLOR2, 
					PF_MAX_CHAN8,	// Red
					PF_MAX_CHAN8,	//Green
					0,	//Blue
					ID_COLOR2
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	UI_COLOR3, 
					PF_MAX_CHAN8,	// Red
					0,	//Green
					PF_MAX_CHAN8,	//Blue
					ID_COLOR3
					);
	//-----------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_COLOR(	UI_COLOR4, 
					0,	// Red
					PF_MAX_CHAN8,	//Green
					PF_MAX_CHAN8,	//Blue
					ID_COLOR4
					);
	//-----------------
	//�g�s�b�N�\���̏I���
	AEFX_CLR_STRUCT(def);
	PF_END_TOPIC(ID_COLOR_TOPIC_END);
	//-----------------
	//�`�F�b�N�{�b�N�X
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(UI_ORG1,
					UI_ORG2,
					FALSE,
					0,
					ID_ORG
					);

	//-----------------
	out_data->num_params = ID_NUM_PARAMS;

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	ERR(ae->GetADD(ID_SEED,&infoP->seed));
	ERR(ae->GetFIXED_PER2ONE(ID_Y,&infoP->value));
	ERR(ae->GetFIXED_PER2ONE(ID_EDGE_VALUE,&infoP->edge_value));
	ERR(ae->GetFIXED(ID_OPACITY_RAND,&infoP->opa));

	ERR(ae->GetADD(ID_POINT_VALUE,&infoP->point_value));
	ERR(ae->GetADD(ID_POINT_LENGTH,&infoP->point_length));
	if (!err){
		infoP->point_length = ae->downScale(infoP->point_length);
		if (infoP->point_length <2) infoP->point_length = 2;
	}

	ERR(ae->GetPOPUP(ID_SIZE,&infoP->size));
	ERR(ae->GetADD(ID_COLOR_MAX,&infoP->color_max));
	ERR(ae->GetCOLOR(ID_COLOR1,&infoP->colors[0]));
	ERR(ae->GetCOLOR(ID_COLOR2,&infoP->colors[1]));
	ERR(ae->GetCOLOR(ID_COLOR3,&infoP->colors[2]));
	ERR(ae->GetCOLOR(ID_COLOR4,&infoP->colors[3]));

	ERR(ae->GetCHECKBOX(ID_ORG,&infoP->org));

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;
	PF_InData* in_data = ae->in_data;

	if (infoP->org == TRUE) {
		ERR( ae->CopyInToOut());
	}else{
		ERR(ae->out->clear());
	}
	if ( ((infoP->value>0)&&(infoP->edge_value>0))&&(infoP->opa>0) ){
		A_long hsize1 = ae->out->width() * (ae->out->height() + 8) * sizeof(A_u_char);
		A_long hsize2 = (SPD_RAND_MAX + 8) * sizeof(A_u_char);

		A_long xx = ae->out->width();
		A_long yy = ((hsize1 + hsize2)/2) / ae->out->width() + 8;

		PF_EffectWorld bw1;
		PF_EffectWorld bw2;

		ERR(ae->NewWorld(ae->out->width(), ae->out->height()/4+8, PF_PixelFormat_ARGB32, &bw1));
		ERR(ae->NewWorld(SPD_RAND_MAX, 4, PF_PixelFormat_ARGB32, &bw2));

		/*
		PF_Handle bufH = PF_NEW_HANDLE(hsize1+ hsize2+1024);
		if (!bufH) {
			err = PF_Err_OUT_OF_MEMORY;
			return err;
		}
		PF_LOCK_HANDLE(bufH);
		*/
		//ae->LockHandle(bufH);
		/*
		CFsBuffer buf1 = ae->NewBuffer( ae->out->width() *(ae->out->height()+8)*sizeof(A_u_char));// + SPD_RAND_MAX
		if (buf1.alive()==FALSE){
			ae->out_data->out_flags |= PF_OutFlag_DISPLAY_ERROR_MESSAGE;
			err = PF_Err_INTERNAL_STRUCT_DAMAGED;
			return err;
		}
		CFsBuffer buf2 = ae->NewBuffer((SPD_RAND_MAX+8)*sizeof(A_u_char));// + 
		if (buf2.alive()==FALSE){
			buf1.Dispose();
			ae->out_data->out_flags |= PF_OutFlag_DISPLAY_ERROR_MESSAGE;
			err = PF_Err_INTERNAL_STRUCT_DAMAGED;
			return err;
		}
		buf1.Lock();
		buf2.Lock();
		infoP->buf		= buf1.bufA_u_char();
		infoP->sputRandTable = buf2.bufA_u_char();
		*/
		infoP->buf		= (A_u_char*)bw1.data;
		infoP->sputRandTable = (A_u_char*)bw2.data;
		SetupSputData(infoP->size,infoP->sputRandTable);

		switch(ae->pixelFormat())
		{
		case PF_PixelFormat_ARGB128:
			ERR(MainRender32(ae,infoP));
			break;
		case PF_PixelFormat_ARGB64:
			ERR(MainRender16(ae,infoP));
			break;
		case PF_PixelFormat_ARGB32:
			ERR(MainRender8(ae,infoP));
			break;
		}
		
		ae->DisposeWorld(&bw1);
		ae->DisposeWorld(&bw2);
		//PF_UNLOCK_HANDLE(bufH);
		//PF_DISPOSE_HANDLE(bufH);
	}

	return err;
}

//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------



#include "Fs_Entry.h"
