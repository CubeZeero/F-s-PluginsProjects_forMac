//-----------------------------------------------------------------------------------
/*
	F's Plugins for VS2010/VS2012
*/
//-----------------------------------------------------------------------------------

#pragma once
#ifndef FS_TAGET_H
#define FS_TAGET_H

//-----------------------------------------------------------------------------------
//�v���O�C���̎��ʂɎg���閼�O
#define FS_NAME			"F's Mosaic"
//-----------------------------------------------------------------------------------
// Description used in the plugin UI
#define FS_DESCRIPTION	"Mosaic effect"

	//-----------------------------------------------------------------------------------
	//�v���O�C�����\������郁�j���[��
	//#define FS_CATEGORY "F's Plugins-Channel"
	//#define FS_CATEGORY "F's Plugins-Draw"
	#define FS_CATEGORY "NF's Plugins-Filter"
	//#define FS_CATEGORY "F's Plugins-Cell"
	//#define FS_CATEGORY "F's Plugins-Colorize"
	//#define FS_CATEGORY "F's Plugins-Script"
//#define FS_CATEGORY "F's Plugins-Test"

//-----------------------------------------------------------
#ifndef SUPPORT_SMARTFX			//�Q�d�o�^��h��
#define SUPPORT_SMARTFX			//�����L���ɂ����SmartFX+Float_Color�ɑΉ�����
#endif
//#define NO_USE_FSGRAPHICS	//�����L���ɂ����FsGraphics�֌W���C���N���[�h����Ȃ�

//-----------------------------------------------------------------------------------
// Version header (resolved via REZ_SEARCH_PATHS)
#include "FsVersion.h"

//-----------------------------------------------------------------------------------
//out_flags
/*
out_data->out_flags
	PF_OutFlag_PIX_INDEPENDENT		1024
	PF_OutFlag_NON_PARAM_VARY			4
	PF_OutFlag_DEEP_COLOR_AWARE		33554432
	PF_OutFlag_USE_OUTPUT_EXTENT	64
	PF_OutFlag_I_EXPAND_BUFFER		512
	PF_OutFlag_I_DO_DIALOG				32
*/

//#define FS_OUT_FLAGS	33556032
#define FS_OUT_FLAGS	33556036	//��������L���ɂ���Ɩ��t���[�����Ƃɕ`�悷��
//#define FS_OUT_FLAGS	1600		//8bit�̂�
//-----------------------------------------------------------------------------------
//out_flags2
/*
out_data->out_flags2
	PF_OutFlag2_FLOAT_COLOR_AWARE					4096
	PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG	8
	PF_OutFlag2_SUPPORTS_SMART_RENDER				1024
	PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS		1
	PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS;			64
*/
#if defined(SUPPORT_SMARTFX)
#define FS_OUT_FLAGS2 134222921
#else
#define FS_OUT_FLAGS2 134217801
#endif


//-----------------------------------------------------------------------------------
#endif
