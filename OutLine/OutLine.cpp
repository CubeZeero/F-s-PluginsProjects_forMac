//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "OutLine.h"


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
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_Y,	//�p�����[�^�̖��O
					1, 		//���l���͂���ꍇ�̍ŏ��l
					100,			//���l���͂���ꍇ�̍ő�l
					1,				//�X���C�_�[�̍ŏ��l 
					10,			//�X���C�_�[�̍ő�l
					1,				//�f�t�H���g�̒l
					ID_Y
					);

	//----------------------------------------------------------------
	//�F�̎w��
	AEFX_CLR_STRUCT(def);
	//def.flags = PF_ParamFlag_CANNOT_TIME_VARY;//���������ƃL�[�t���[�������ĂȂ��Ȃ�
	PF_ADD_COLOR(	STR_COLOR, 
					0xFF,
					0xFF,
					0xFF,
					ID_COLOR
					);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FLOAT_SLIDER(STR_LEVEL,	//Name
						0,						//VALID_MIN
						400,					//VALID_MAX
						100,					//SLIDER_MIN
						200,					//SLIDER_MAX
						1,						//CURVE_TOLERANCE
						100,					//DFLT
						1,						//PREC
						0,						//DISP
						0,						//WANT_PHASE
						ID_LEVEL
						);	
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
	PF_Err				err					= PF_Err_NONE;
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
	PF_Err 	err 	= PF_Err_NONE;
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
CopyAlphaToRed8 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;

	outP->red = inP->alpha;
	outP->green = 0;
	outP->blue = 0;
	outP->alpha = PF_MAX_CHAN8;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
CopyAlphaToRed16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;

	outP->red = inP->alpha;
	outP->green = 0;
	outP->blue = 0;
	outP->alpha = PF_MAX_CHAN16;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
