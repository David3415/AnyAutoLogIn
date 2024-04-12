#pragma once
#ifdef UNICODE
#define tcout std::wcout
#elif
#define tcout std::cout
#endif // UNICODE

#include <Windows.h>
#include "ShellAPI.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <Tlhelp32.h>
#include <windowsx.h>
#include <algorithm>
#include <shobjidl.h> 
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

class SelectFileDLGClass
{
public:

	int SelectFileDLGVoid();
	static LRESULT CALLBACK SelectFileDLGCallback(HWND hWndSet, UINT uMsgSet, WPARAM wParam, LPARAM lParam);
	struct oldValStruct
	{
		int struct_id;
		wstring struct_user;
		int struct_user_id;
		wstring struct_user_pass;
	};
	vector<oldValStruct>oldValStructVec;
};
