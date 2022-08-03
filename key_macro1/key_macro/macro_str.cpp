#include "StdAfx.h"
#include "macro_def.h"
#include "virtual_key.h"

const char *strKeyboardOption (int flags)
{
	switch(flags) {
	case 0: return "";
	case 1: return "������";
	case 2: return "����";
	case 3: return "";
	default: return "(����)";
	}
}

const char *strMouseOption (int flags)
{
	switch(flags) {
	case 0: return "";
	case 1: return "������";
	case 2: return "����";
	case 3: return "Ŭ��";
	default: return "(����)";
	}
}

const char *GetItemDescription (const sMacroItem &item)
{
	int n = 0;
	static char desc[256];
	desc[0] = '\0';

	switch (item.type) {
	case sMacroItem::NONE: 
		n = sprintf (desc, "(����)");
		break;

	case sMacroItem::KEY: {
		int index = getVkIndex(item.key.vk);
		n = sprintf (desc, "Ű���� %s ", GetVirtualKeyDesc(index));
		if (item.key.flags) { 
			n += sprintf (desc + n, "%s", strKeyboardOption(item.key.flags));
		}
		break; }

	case sMacroItem::MOUSE: {
		n = sprintf (desc, "���콺 ");
		if (item.mouse.flags & MOUSEEVENTF_MOVE) {
			n += sprintf (desc + n, "��ġ(%d, %d) ", item.mouse.x, item.mouse.y);
		}

		if (item.mouse.flags & MOUSEEVENTF_WHEEL) {
			n += sprintf (desc + n, "��(%d) ", (int)(short)HIWORD(item.mouse.flags));
		}

		int flags = (item.mouse.flags>>1) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "�޹�ư_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>3) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "������ư_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>5) & 0x03;
		if (flags) {
			n += sprintf (desc + n, "�߾ӹ�ư_%s ", strMouseOption(flags));
		}
		flags = (item.mouse.flags>>7) & 0x03;
		if (flags) {
			if (HIWORD(item.mouse.flags) == XBUTTON1) {
				n += sprintf (desc + n, "X1��ư_%s ", strMouseOption(flags));
			}
			if (HIWORD(item.mouse.flags) == XBUTTON2) {
				n += sprintf (desc + n, "X2��ư_%s ", strMouseOption(flags));
			}
		}
		break; }

	case sMacroItem::DELAY:
		n = sprintf (desc, "�ð����� %0.3f ��", (double)item.time.delay/1000.);
		break;
	}

	return desc;
}

