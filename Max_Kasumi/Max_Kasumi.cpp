//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "Max_Kasumi.h"


//-------------------------------------------------------------------------------------------------
// Place parameters in After Effects
// See Param_Utils.h for details
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;

	//----------------------------------------------------------------
	// Slider parameter
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(STR_MAX,	// parameter name
		-30, 				// slider min when negative values allowed
		30,			// slider max when negative values allowed
		-15,				// slider default min
		15,			// slider default max
		0,				// default value
		ID_MAX
	);

	//----------------------------------------------------------------
	// Popup menu
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(STR_DIR1,
		3,	// items
		1,	// default
		STR_DIR2,
		ID_DIR
	);
	//----------------------------------------------------------------
	// Popup menu
	AEFX_CLR_STRUCT(def);
	PF_ADD_POPUP(STR_CH1,
		3,	// items
		1,	// default
		STR_CH2,
		ID_CHANNEL
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
	PF_Err		err = PF_Err_NONE;

	ERR(ae->GetADD(ID_MAX, &infoP->max));
	if (!err) infoP->max = ae->downScaleNoClip(infoP->max);
	if (infoP->max < 0) {
		infoP->minus = TRUE;
		infoP->max *= -1;
	}
	else {
		infoP->minus = FALSE;
	}
	ERR(ae->GetPOPUP(ID_DIR, &infoP->dir));
	ERR(ae->GetPOPUP(ID_CHANNEL, &infoP->ch));

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	// Copy input to output
	ERR(ae->CopyInToOut());
	
	if ( infoP->max==0)
	{
		return err;
	}
	if (ae->downSaleValue() != 1) {
		return err;
	}
	switch(ae->pixelFormat())
	{
	case PF_PixelFormat_ARGB128:
		ERR(Exec32(ae, infoP));
		break;
	case PF_PixelFormat_ARGB64:
		ERR(Exec16(ae, infoP));
		break;
	case PF_PixelFormat_ARGB32:
		ERR(Exec8(ae,infoP));
		break;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
	// Main rendering for legacy host
/*
	If host does not support SmartFX (older than After Effects 7),
	this function is used for rendering (AE 6.5 compatible path).
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
	If SmartFX is supported, parameters are fetched in PreRender.
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
