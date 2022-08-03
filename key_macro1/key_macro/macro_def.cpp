#include "stdafx.h"
#include <time.h>
#include <math.h>
#include "macro_def.h"
#include "AppIni.h"
#include "Common.h"

extern bool g_keyProcDisable;

static bool macroRunning = false;
vector<sMacro> g_macros;

void LoadMacros (const char *macroFileName)
{
	FILE *fp = fopen (macroFileName, "rb");
	if (!fp) return;

	g_macros.clear ();

	long c = 0;
	fread (&c, sizeof(long), 1, fp);

	g_macros.resize(c);
	for (int i=0; i<c; ++i) {
		sMacro &m = g_macros[i];

		fread (m.name,       sizeof(char), 256, fp);
		fread (&m.start_key, sizeof(long), 1, fp);
		fread (&m.stop_key,  sizeof(long), 1, fp);
		fread (&m.repeat_cnt,sizeof(long), 1, fp);
		
		long d = 0;
		fread (&d, sizeof(long), 1, fp);

		m._item.resize (d);
		for (int j=0; j<d; ++j) {
			fread (&m._item[j], sizeof(sMacroItem), 1, fp);
		}
	}
	fclose (fp);
}

void SaveMacro (const char *macroFileName)
{
	FILE *fp = fopen (macroFileName, "wb");
	if (!fp) return;

	long c = g_macros.size();
	fwrite (&c, sizeof(long), 1, fp);

	for (int i=0; i<c; ++i) {
		sMacro &m = g_macros[i];

		fwrite (m.name,       sizeof(char), 256, fp);
		fwrite (&m.start_key, sizeof(long), 1, fp);
		fwrite (&m.stop_key,  sizeof(long), 1, fp);
		fwrite (&m.repeat_cnt,sizeof(long), 1, fp);
		
		long d = m._item.size();
		fwrite (&d, sizeof(long), 1, fp);

		for (int j=0; j<d; ++j) {
			fwrite (&m._item[j], sizeof(sMacroItem), 1, fp);
		}
	}
	fclose (fp);
}

void MacroStartStop (int vk)
{
	if (!macroRunning) return;

	for (unsigned int i=0; i<g_macros.size(); ++i) {
		sMacro &m = g_macros[i];

		// 매크로가 비실행상태에서 시작키가 눌렸을 때, 첫 _item부터 시작한다.
		if (!m.is_running() && m.start_key == vk) {
			m.start (1);
		}
		// 매크로가 실행상태에서 중지키가 눌렸을 때, 중지 상태로 만든다.
		else if (m.is_running() && m.stop_key == vk) {
			m.stop ();
		}
	}
}

void MacroStart (int id, int index)
{
	if (0 <= id && id < (int)g_macros.size()) {
		sMacro &m = g_macros[id];

		// 매크로가 비실행 상태이거나 실행종료 상태이면 첫 _item부터 시작한다.
		if (!m.is_running()) {
			m.start (index);
		}
	}
}

void MacroInit ()
{
	macroRunning = true;

	for (unsigned int i=0; i<g_macros.size(); ++i) {
		sMacro &m = g_macros[i];

		m.init ();
	}
}

void MacroTerm ()
{
	macroRunning = false;

	for (unsigned int i=0; i<g_macros.size(); ++i) {
		g_macros[i].stop ();
	}
}

int GetMouseButtonVK_ (long flags)
{
	int vk = 0;

	if      (flags & MOUSEEVENTF_LEFTDOWN)  { vk = VK_LBUTTON;				}
	else if (flags & MOUSEEVENTF_LEFTUP)    { vk = VK_LBUTTON | 0x10000;	}
	else if (flags & MOUSEEVENTF_RIGHTDOWN) { vk = VK_RBUTTON;				}
	else if (flags & MOUSEEVENTF_RIGHTUP)   { vk = VK_RBUTTON | 0x10000;	}
	else if (flags & MOUSEEVENTF_MIDDLEDOWN){ vk = VK_MBUTTON;				}
	else if (flags & MOUSEEVENTF_MIDDLEUP)  { vk = VK_MBUTTON | 0x10000;	}
	else if (flags & MOUSEEVENTF_WHEEL)     { vk = ((short)HIWORD(flags) > 0) ? 0x0A : 0x0B; }
	else if (flags & MOUSEEVENTF_XDOWN) {
		if (HIWORD(flags) & XBUTTON1)		{ vk = VK_XBUTTON1;  }
		if (HIWORD(flags) & XBUTTON2)		{ vk = VK_XBUTTON2;  }
	}
	else if (flags & MOUSEEVENTF_XUP) {
		if (HIWORD(flags) & XBUTTON1)		{ vk = VK_XBUTTON1 | 0x10000;  }
		if (HIWORD(flags) & XBUTTON2)		{ vk = VK_XBUTTON2 | 0x10000;  }
	}
	return vk;
}

void MacroStep (sMacro &m, int dt)
{
	sMacroItem &mi = m._item[m.index];

	switch (mi.type) {
	case sMacroItem::KEY:
		if(mi.key.flags & 1) {
			g_keyProcDisable = true;
			keybd_event ((BYTE)mi.key.vk, 0, KEYEVENTF_EXTENDEDKEY, 0);
			g_keyProcDisable = false;

			MacroStartStop ((BYTE)mi.key.vk);
		}

		if(mi.key.flags & 2) {
			g_keyProcDisable = true;
			keybd_event ((BYTE)mi.key.vk, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			g_keyProcDisable = false;

			MacroStartStop ((BYTE)mi.key.vk | 0x10000);
		}

		m.index ++;
		break;

	case sMacroItem::MOUSE: {
		int mx = mi.mouse.x;
		int my = mi.mouse.y;

		ScreenIndependentMousePos (mx, my);

		DWORD flag1 = mi.mouse.flags & (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_XDOWN | MOUSEEVENTF_MOVE | MOUSEEVENTF_WHEEL);
		
		if (flag1 & MOUSEEVENTF_MOVE) flag1 |= MOUSEEVENTF_ABSOLUTE;

		if (flag1) {
			g_keyProcDisable = true;
			mouse_event (flag1, mx, my, (short)HIWORD(mi.mouse.flags), 0);
			g_keyProcDisable = false;

			MacroStartStop (GetMouseButtonVK_ (mi.mouse.flags));
		}
		
		DWORD flag2 = mi.mouse.flags & (MOUSEEVENTF_LEFTUP | MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_XUP );
		
		if (flag2) {
			g_keyProcDisable = true;
			mouse_event (flag2, mx, my, 0, 0);
			g_keyProcDisable = false;

			MacroStartStop (GetMouseButtonVK_ (mi.mouse.flags));
		}

		m.index ++;
		break; }

	case sMacroItem::DELAY:
		if (m.delay == 0) {
			m.delay = mi.time.delay;
		}
		else {
			m.delay -= dt;
		}
		
		if (m.delay <= 0) { 
			m.index ++; 
			m.delay = 0;
		}
		break;

	default:
		m.index ++;
		break;
	}
}

void AllMacroStep (int dt)
{
	if (!macroRunning) return;

	for (unsigned int i=0; i<g_macros.size(); ++i) {
		sMacro &m = g_macros[i];

		if (0 < m.index && m.index < (int)m._item.size()) {
			MacroStep (m, dt);

			if ((int)m._item.size() <= m.index) {
				m.run_count++;

				if ((m.repeat_cnt == 0) || (m.run_count < m.repeat_cnt)) {
					m.index = 1; // 처음부터 재시작
				}
			}
		}
	}
}
