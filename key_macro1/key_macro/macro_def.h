#pragma once
#include <vector>

using namespace std;

struct sMacroItem {
	enum { NONE = 0, KEY, MOUSE, DELAY } type;

	union {
		struct sKey {
			long vk;
			unsigned long flags;
			// 0x01 - 누르기
			// 0x02 - 떼기
			// 0x03 - 누르고 떼기
		} key;

		struct sMouse {
			long x, y;
			unsigned long flags;
		} mouse;

		struct sTime {
			long delay; // 단위: msec
		} time;

		long data[3];
	};

	sMacroItem () : type(NONE) 
	{ 
		data[0] = data[1] = data[2] = 0;
	}
	
	sMacroItem (const sMacroItem &mi) {
		type = mi.type;
		data[0] = mi.data[0];
		data[1] = mi.data[1];
		data[2] = mi.data[2];
	}
	
	sMacroItem &operator = (const sMacroItem &mi) {
		if (this != &mi) {
			type = mi.type;
			data[0] = mi.data[0];
			data[1] = mi.data[1];
			data[2] = mi.data[2];
		}
		return *this;
	}
};

struct sMacro {
	char name[256];
	long start_key;
	long stop_key;
	long repeat_cnt;

	vector<sMacroItem> _item;

	// 매크로 실행시 필요한 변수들
	long index;
	long delay;
	long str_index;
	long run_count;

	void init ()
	{
		index = -1;
		delay = 0;
		str_index = 0;
		run_count = 0;
	}

	void start (int index_ = 1)
	{
		init();
		index = index_;
	}

	void stop ()
	{
		index = _item.size();
		run_count = repeat_cnt;
	}

	bool is_running()
	{
		return 0 <= index && index < (int)_item.size();
	}

	sMacro () : 
		start_key(0), 
		stop_key(0), 
		repeat_cnt(1) 
	{
		init();
		name[0] = '\0';
	}
	
		sMacro (const sMacro &macro) {
		strncpy (name, macro.name, 256);
		name[256-1] = '\0';
		start_key	= macro.start_key;
		stop_key	= macro.stop_key;
		repeat_cnt	= macro.repeat_cnt;
		_item = macro._item;

		init ();
	}

	sMacro &operator = (const sMacro &macro) {
		if (this != &macro) {
			strncpy (name, macro.name, 256);
			name[256-1] = '\0';
			start_key	= macro.start_key;
			stop_key	= macro.stop_key;
			repeat_cnt	= macro.repeat_cnt;
			_item = macro._item;

			init ();
		}
		return *this;
	}
};

extern vector<sMacro> g_macros;

void LoadMacros (const char *macroFileName);
void SaveMacro (const char *macroFileName);

void MacroStartStop (int vk);
void MacroInit ();
void MacroTerm ();

void AllMacroStep (int dt);
void MacroStep (sMacro &m, int dt);
