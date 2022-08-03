#pragma once

struct VIRTUAL_KEY {
	int vk;
	const char *name;
	const char *desc;
};

extern VIRTUAL_KEY g_vk_list[];

extern int getVkIndex (int vk);
extern int GetVirtualKeyCode (int index);
extern const char *GetVirtualKeyDesc (int index);
extern const char *GetVirtualKeyDescFromVK (int vk);
extern const char *GetVirtualKeyNameFromVK (int vk);
