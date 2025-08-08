//-----------------------------------------------------------------------------------
/*
	ChromaticAberration for VS2010
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef ChromaticAberration_H
#define ChromaticAberration_H

#include "../FsLibrary/Fs.h"

#include "Fs_Target.h"

#include "AE_PluginData.h"
#include "AE_GeneralPlug.h"

#include "../FsLibrary/FsAE.h"

// User interface parameter IDs
// Parameter IDs for ParamsSetup and Render functions
enum {
	ID_INPUT = 0,	// default input layer

	ID_R,
	ID_G,
	ID_B,
	ID_CENTER,
	ID_NUM_PARAMS
};

//UI�̕\��������
#define	STR_R				"red"
#define	STR_G				"green"
#define	STR_B				"blue"
#define	STR_CENTER			"center"

//UI�̃p�����[�^
typedef struct ParamInfo {
	PF_FpLong	r;
	PF_FpLong	g;
	PF_FpLong	b;

	PF_FpLong	cx;
	PF_FpLong	cy;

	CFsAE*		ae;

} ParamInfo, *ParamInfoP, **ParamInfoH;

//-------------------------------------------------------


//-----------------------------------------------------------------------------------
extern "C" {

DllExport 
PF_Err 
EntryPointFunc(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // ChromaticAberration_H
