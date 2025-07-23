//-----------------------------------------------------------------------------------
/*
	F's Plugins-cs4 for VS2008
*/
//-----------------------------------------------------------------------------------


#pragma once
#ifndef AnimatedNoise_H
#define AnimatedNoise_H

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

//User interface parameter IDs
//Parameter IDs for ParamsSetup and Render functions
enum {
	ID_INPUT = 0,			// default input layer 
	ID_ANIMATED_CB,			//Animate
	ID_ANIMATED_ADD,		//Animate
	ID_VALUE_ADD,			//Noise strength
	ID_LENGTH_FIXED,		//Noise range
	ID_COLOR_CB,			//Color monochrome
	ID_BLOCK_VALUE_FIXED,	//Block noise strength
	ID_BLOCK_LENGTH_FIXED,	//Block noise range
	ID_BLOCK_WIDTH_ADD,		//Block noise width
	ID_BLOCK_HEIGHT_ADD,	//Block noise height
	ID_BLOCK_COLOR_CB,		//Color monochrome

	ID_NUM_PARAMS
	};
typedef struct PrmTbl{
	PF_PixelPtr	data;		//Image
	A_long 		width;		//Image width
	A_long 		height;		//Image height
	A_long 		w;			//Target
	A_long 		h;
	A_long 		target;

	PF_Boolean	animFlag;	//
	A_long 		anim;

	A_long		frame;
	A_long		seed;

	A_long 		value;
	PF_Fixed	length;
	PF_Boolean	colorFlag;

	PF_Fixed	block_value;
	PF_Fixed	block_length;
	A_long 		block_width;
	A_long 		block_height;
	PF_Boolean	block_colorFlag;

} PrmTbl;
static void NoiseMain8(PrmTbl *prm);
static void NoiseMain16(PrmTbl *prm);
static void NoiseMain32(PrmTbl *prm);
static void NoiseBlock8(PrmTbl *prm);
static void NoiseBlock16(PrmTbl *prm);
static void NoiseBlock32(PrmTbl *prm);

//-------------------------------------------------------------------------------------------------
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
#endif // AnimatedNoise_H
