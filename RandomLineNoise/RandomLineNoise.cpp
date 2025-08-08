//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------


#include "RandomLineNoise.h"



//-----------------------------------------------------------------------------------
static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.About(in_data,out_data,params,output);
	return err;
}
//-----------------------------------------------------------------------------------
static PF_Err 
GlobalSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.GlobalSetup(in_data,out_data,params,output);
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GlobalSetdown(
	PF_InData	*in_data)
{
	PF_Err	err				= PF_Err_NONE;
	CFsAE ae;
	err = ae.GlobalSetdown(in_data);
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{

	return PF_Err_NONE;
}
//-------------------------------------------------------------------------------------------------
static PF_Err SequenceSetdown (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	return PF_Err_NONE;
}


//-------------------------------------------------------------------------------------------------
static PF_Err SequenceResetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	return PF_Err_NONE;
}

//-------------------------------------------------------------------------------------------------
// Pass parameters to After Effects
// Reference to Param_Utils.h
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;

	//----------------------------------------------------------------
	// First parameter
	// Default slider value
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER( STR_Y, // Parameter name
				0, // Minimum value if not specified
				10000, // Maximum value if not specified
				0, // Slider minimum value
				1000, // Slider maximum value
				100, // Default value
				ID_Y
				);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_FIXED( STR_STRONG, // Parameter name
				0, // Minimum value if not specified
				100, // Maximum value if not specified
				0, // Slider minimum value
				50, // Slider maximum value
				10, // Default value
				1, // Flag for display
				0,
				0,
				ID_STRONG
				);
	//----------------------------------------------------------------
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER( STR_LENGTH_MIN, // Parameter name
				0, // Minimum value if not specified
				1024, // Maximum value if not specified
				0, // Slider minimum value
				100, // Slider maximum value
				10, // Default value
				ID_LENGTH_MIN
				);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER( STR_LENGTH_MAX, // Parameter name
				0, // Minimum value if not specified
				1024, // Maximum value if not specified
				0, // Slider minimum value
				100, // Slider maximum value
				30, // Default value
				ID_LENGTH_MAX
				);
	//----------------------------------------------------------------
	// Additional parameters
	// Checkbox
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_COLOR1,
				STR_COLOR2,
				FALSE,
				0,
				ID_COLOR
				);
	//----------------------------------------------------------------
	// Additional parameters
	// Checkbox
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER( STR_WEIGHT, // Parameter name
				1, // Minimum value if not specified
				16, // Maximum value if not specified
				1, // Slider minimum value
				4, // Slider maximum value
				2, // Default value
				ID_WEIGHT
				);
	//----------------------------------------------------------------
	// Additional parameters
	// Checkbox
	AEFX_CLR_STRUCT(def);
	PF_ADD_CHECKBOX(STR_VERTUAL1,
				STR_VERTUAL2,
				FALSE,
				0,
				ID_VERTUAL
				);
	//----------------------------------------------------------------
	out_data->num_params =  ID_NUM_PARAMS; 
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
static void drawLine8(LineDrawParam *lP)
{
	A_long p = lP->x0 + lP->y0 * lP->widthTrue;
	A_long o = lP->widthTrue -(lP->x1 - lP->x0 + 1);
	A_long i,j;
	PF_Pixel *data;
	data = (PF_Pixel *)lP->data;
	for(j=lP->y0;j<=lP->y1;j++){
		for(i=lP->x0;i<=lP->x1;i++){
			if  (data[p].alpha != 0)  {
				data[p].red  = RoundByteLong(data[p].red	+ FS_CONVERT16TO8(lP->r));
				data[p].green= RoundByteLong(data[p].green	+ FS_CONVERT16TO8(lP->g));
				data[p].blue = RoundByteLong(data[p].blue	+ FS_CONVERT16TO8(lP->b));
			}
			p++;
		}
		p += o;
	}
}
//-------------------------------------------------------------------------------------------------
static void drawLine16(LineDrawParam *lP)
{
	A_long p = lP->x0 + lP->y0 * lP->widthTrue;
	A_long o = lP->widthTrue -(lP->x1 - lP->x0 + 1);
	A_long i,j;
	PF_Pixel16 *data;
	data = (PF_Pixel16 *)lP->data;
	for(j=lP->y0;j<=lP->y1;j++){
		for(i=lP->x0;i<=lP->x1;i++){
			if  (data[p].alpha != 0)  {
				data[p].red  = RoundShortFpLong(data[p].red	+ lP->r);
				data[p].green= RoundShortFpLong(data[p].green	+ lP->g);
				data[p].blue = RoundShortFpLong(data[p].blue	+ lP->b);
			}
			p++;
		}
		p += o;
	}
}
//-------------------------------------------------------------------------------------------------
static void drawLine32(LineDrawParam *lP)
{

	A_long p = lP->x0 + lP->y0 * lP->widthTrue;
	A_long o = lP->widthTrue -(lP->x1 - lP->x0 + 1);
	A_long i,j;
	PF_PixelFloat *data;
	data = (PF_PixelFloat *)lP->data;
	for(j=lP->y0;j<=lP->y1;j++){
		for(i=lP->x0;i<=lP->x1;i++){
			if  (data[p].alpha != 0)  {
				data[p].red  = RoundFpShortDouble(data[p].red	+ (PF_FpShort)lP->r/PF_MAX_CHAN16);
				data[p].green= RoundFpShortDouble(data[p].green	+ (PF_FpShort)lP->g/PF_MAX_CHAN16);
				data[p].blue = RoundFpShortDouble(data[p].blue	+ (PF_FpShort)lP->b/PF_MAX_CHAN16);
			}
			p++;
		}
		p += o;
	}
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetLineDrawParamsFromAE(CFsAE *ae, LineDrawParam *lP)
{
	PF_Err		err 		= PF_Err_NONE;
	lP->data		= ae->out->data();
	lP->width		= ae->out->width();
	lP->widthTrue	= ae->out->widthTrue();
	lP->height		= ae->out->height();
	return err;
}
//-------------------------------------------------------------------------------------------------
static PF_Boolean GetLineDrawParamsFromParamInfo(ParamInfo *infoP, LineDrawParam *lP)
{
	PF_Boolean		ret 		= TRUE;
	A_long length = F_RAND2(infoP->lengthMin,infoP->lengthMax);
	if (length<=0) ret = FALSE;

	if ( ret ==TRUE){
		if (infoP->vertualFlag) {
			lP->x0 = infoP->x;
			lP->x1 = infoP->x + infoP->weight -1;
			lP->y0 = infoP->y;
			lP->y1 = infoP->y + length -1 ;
		}else{
			lP->x0 = infoP->x;
			lP->x1 = infoP->x + length -1 ;
			lP->y0 = infoP->y;
			lP->y1 = infoP->y + infoP->weight -1;
		}
		if ( (lP->x1<0) || (lP->x0>=lP->width) ||(lP->y1<0) || (lP->y0>=lP->height) ) ret=FALSE;
		if (ret==TRUE){
			if (lP->x0<0) lP->x0=0;
			if (lP->x1>=lP->width) lP->x1 = lP->width -1;
			if (lP->y0<0) lP->y0=0;
			if (lP->y1>=lP->height) lP->y1 = lP->height -1;
		}
	}
	if ( ret==TRUE){
		if (infoP->color) {
			lP->r = F_RAND2(-infoP->strong,infoP->strong);
			lP->g = F_RAND2(-infoP->strong,infoP->strong);
			lP->b = F_RAND2(-infoP->strong,infoP->strong);
		}else{
			lP->r = lP->g = lP->b = F_RAND2(-infoP->strong,infoP->strong);
			F_RAND();
			F_RAND();
		}
	}else{
		F_RAND();
		F_RAND();
		F_RAND();
	}
	return ret;
}
//-------------------------------------------------------------------------------------------------
static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->GetADD(ID_Y,&infoP->value));
	if (!err) infoP->value *= 20;
	ERR(ae->GetFIXED(ID_STRONG,&infoP->strong));
	if (!err) infoP->strong /=100; 
	ERR(ae->GetADD(ID_LENGTH_MIN,&infoP->lengthMin));
	ERR(ae->GetADD(ID_LENGTH_MAX,&infoP->lengthMax));
	if (!err){
		infoP->lengthMin = ae->downScale(infoP->lengthMin);
		infoP->lengthMax = ae->downScale(infoP->lengthMax);
		if (infoP->lengthMin>infoP->lengthMax) swapLong(&infoP->lengthMin,&infoP->lengthMax);
	}
	ERR(ae->GetCHECKBOX(ID_COLOR,&infoP->color));
	ERR(ae->GetADD(ID_WEIGHT,&infoP->weight));
	if (!err){
		infoP->weight = ae->downScale(infoP->weight);
	}
	ERR(ae->GetCHECKBOX(ID_VERTUAL,&infoP->vertualFlag));

	return err;
}
void (*drawLine)(LineDrawParam *lP);
//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err	err = PF_Err_NONE;

	// Copy input to output
	ERR(ae->CopyInToOut());
	if ( (infoP->value>0)&&(infoP->strong>0)){

		F_SRAND(ae->frame());

		A_long i;
		LineDrawParam l;
		GetLineDrawParamsFromAE(ae,&l);
		switch(ae->pixelFormat())
		{
		case PF_PixelFormat_ARGB128:
			drawLine = drawLine32;
			break;
		case PF_PixelFormat_ARGB64:
			drawLine = drawLine16;
			break;
		case PF_PixelFormat_ARGB32:
			drawLine = drawLine8;
			break;
		}
		A_long left = infoP->lengthMax/-2;
		for (i=0;i<infoP->value;i++){
			infoP->x = F_RAND2(left,l.width);
			infoP->y = F_RAND3(l.height);
			if ( GetLineDrawParamsFromParamInfo(infoP,&l)==TRUE) drawLine(&l);
		}
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
// Rendering main routine
/*
	Hosts that don't support SmartFX (Before After Effects 7) call this function for rendering
	This function supports v6.5 for backward compatibility
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
		ERR(ae.CopyInToOut());
		ParamInfo info;
		ERR(GetParams(&ae,&info));
		ERR(Exec(&ae,&info));
	}
	return err;
}
//-------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
/*
	For SmartFX support, this function is called first to check parameter values
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
static PF_Err 
RespondtoAEGP ( 	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void*			extraP)
{
	PF_Err			err = PF_Err_NONE;
	
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg, 
											"%s",	
											reinterpret_cast<A_char*>(extraP));

	return err;
}

//-----------------------------------------------------------------------------------
DllExport	PF_Err 
EntryPointFunc (
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP)
{
	PF_Err		err = PF_Err_NONE;
	
	try
	{
		CFsAE ae;
		switch (cmd) {
			case PF_Cmd_ABOUT:
				err = About(in_data,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETUP:
				err = GlobalSetup(	in_data,out_data,params,output);
				break;
			case PF_Cmd_GLOBAL_SETDOWN:
				err = GlobalSetdown(in_data);
				break;
			case PF_Cmd_PARAMS_SETUP:
				err = ParamsSetup(	in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_SETUP:
				err = SequenceSetup(in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_SETDOWN:
				err = SequenceSetdown(in_data,out_data,params,output);
				break;
			case PF_Cmd_SEQUENCE_RESETUP:
				err = SequenceResetup(in_data,out_data,params,output);
				break;
			case PF_Cmd_RENDER:
					err = Render(in_data,out_data,params,output);
					break;
#if defined(SUPPORT_SMARTFX)
			case PF_Cmd_SMART_PRE_RENDER:
				err = PreRender(in_data,out_data,reinterpret_cast<PF_PreRenderExtra*>(extraP));
				break;
			case PF_Cmd_SMART_RENDER:
				err = SmartRender(	in_data,out_data,reinterpret_cast<PF_SmartRenderExtra*>(extraP));
				break;
#endif
			case PF_Cmd_COMPLETELY_GENERAL:
				err = RespondtoAEGP(in_data,out_data,params,output,extraP);
				break;
			case PF_Cmd_DO_DIALOG:
				//err = PopDialog(in_data,out_data,params,output);
				break;		
			case PF_Cmd_USER_CHANGED_PARAM:
				err = HandleChangedParam(	in_data,
											out_data,
											params,
											output, 
											reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
			case PF_Cmd_QUERY_DYNAMIC_FLAGS:
				err = QueryDynamicFlags(in_data,
										out_data,
										params,
										reinterpret_cast<PF_UserChangedParamExtra*>(extraP));
				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
