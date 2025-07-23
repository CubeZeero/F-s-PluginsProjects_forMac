/*
	Plugin parameter settings

	PiPL resource code should be minimum

*/
#pragma once
#ifndef Filter_Target_H
#define Filter_Target_H

// Version definitions (from FsVersion.h to avoid Rez compile issues)
#define	MAJOR_VERSION		3
#define	MINOR_VERSION		0
#define	BUG_VERSION			0
#define	STAGE_VERSION		PF_Stage_RELEASE
#define	BUILD_VERSION		0
#define FS_VERSION	1572864



#define FS_DESCRIPTION		"Filter Effect Filter"
#define	FS_NAME				"F's Filter"
#define FS_MATCH_NAME		FS_NAME
#define FS_CREATER			"Copyright (c) 2019 bryful ( bryful@gmail.com/twitter:bryful )"
//-----------------------------------------------------------------------------------
//Plugin category selection

//#define FS_CATEGORY "NF's Plugins-Cell"
//#define FS_CATEGORY "NF's Plugins-Channel"
//#define FS_CATEGORY "NF's Plugins-Colorize"
//#define FS_CATEGORY "NF's Plugins-Draw"
#define FS_CATEGORY "NF's Plugins-Filter"
//#define FS_CATEGORY "NF's Plugins-Noise"
//#define FS_CATEGORY "NF's Plugins-expression"
//#define FS_CATEGORY "NF's Plugins-{Legacy}"

//#define SUPPORT_SMARTFX			//Enable SmartFX+Float_Color support

//value:4 [PF_OutFlag_NON_PARAM_VARY] Draw on all layers

//value:64 [PF_OutFlag_USE_OUTPUT_EXTENT] Use output extent
//value:16777216 [PF_OutFlag_I_HAVE_EXTERNAL_DEPENDENCIES]

//value:33554432[PF_OutFlag_DEEP_COLOR_AWARE] 16bit

//#define FS_OUT_FLAGS	50332164	//Enable to draw on all layers
#define FS_OUT_FLAGS	50332160	//Normal mode



#if defined(SUPPORT_SMARTFX)
//value:8 [PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG] Collapse
//value:1024 [PF_OutFlag2_SUPPORTS_SMART_RENDER] Smart render support
//value:4096 [PF_OutFlag2_FLOAT_COLOR_AWARE] 32bit
#define FS_OUT_FLAGS2	5128

#else
//value : 8[PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG]
#define FS_OUT_FLAGS2	8
#endif

#define FS_ABOUT_STR "function FsAbout()\
{\
	this.pluginName = \"%s\";\
	this.pluginVersion = \"Version %d.%d\";\
	this.pluginDis = \"%s\";\
	this.creater = \"%s\";\
	var winObj = new Window(\"dialog\", \"%s\", [ 0,  0,  500,  200] );\
	this.edFsName = winObj.add(\"edittext\", [  30,   12,   30+ 440,   12+  40], this.pluginName, { readonly:true, borderless:true });\
	this.edFsName.graphics.font = ScriptUI.newFont(\"Tahoma\",ScriptUI.FontStyle.BOLD, 32);\
	\
	this.edFsVersion = winObj.add(\"edittext\", [  70,   60,   70+ 430,   60+  20], this.pluginVersion, { readonly:true, borderless:true });\
	this.edFsVersion.graphics.font = ScriptUI.newFont(\"Tahoma\",ScriptUI.FontStyle.BOLD, 16);\
	\
	this.edFsDis = winObj.add(\"edittext\", [  30,   90,   30 + 470,   90 +  20], this.pluginDis, { readonly:true, borderless:true });\
	this.edFsDis.graphics.font = ScriptUI.newFont(\"Tahoma\",ScriptUI.FontStyle.REGULAR, 16);\
	\
	this.edMyName = winObj.add(\"edittext\", [  30,  120,   30+ 470,  120+  20], this.creater, { readonly:true, borderless:true });\
	this.edMyName.graphics.font = ScriptUI.newFont(\"Tahoma\",ScriptUI.FontStyle.REGULAR, 16);\
	var btnOK = winObj.add(\"button\", [ 360,  150,  360+  100,  150+  40], \"OK\" , { name:\"ok\" });\
	btnOK.graphics.font = ScriptUI.newFont(\"Tahoma\",ScriptUI.FontStyle.REGULAR, 11);\
	this.show = function()\
	{\
		winObj.center(); \
		return winObj.show();\
	}\
}\
var dlg = new FsAbout;\
\
dlg.show();\
"




#endif // Filter_Target_H

