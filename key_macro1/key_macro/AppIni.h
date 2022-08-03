#pragma once
#include "Ini.h"


struct sMacorBitOptions {
	DWORD DUMMY : 1;
};

struct sRecBitOptions {
	DWORD KEYBOARD_KEY_REC		: 1;	// 0x01 - Keyboard �Է� ���
	DWORD MOUSE_BUTTON_REC		: 1;	// 0x02 - Mouse Button �Է� ���
	DWORD MOUSE_POSITION_REC	: 1;	// 0x04 - Mouse ��ġ ��ȭ ���
	DWORD MOUSE_WHEEL_REC		: 1;	// 0x08 - Mouse �� ��ȭ ���
	DWORD EVENT_DELAY			: 1;	// 0x10 - Keyboard�� Mouse �̺�Ʈ�� �ð� ���� ���
	DWORD MERGE_UP_DOWN			: 1;	// 0x20 - Button Up/Down �̺�Ʈ ��ġ�� ���
};

class CAppIni: public CIni
{
	// ���α׷��� ����Ǳ� ���� ini ���Ͽ� �����Ǵ� ������.
	// ���α׷� ������ ���� ������ ���� ���ȴ�.
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
