#pragma once

template <typename T>
T BOUND (T value, T lo, T hi)
{
	if (value < lo) value = lo;
	if (value > hi) value = hi;
	return value;
}

inline int ROUND (double x)
{
	if (x > 0.) return (int)(x + 0.5);
	if (x < 0.) return (int)(x - 0.5);
	return 0;
}

inline void ScreenDependentMousePos (int &mx, int &my)
{
	mx = (int)(mx*GetSystemMetrics(SM_CXSCREEN)/65536.);
	my = (int)(my*GetSystemMetrics(SM_CYSCREEN)/65536.);
}

inline void ScreenIndependentMousePos (int &mx, int &my)
{
	mx = (mx > 0) ? 
		(int)((mx+0.5)*65536./GetSystemMetrics(SM_CXSCREEN)) : 
		(int)((mx-0.5)*65536./GetSystemMetrics(SM_CXSCREEN)) ;
	my = (my > 0) ? 
		(int)((my+0.5)*65536./GetSystemMetrics(SM_CYSCREEN)) : 
		(int)((my-0.5)*65536./GetSystemMetrics(SM_CYSCREEN)) ;
}

extern CString GetVersionInfo(HMODULE hLib, CString csEntry);
extern bool ApplicationAlreadyExist (char *WindowClass, char *Title);
