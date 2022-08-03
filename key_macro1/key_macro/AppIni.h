#pragma once
#include "Ini.h"


struct sMacorBitOptions {
	DWORD DUMMY : 1;
};

struct sRecBitOptions {
	DWORD KEYBOARD_KEY_REC		: 1;	// 0x01 - Keyboard 입력 기록
	DWORD MOUSE_BUTTON_REC		: 1;	// 0x02 - Mouse Button 입력 기록
	DWORD MOUSE_POSITION_REC	: 1;	// 0x04 - Mouse 위치 변화 기록
	DWORD MOUSE_WHEEL_REC		: 1;	// 0x08 - Mouse 휠 변화 기록
	DWORD EVENT_DELAY			: 1;	// 0x10 - Keyboard나 Mouse 이벤트간 시간 간격 기록
	DWORD MERGE_UP_DOWN			: 1;	// 0x20 - Button Up/Down 이벤트 합치기 허용
};

class CAppIni: public CIni
{
	// 프로그램이 종료되기 전에 ini 파일에 보관되는 변수들.
	// 프로그램 내에서 전역 변수와 같이 사용된다.
public: 
	sMacorBitOptions macroOptions;
	sRecBitOptions   recOptions; 

	int  windowSX;
	int  windowSY;  

	char macroFileName[MAX_PATH+1];
	char macroProgramTitle[MAX_PATH+1];

	int  eventDelay;
	int  keyMacroRun;
	int  keyMacroRecord;
	int  keyMousePosCapture;

	int  recMouseDistance;
	int  recEventTimeInterval;

public:
	CAppIni(const char *ini_path);
	virtual ~CAppIni();

	void LoadData();
	void SaveData();

private:
	void TransferAllData (bool bSave);
};

extern CAppIni g_ini;
