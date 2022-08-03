#include "StdAfx.h"
#include "AppIni.h"



CAppIni::CAppIni(const char *inipath)
: CIni(inipath)
{
	LoadData();
}

CAppIni::~CAppIni()
{
	SaveData();
}

void CAppIni::LoadData()
{
	TransferAllData (false);
}

void CAppIni::SaveData()
{
	TransferAllData (true);
}

void CAppIni::TransferAllData (bool bSave)
{
	Transfer (bSave, "macroOptions",		(DWORD &)macroOptions,	0x00);
	Transfer (bSave, "recOptions",			(DWORD &)recOptions,	0x37);

	Transfer (bSave, "windowSX",			windowSX,				100);
	Transfer (bSave, "windowSY",			windowSY,				100);

	Transfer (bSave, "macroFileName",		macroFileName,			MAX_PATH,	"macro.m");
	Transfer (bSave, "macroProgramTitle",	macroProgramTitle,		MAX_PATH,	"키보드/마우스 매크로 V1(쉬운 버전)");
	macroFileName[MAX_PATH] = '\0';
	macroProgramTitle[MAX_PATH] = '\0';

	Transfer (bSave, "eventDelay",			eventDelay,				33);
	Transfer (bSave, "keyMacroRun",			keyMacroRun,			VK_F10);
	Transfer (bSave, "keyMacroRecord",		keyMacroRecord,			VK_F11);
	Transfer (bSave, "keyMousePosCapture",	keyMousePosCapture,		VK_F12);

	Transfer (bSave, "recMouseDistance",	recMouseDistance,		10);
	Transfer (bSave, "recEventTimeInterval",recEventTimeInterval,	100);
}

CAppIni g_ini("key_macro.ini");