#pragma once
#include <Windows.h>
#include "ShellAPI.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

class OldNewValStructClass
{
public:
	OldNewValStructClass() { };
	struct OldValStruct
	{
		wstring struct_user;
		int struct_user_id;
		wstring struct_user_pass;
	};
	struct NewValStruct
	{
		wstring struct_user;
		int struct_user_id;
		wstring struct_user_pass;
	};
	BOOL GetTextVoid(HWND _hWnd, TCHAR* _char);
	wchar_t* SetTextVoid(HWND _hWnd1, HWND _hWnd2);
	TCHAR* _char1; TCHAR* _char2;
	vector<OldValStruct>oldValStructVec{1};
	vector<NewValStruct>newValStructVec{1};
	LPSTR oldVal;
	const int len = {};
};