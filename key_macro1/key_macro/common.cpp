

#include "stdafx.h"

#pragma comment (lib, "Version.lib")

CString GetVersionInfo(HMODULE hLib, CString csEntry)
{
	CString csRet;

	if (hLib == NULL) hLib = AfxGetResourceHandle();

	HRSRC hVersion = FindResource( hLib, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION );
	if (hVersion != NULL) {
		HGLOBAL hGlobal = LoadResource( hLib, hVersion );
		if ( hGlobal != NULL) {

			LPVOID versionInfo = LockResource(hGlobal);
			if (versionInfo != NULL) {
				DWORD vLen,langD;
				BOOL retVal;

				LPVOID retbuf=NULL;
				static char fileEntry[256];
				sprintf(fileEntry,_T("\\VarFileInfo\\Translation"));

				retVal = VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen);
				if (retVal && vLen==4) {
					memcpy(&langD,retbuf,4);
					sprintf(fileEntry, _T("\\StringFileInfo\\%02X%02X%02X%02X\\%s"),
						(langD & 0xff00)>>8,langD & 0xff,(langD & 0xff000000)>>24,
						(langD & 0xff0000)>>16, csEntry);
				}
				else
					sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\%s", GetUserDefaultLangID(), (LPCTSTR)csEntry);

				if (VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen))
					csRet = (char*)retbuf;
			}
		}

		UnlockResource( hGlobal );
		FreeResource( hGlobal );
	}

	return csRet;
}

bool ApplicationAlreadyExist (char *WindowClass, char *Title)
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, Title);   // Create mutex
	switch(GetLastError()) {
	case ERROR_SUCCESS:
		break;
	case ERROR_ALREADY_EXISTS:
		return true;
	default:
		return false;
	}
	return false;
}