CopyAlphaToRed32 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_PixelFloat	*inP, 
	PF_PixelFloat	*outP)
{
	PF_Err			err = PF_Err_NONE;

	outP->red = inP->alpha;
	outP->green = 0;
	outP->blue = 0;
	outP->alpha = 1.0;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinHor8 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_Pixel *data;
	data = (PF_Pixel *)infoP->data;

	int xmax = infoP->width -1 - infoP->value; 

	for (int y=0; y<infoP->height; y++){
		int posY = y * infoP->widthTrue;
		int minIndex = -1000;
		A_u_char minValue = 0;
		for (int x=0; x<infoP->width; x++){
			if ( (x<infoP->value)||(x>= xmax)){
				data[x + posY].green = 0;
			}else{
				int k0 = x - infoP->value;
				int k1 = x + infoP->value;
			
				if ( k0<minIndex) {
					A_u_char k1p = data[k1 + posY].red;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[k0 + posY].red;
					for (int k=k0+1; k<=k1;k++)
					{
						A_u_char kp = data[k + posY].red;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + posY].green = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinHor16 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_Pixel16 *data;
	data = (PF_Pixel16 *)infoP->data;

	int xmax = infoP->width -1 - infoP->value; 

	for (int y=0; y<infoP->height; y++){
		int posY = y * infoP->widthTrue;
		int minIndex = -1000;
		A_u_short minValue = 0;
		for (int x=0; x<infoP->width; x++){
			if ( (x<infoP->value)||(x> xmax)){
				data[x + posY].green = 0;
			}else{
				int k0 = x - infoP->value;
				int k1 = x + infoP->value;
			
				if ( k0<minIndex) {
					A_u_short k1p = data[k1 + posY].red;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[k0 + posY].red;
					for (int k=k0+1; k<=k1;k++)
					{
						A_u_short kp = data[k + posY].red;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + posY].green = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinHor32 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_PixelFloat *data;
	data = (PF_PixelFloat *)infoP->data;

	int xmax = infoP->width -1 - infoP->value; 

	for (int y=0; y<infoP->height; y++){
		int posY = y * infoP->widthTrue;
		int minIndex = -1000;
		PF_FpShort minValue = 0;
		for (int x=0; x<infoP->height; x++){
			if ( (x<infoP->value)||(x> xmax)){
				data[x + posY].green = 0;
			}else{
				int k0 = x - infoP->value;
				int k1 = x + infoP->value;
			
				if ( k0<minIndex) {
					PF_FpShort k1p = data[k1 + posY].red;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[k0 + posY].red;
					for (int k=k0+1; k<=k1;k++)
					{
						PF_FpShort kp = data[k + posY].red;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + posY].green = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinVur8 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_Pixel *data;
	data = (PF_Pixel *)infoP->data;

	int ymax = infoP->height -1 - infoP->value; 

	for (int x=0; x<infoP->width; x++){
		int minIndex = -1000;
		A_u_char minValue = 0;
		for (int y=0; y<infoP->height; y++){
			if ( (y<infoP->value)||(y>= ymax)){
				data[x + y*infoP->widthTrue].alpha = 0;
			}else{
				int k0 = y - infoP->value;
				int k1 = y + infoP->value;
			
				if ( k0<minIndex) {
					A_u_char k1p = data[x + k1*infoP->widthTrue].green;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[x + k0*infoP->widthTrue].green;
					for (int k=k0+1; k<=k1;k++)
					{
						A_u_char kp = data[x + k*infoP->widthTrue].green;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + y*infoP->widthTrue].alpha = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinVur16 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_Pixel16 *data;
	data = (PF_Pixel16 *)infoP->data;

	int ymax = infoP->height -1 - infoP->value; 

	for (int x=0; x<infoP->width; x++){
		int minIndex = -1000;
		A_u_short minValue = 0;
		for (int y=0; y<infoP->height; y++){
			if ( (y<infoP->value)||(y> ymax)){
				data[x + y*infoP->widthTrue].alpha = 0;
			}else{
				int k0 = y - infoP->value;
				int k1 = y + infoP->value;
			
				if ( k0<minIndex) {
					A_u_short k1p = data[x + k1*infoP->widthTrue].green;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[x + k0*infoP->widthTrue].green;
					for (int k=k0+1; k<=k1;k++)
					{
						A_u_short kp = data[x + k*infoP->widthTrue].green;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + y*infoP->widthTrue].alpha = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MinVur32 (MinInfo *infoP)
{
	PF_Err			err = PF_Err_NONE;
	PF_PixelFloat *data;
	data = (PF_PixelFloat *)infoP->data;

	int ymax = infoP->height -1 - infoP->value; 

	for (int x=0; x<infoP->width; x++){
		int minIndex = -1000;
		PF_FpShort minValue = 0;
		for (int y=0; y<infoP->height; y++){
			if ( (y<infoP->value)||(y> ymax)){
				data[x + y*infoP->widthTrue].alpha = 0;
			}else{
				int k0 = y - infoP->value;
				int k1 = y + infoP->value;
			
				if ( k0<minIndex) {
					PF_FpShort k1p = data[x + k1*infoP->widthTrue].green;
					if (minValue>=k1p){
						minIndex = k1;
						minValue = k1p;
					}
				}else{
					minIndex = k0;
					minValue = data[x + k0*infoP->widthTrue].green;
					for (int k=k0+1; k<=k1;k++)
					{
						PF_FpShort kp = data[x + k*infoP->widthTrue].green;
						if (minValue>=kp){
							minIndex = k;
							minValue = kp;
						}
					}
				}
				data[x + y*infoP->widthTrue].alpha = minValue;
			}

		}
	}

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MaskAlpha8 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);

	A_long v =   (A_long)inP->alpha -(A_long)outP->alpha;

	if (niP->level != 1.0){
		v = (A_long)((double)v * niP->level + 0.5);
	}
	if (v <0) v = 0;
	else if (v>PF_MAX_CHAN8) v = PF_MAX_CHAN8; 
	
	*outP = niP->color;
	outP->alpha = (A_u_char)v;
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MaskAlpha16 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);

	
	A_long v =   (A_long)inP->alpha -(A_long)outP->alpha;

	if (niP->level != 1.0){
		v = (A_long)((double)v * niP->level + 0.5);
	}
	if (v <0) v = 0;
	else if (v>PF_MAX_CHAN16) v = PF_MAX_CHAN16; 
	
	*outP = niP->color16;
	outP->alpha = (A_u_short)v;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
MaskAlpha32 (
	refconType		refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_PixelFloat	*inP, 
	PF_PixelFloat	*outP)
{
	PF_Err			err = PF_Err_NONE;
	ParamInfo *	niP		= reinterpret_cast<ParamInfo*>(refcon);

	
	double v =   (double)inP->alpha -(double)outP->alpha;

	if (niP->level != 1.0){
		v = (v * niP->level);
	}
	if (v <0) v = 0;
	else if (v>1.0) v = 1.0; 
	
	*outP = niP->color32;
	outP->alpha = (PF_FpShort)v;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;


	ERR(ae->GetADD(ID_Y,&infoP->value));
	ERR(ae->GetCOLOR(ID_COLOR,&infoP->color));
	infoP->color16 = CONV8TO16(infoP->color);
	infoP->color32 = CONV8TO32(infoP->color);
	ERR(ae->GetFLOAT(ID_LEVEL,&infoP->level));
	if (infoP->level <0) infoP->level =0;
	infoP->level /= 100.0;

	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	//��ʂ��R�s�[
	MinInfo mi;
	mi.data = ae->out->data();
	mi.width = ae->out->width();
	mi.widthTrue = ae->out->widthTrue();
	mi.height = ae->out->height();
	mi.value = infoP->value;
	
	switch(ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		ERR(ae->iterate32((refconType)infoP,CopyAlphaToRed32));
		MinHor32(&mi);
		MinVur32(&mi);
		ERR(ae->iterate32((refconType)infoP,MaskAlpha32));
		break;
	case PF_PixelFormat_ARGB64:
		ERR(ae->iterate16((refconType)infoP,CopyAlphaToRed16));
		MinHor16(&mi);
		MinVur16(&mi);
		ERR(ae->iterate16((refconType)infoP,MaskAlpha16));
		break;
	case PF_PixelFormat_ARGB32:
		ERR(ae->iterate8((refconType)infoP,CopyAlphaToRed8));
		MinHor8(&mi);
		MinVur8(&mi);
		ERR(ae->iterate8((refconType)infoP,MaskAlpha8));
		break;
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
