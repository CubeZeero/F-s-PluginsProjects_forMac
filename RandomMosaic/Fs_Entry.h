//-----------------------------------------------------------------------------------
/*
	F's Plugins Entry Point for Mac
*/
//-----------------------------------------------------------------------------------
#pragma once

#ifndef RandomMosaic_Fs_Entry_H
#define RandomMosaic_Fs_Entry_H

#include "RandomMosaic.h"

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
static PF_Err ParamsSetup (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output)
{
	PF_Err			err = PF_Err_NONE;
	PF_ParamDef		def;

	//First parameter
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_Y,//Parameter name
					0, 				//Minimum value when slider is used
					2048,			//Maximum value when slider is used
					0,				//Slider minimum value 
					512,			//Slider maximum value
					0,					//Default value
					ID_Y
					);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_SIZEMAX,//Parameter name
					3, 				//Minimum value when slider is used
					1024,			//Maximum value when slider is used
					12,				//Slider minimum value 
					64,				//Slider maximum value
					24,				//Default value
					ID_SIZEMAX
					);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_SIZEMIN,//Parameter name
					3, 				//Minimum value when slider is used
					1024,			//Maximum value when slider is used
					6,				//Slider minimum value 
					64,			//Slider maximum value
					6,				//Default value
					ID_SIZEMIN
					);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_ASPECT,//Parameter name
					0, 				//Minimum value when slider is used
					100,			//Maximum value when slider is used
					0,				//Slider minimum value 
					100,			//Slider maximum value
					0,				//Default value
					ID_ASPECT
					);
	AEFX_CLR_STRUCT(def);
	PF_ADD_SLIDER(	STR_RANDOMCOLOR,//Parameter name
					0, 				//Minimum value when slider is used
					255,			//Maximum value when slider is used
					0,				//Slider minimum value 
					16,			//Slider maximum value
					0,				//Default value
					ID_RANDCOLOR
					);

	out_data->num_params = ID_NUM_PARAMS;

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

	ERR(ae->GetADD(ID_Y,&infoP->value));
	
	ERR(ae->GetADD(ID_SIZEMAX,&infoP->sizeMax));
	if (!err) infoP->sizeMax = ae->downScale(infoP->sizeMax);
	
	ERR(ae->GetADD(ID_SIZEMIN,&infoP->sizeMin));
	if (!err) {
		infoP->sizeMin = ae->downScale(infoP->sizeMin);
		if (infoP->sizeMin > infoP->sizeMax) infoP->sizeMin = infoP->sizeMax;
	}
	
	ERR(ae->GetADD(ID_ASPECT,&infoP->aspect));
	
	ERR(ae->GetADD(ID_RANDCOLOR,&infoP->randomColor));

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err Exec8(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->CopyInToOut());
	if (!err){
		PF_Pixel *data;
		PF_Pixel *outData;
		ae->GetInData(&data);
		ae->GetOutData(&outData);
		
		A_long width = ae->in_data->width;
		A_long height = ae->in_data->height;
		A_long lineLng = ae->in_data->widthTrue;
		
		A_long sizeMax = infoP->sizeMax;
		A_long sizeMin = infoP->sizeMin;
		A_long aspect = infoP->aspect;
		A_long randomColor = infoP->randomColor;
		
		//Random mosaic effect implementation
		//This is a simplified version - actual implementation would be more complex
		for (A_long y = 0; y < height; y += sizeMax) {
			for (A_long x = 0; x < width; x += sizeMax) {
				//Get random color for this mosaic block
				PF_Pixel color;
				if (randomColor > 0) {
					color.red = (A_u_char)(rand() % 256);
					color.green = (A_u_char)(rand() % 256);
					color.blue = (A_u_char)(rand() % 256);
					color.alpha = 255;
				} else {
					//Use average color of the block
					color = data[y * lineLng + x];
				}
				
				//Fill the mosaic block
				A_long blockSize = sizeMin + (rand() % (sizeMax - sizeMin + 1));
				for (A_long by = 0; by < blockSize && (y + by) < height; by++) {
					for (A_long bx = 0; bx < blockSize && (x + bx) < width; bx++) {
						outData[(y + by) * lineLng + (x + bx)] = color;
					}
				}
			}
		}
	}

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err Exec16(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->CopyInToOut());
	if (!err){
		PF_Pixel16 *data;
		PF_Pixel16 *outData;
		ae->GetInData(&data);
		ae->GetOutData(&outData);
		
		A_long width = ae->in_data->width;
		A_long height = ae->in_data->height;
		A_long lineLng = ae->in_data->widthTrue;
		
		A_long sizeMax = infoP->sizeMax;
		A_long sizeMin = infoP->sizeMin;
		A_long aspect = infoP->aspect;
		A_long randomColor = infoP->randomColor;
		
		//Random mosaic effect implementation for 16-bit
		//This is a simplified version - actual implementation would be more complex
		for (A_long y = 0; y < height; y += sizeMax) {
			for (A_long x = 0; x < width; x += sizeMax) {
				//Get random color for this mosaic block
				PF_Pixel16 color;
				if (randomColor > 0) {
					color.red = (A_u_short)(rand() % 65536);
					color.green = (A_u_short)(rand() % 65536);
					color.blue = (A_u_short)(rand() % 65536);
					color.alpha = 65535;
				} else {
					//Use average color of the block
					color = data[y * lineLng + x];
				}
				
				//Fill the mosaic block
				A_long blockSize = sizeMin + (rand() % (sizeMax - sizeMin + 1));
				for (A_long by = 0; by < blockSize && (y + by) < height; by++) {
					for (A_long bx = 0; bx < blockSize && (x + bx) < width; bx++) {
						outData[(y + by) * lineLng + (x + bx)] = color;
					}
				}
			}
		}
	}

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err Exec32(CFsAE *ae, ParamInfo *infoP)
{
	PF_Err		err 		= PF_Err_NONE;

	ERR(ae->CopyInToOut());
	if (!err){
		PF_PixelFloat *data;
		PF_PixelFloat *outData;
		ae->GetInData(&data);
		ae->GetOutData(&outData);
		
		A_long width = ae->in_data->width;
		A_long height = ae->in_data->height;
		A_long lineLng = ae->in_data->widthTrue;
		
		A_long sizeMax = infoP->sizeMax;
		A_long sizeMin = infoP->sizeMin;
		A_long aspect = infoP->aspect;
		A_long randomColor = infoP->randomColor;
		
		//Random mosaic effect implementation for 32-bit float
		//This is a simplified version - actual implementation would be more complex
		for (A_long y = 0; y < height; y += sizeMax) {
			for (A_long x = 0; x < width; x += sizeMax) {
				//Get random color for this mosaic block
				PF_PixelFloat color;
				if (randomColor > 0) {
					color.red = (float)(rand() % 1000) / 1000.0f;
					color.green = (float)(rand() % 1000) / 1000.0f;
					color.blue = (float)(rand() % 1000) / 1000.0f;
					color.alpha = 1.0f;
				} else {
					//Use average color of the block
					color = data[y * lineLng + x];
				}
				
				//Fill the mosaic block
				A_long blockSize = sizeMin + (rand() % (sizeMax - sizeMin + 1));
				for (A_long by = 0; by < blockSize && (y + by) < height; by++) {
					for (A_long bx = 0; bx < blockSize && (x + bx) < width; bx++) {
						outData[(y + by) * lineLng + (x + bx)] = color;
					}
				}
			}
		}
	}

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
	Exec (CFsAE *ae , ParamInfo *infoP)
{
	PF_Err		err = PF_Err_NONE;

	// Responds to the user about aborting
	if (!err) {
		ERR(ae->Err_Alloc(sizeof(ParamInfo), &infoP));
	}
	if (!err) {
		ERR(GetParams(ae, infoP));
	}
	if (!err) {
		ERR(ae->Exec());
	}
	if (!err) {
		ERR(ae->Err_Alloc(sizeof(ParamInfo), &infoP));
	}
	if (!err) {
		ERR(GetParams(ae, infoP));
	}
	if (!err) {
		ERR(ae->Exec());
	}

	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
Render ( 
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err 		= PF_Err_NONE;
	PF_Handle		pixelFormat = 	NULL;
	
	CFsAE ae(in_data,out_data,params,output,ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err) {
		ERR(ae.CopyInToOut());
	}
	if (!err) {
		ERR(ae.GetParams());
	}
	if (!err) {
		ERR(ae.Exec());
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err
PreRender(
	PF_InData			*in_data,
	PF_OutData			*out_data,
	PF_PreRenderExtra	*extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	CFsAE ae(in_data,out_data,extraP,sizeof(ParamInfo),ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err) {
		ERR(ae.GetParams());
	}
	if (!err) {
		ERR(ae.PreRender());
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err
SmartRender(
	PF_InData				*in_data,
	PF_OutData				*out_data,
	PF_SmartRenderExtra		*extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	CFsAE ae(in_data,out_data,extraP,ID_NUM_PARAMS);
	err = ae.resultErr();
	if (!err) {
		ERR(ae.GetParams());
	}
	if (!err) {
		ERR(ae.SmartRender());
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
static PF_Err 
RespondtoAEGP ( 	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void*			extraP)
{
	PF_Err		err 		= PF_Err_NONE;
	
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacks()->sprintf( out_data->return_msg, 
		"RespondtoAEGP was called.");
	return err;
}

//-------------------------------------------------------------------------------------------------
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
	
	try {
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
				err = ParamsSetup (in_data,out_data,params,output);
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
			case PF_Cmd_SMART_PRE_RENDER:
				err = PreRender(in_data,out_data,(PF_PreRenderExtra*)extraP);
				break;
			case PF_Cmd_SMART_RENDER:
				err = SmartRender(in_data,out_data,(PF_SmartRenderExtra*)extraP);
				break;
			case PF_Cmd_COMPLETELY_GENERAL:
				err = RespondtoAEGP(in_data,out_data,params,output,extraP);
				break;
			case PF_Cmd_DO_DIALOG:
				err = RespondtoAEGP(in_data,out_data,params,output,extraP);
				break;	
			case PF_Cmd_USER_CHANGED_PARAM:
				err = HandleChangedParam(in_data,out_data,params,output,extraP);
				break;
			case PF_Cmd_QUERY_DYNAMIC_FLAGS:
				err = QueryDynamicFlags(in_data,out_data,params,extra);
				break;
		}
	}
	catch(PF_Err & thrown_err){
		err = thrown_err;
	}
	catch ( LSys::X & thrown_err){
		err = thrown_err.result();
	}
	catch (...){
		err = PF_Err_INTERNAL_STRUCT_DAMAGED;
	}
	return err;
}

//-------------------------------------------------------------------------------------------------
PF_Err PluginDataEntryFunction2(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extraP)
{
	return EntryPointFunc(cmd, in_data, out_data, params, output, extraP);
}

#endif // RandomMosaic_Fs_Entry_H 