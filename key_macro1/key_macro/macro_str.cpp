#include "StdAfx.h"
#include "macro_def.h"
#include "virtual_key.h"

const char *strKeyboardOption (int flags)
{
	switch(flags) {
	case 0: return "";
	case 1: return "누르기";
	case 2: return "떼기";
	case 3: return "";
	default: return "(오류)";
	}
}

const char *strMouseOption (int flags)
{
	switch(flags) {
	case 0: return "";
	case 1: return "누르기";
	case 2: return "떼기";
	case 3: return "클릭";
	default: return "(오류)";
	}
}

const char *GetItemDescription (const sMacroItem &item)
{
	int n = 0;
	static char desc[256];
	desc[0] = '\0';

	switch (item.type) {
	case sMacroItem::NONE: 
		n = sprintf (desc, "(시작)");
		break;

	case sMacroItem::KEY: {
		int index = getVkIndex(item.key.vk);
		n = sprintf (desc, "키보드 %s ", GetVirtualKeyDesc(index));
		if (item.key.flags) { 
			n += sprintf (desc + n, "%s", strKeyboardOption(item.key.flags));
		}
		break; }

	case sMacroItem::MOUSE: {
		n = sprintf (desc, "마우스 ");
		if (item.mouse.flags & MOUSEEVENTF_MOVE) {
			n += sprintf (desc + n, "위치(%d, %d) ", item.mouse.x, item.mouse.y);
		}

		if (item.mouse.flags & MOUSEEVENTF_WHEEL) {
			n += sprintf (desc + n, "휠(%d) ", (int)(short)HIWORD(item.mouse.flags));
		}

		int flags = (item.mouse.flags>>1) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "왼버튼_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>3) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "오른버튼_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>5) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "중앙버튼_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>7) & 0x03;
		if (flags) {
			if (HIWORD(item.mouse.flags) == XBUTTON1) {
				n += sprintf (desc + n, "X1버튼_%s ", strMouseOption(flags));
			}
			if (HIWORD(item.mouse.flags) == XBUTTON2) {
				n += sprintf (desc + n, "X2버튼_%s ", strMouseOption(flags));
			}
		}
		break; }

	case sMacroItem::DELAY:
		n = sprintf (desc, "시간지연 %0.3f 초", (double)item.time.delay/1000.);
		break;
	}

	return desc;
}

