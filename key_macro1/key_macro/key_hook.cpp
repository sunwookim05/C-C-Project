#include "stdafx.h"
#include "macro_def.h"
#include "resource.h"
#include "DialogKeyboard.h"
#include "DialogMouse.h"
#include "DialogMacroRec.h"
#include "key_macroDlg.h"

extern CDialogKeyboard  *g_keyDlg;
extern CDialogMouse     *g_mouseDlg;
extern CDialogMacroRec  *g_recDlg;
extern Ckey_macroDlg    *g_macroDlg;

bool g_keyProcDisable = false;

static HHOOK hKeyboardHook = NULL; 
static HHOOK hMouseHook    = NULL;


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (0 <= nCode && !g_keyProcDisable) {
		KBDLLHOOKSTRUCT *keyStat = (KBDLLHOOKSTRUCT *)lParam;
		// TRACE ("K %d %X : %X %X %X %d\n", nCode, wParam, (int)keyStat->flags, keyStat->scanCode, keyStat->vkCode, keyStat->time);

		int vk = 0;
		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) { vk = keyStat->vkCode;            }
		if (wParam == WM_KEYUP   || wParam == WM_SYSKEYUP)   { vk = keyStat->vkCode | 0x10000;  }

		if (g_keyDlg)        g_keyDlg->OnKeyEvent (vk);
		else if (g_mouseDlg) g_mouseDlg->OnKeyEvent (vk);
		else if (g_recDlg)   g_recDlg->OnKeyboardEvent (vk, wParam, keyStat);
		else if (g_macroDlg) g_macroDlg->OnKeyMouseEvent (vk, true);
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

int GetMouseButtonVK (DWORD wParam, DWORD mouseData)
{
	int vk = 0;
	if      (wParam == WM_LBUTTONDOWN) { vk = VK_LBUTTON;				}
	else if (wParam == WM_LBUTTONUP)   { vk = VK_LBUTTON | 0x10000;		}
	else if (wParam == WM_RBUTTONDOWN) { vk = VK_RBUTTON;				}
	else if (wParam == WM_RBUTTONUP)   { vk = VK_RBUTTON | 0x10000;		}
	else if (wParam == WM_MBUTTONDOWN) { vk = VK_MBUTTON;				}
	else if (wParam == WM_MBUTTONUP)   { vk = VK_MBUTTON | 0x10000;		}
	else if (wParam == WM_MOUSEWHEEL)  { vk = ((short)HIWORD(mouseData) > 0) ? 0x0A : 0x0B; }
	else if (wParam == WM_XBUTTONDOWN) {
		if (HIWORD(mouseData) & XBUTTON1) { vk = VK_XBUTTON1;  }
		if (HIWORD(mouseData) & XBUTTON2) { vk = VK_XBUTTON2;  }
	}
	else if (wParam == WM_XBUTTONUP) {
		if (HIWORD(mouseData) & XBUTTON1) { vk = VK_XBUTTON1 | 0x10000;  }
		if (HIWORD(mouseData) & XBUTTON2) { vk = VK_XBUTTON2 | 0x10000;  }
	}
	return vk;
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (0 <= nCode && !g_keyProcDisable) {
		MSLLHOOKSTRUCT *mouseStat = (MSLLHOOKSTRUCT *)lParam;
		// TRACE ("M %d %X : %X (%d, %d) %X %d\n", nCode, wParam, (int)mouseStat->flags, mouseStat->pt.x, mouseStat->pt.y, mouseStat->mouseData, mouseStat->time);

		int vk = GetMouseButtonVK (wParam, mouseStat->mouseData);

		if (g_mouseDlg)      g_mouseDlg->OnMouseEvent (mouseStat->pt.x, mouseStat->pt.y);
		else if (g_recDlg)   g_recDlg->OnMouseEvent (vk, wParam, mouseStat);
		else if (g_macroDlg) g_macroDlg->OnKeyMouseEvent (vk, false);
	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void InstallHook ()
{
	HINSTANCE hInst = AfxGetInstanceHandle ();

	hKeyboardHook = SetWindowsHookEx (WH_KEYBOARD_LL, LowLevelKeyboardProc, hInst, 0); 
	hMouseHook    = SetWindowsHookEx (WH_MOUSE_LL, LowLevelMouseProc, hInst, 0);
}

void UninstallHook ()
{
	UnhookWindowsHookEx(hKeyboardHook);
	UnhookWindowsHookEx(hMouseHook);

	hKeyboardHook = NULL;
	hMouseHook    = NULL;
}