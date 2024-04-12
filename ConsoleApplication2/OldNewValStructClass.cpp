#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "ShellAPI.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h>
#include <malloc.h>
#include "OldNewValStructClass.h"
#define LOGINSIZE 10
#define PASSSIZE 10
using namespace std;

BOOL OldNewValStructClass::GetTextVoid(HWND _hWnd, TCHAR* _char) {
	LPSTR oldVal{};
	const int len = GetWindowTextLengthW(_hWnd);
	cout << len << ":";
	GetWindowTextW(_hWnd, _char, LOGINSIZE);
	oldValStructVec[0].struct_user_id = (int)&_char;
	//tcout << _char << "!@#%$";
	//SetWindowTextA(hWndUserID[0], (LPCSTR)&buffer);
	return true;
};
wchar_t* OldNewValStructClass::SetTextVoid(HWND _hWnd1, HWND _hWnd2) {
	wchar_t _char1[LOGINSIZE];
	wchar_t _char2[LOGINSIZE];
	wchar_t _spaceChar[1] = { ' ' };

	//const int len_spaceChar0 = sizeof(_spaceChar);
	const int len1 = GetWindowTextLengthW(_hWnd1);
	const int len2 = GetWindowTextLengthW(_hWnd2);

	GetWindowTextW(_hWnd1, _char1, LOGINSIZE);
	GetWindowTextW(_hWnd2, _char2, LOGINSIZE);



	int len_spaceChar = wcslen(_spaceChar);
	int lena = wcslen(_char1);
	int lenb = wcslen(_char2);


	wchar_t* temp_char = (wchar_t*)malloc(lena + lenb +1);

	wchar_t* p_spaceChar = _spaceChar;

	wchar_t* p_char1 = _char1;
	wchar_t* p_char2 = _char2;

	wmemcpy(temp_char, p_spaceChar, 1);
	wmemcpy(temp_char + 1, p_char1, lena + 1);
	wmemcpy(temp_char + lena + 1, p_char2, lenb + 1);
	//wcstombs(res_char, temp_char, 500);
//newValStructVec[0].struct_user_id = (int)&_char1;
//tcout << _char << "!@#%$";
//SetWindowTextA(hWndUserID[0], (LPCSTR)&buffer);
	wchar_t* out = temp_char;
	return out;
};


