//-----------------------------------------------------------------------------------
/*
	MainLineRepaint for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef MainLineRepaint_H
#define MainLineRepaint_H

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
//#include "FsAE.h"

// UI parameter IDs
// Used by ParamsSetup and Render functions via params
enum {
	ID_INPUT = 0,	// default input layer

	ID_Main_Color,
	ID_level,

	ID_NUM_PARAMS
};

// UI strings
#define	STR_Main_Color	"Main Color"
#define	STR_level		"Level(%)"

//UI�̃p�����[�^
typedef struct ParamInfo {
	PF_Pixel  		Main_Color;
	A_u_char		lv;
	A_long			count;
	PF_PixelPtr		scanline;
	A_long			scanLength;
	A_long			scanCount;
} ParamInfo, *ParamInfoP, **ParamInfoH;





//-------------------------------------------------------
#define PPNORMAL 255
#define PPTRANS 256
#define PPMAIN 257

#define PS_NORMAL 0
#define PS_TRANS 1
#define PS_MAIN 2

inline A_long PxStatus(A_long v)
{
	if (v == PPMAIN) {
		return PS_MAIN;
	}
	else if (v == PPTRANS)
	{
		return PS_TRANS;
	}
	else
	{
		return PS_NORMAL;
	}
}
//-------------------------------------------------------
inline A_long pV8(PF_Pixel p,PF_Pixel m,A_u_char lv)
{
	A_long ret = PF_MAX_CHAN8;
	if (p.alpha == 0) {
		ret = PPTRANS;
		return ret;
	}
	if (compPix8Lv(p, m, lv) == TRUE)
	{
		ret = PPMAIN;
		return ret;
	}
	double r = (double)p.red / PF_MAX_CHAN8;
	double g = (double)p.green / PF_MAX_CHAN8;
	double b = (double)p.blue / PF_MAX_CHAN8;
	ret= (A_long)(((0.29891 * r) + (0.58661 * g) + (0.11448 * b)) * PF_MAX_CHAN8+0.5);
	if (ret > PF_MAX_CHAN8) 
		ret = PF_MAX_CHAN8;
	else if (ret < 0)
		ret = 0;

	return ret;
}
//-------------------------------------------------------
inline A_long pV16(PF_Pixel16 p, PF_Pixel m, A_u_char lv)
{
	A_long ret = PF_MAX_CHAN8;
	if (p.alpha == 0) {
		ret = PPTRANS;
		return ret;
	}
	PF_Pixel p2 = CONV16TO8(p);
	if (compPix8Lv(p2, m, lv) == TRUE)
	{
		ret = PPMAIN;
		return ret;
	}
	double r = (double)p.red / PF_MAX_CHAN16;
	double g = (double)p.green / PF_MAX_CHAN16;
	double b = (double)p.blue / PF_MAX_CHAN16;
	ret = (A_long)(((0.29891 * r) + (0.58661 * g) + (0.11448 * b)) * PF_MAX_CHAN8 + 0.5);
	if (ret > PF_MAX_CHAN8)
		ret = PF_MAX_CHAN8;
	else if (ret < 0)
		ret = 0;

	return ret;
}
//-------------------------------------------------------
inline A_long pV32(PF_PixelFloat p, PF_Pixel m, A_u_char lv)
{
	A_long ret = PF_MAX_CHAN8;
	if (p.alpha == 0) {
		ret = PPTRANS;
		return ret;
	}
	PF_Pixel p2 = CONV32TO8(p);
	if (compPix8Lv(p2, m, lv) == TRUE)
	{
		ret = PPMAIN;
		return ret;
	}
	double r = (double)p.red;
	if (r > 1) r = 1;
	double g = (double)p.green;
	if (g > 1) g = 1;
	double b = (double)p.blue;
	if (b > 1) b = 1;
	ret = (A_long)(((0.29891 * r) + (0.58661 * g) + (0.11448 * b)) * PF_MAX_CHAN8 + 0.5);
	if (ret > PF_MAX_CHAN8)
		ret = PF_MAX_CHAN8;
	else if (ret < 0)
		ret = 0;

	return ret;
}
//-----------------------------------------------------------------------------------

 PF_Err Exec8(CFsAE* ae, ParamInfo* infoP);
PF_Err Exec16(CFsAE* ae, ParamInfo* infoP);
PF_Err Exec32(CFsAE* ae, ParamInfo* infoP);

extern "C" {

DllExport 
PF_Err 
EntryPointFunc (	
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // MainLineRepaint_H
