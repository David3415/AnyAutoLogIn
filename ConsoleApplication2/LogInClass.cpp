#pragma once
#ifdef UNICODE
#define tcout std::wcout
#elif
#define tcout std::cout
#endif // UNICODE
//#include <mmsystem.h> 
#pragma comment(lib, "Winmm.lib")
//#include "Mmsystem.h"
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
#include <openssl/md5.h>
#include <stdio.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<fstream>
#include <filesystem>
#include "ESC_class.h"
#include "OpenMyDocsClass.h"
#include "EngineClass.h"
#include "LoginClass.h"

using namespace std;

void LoginClass::logInVoid() {
	Sleep(2000);

	INPUT inputs0[1] = { 0 };
	ZeroMemory(inputs0, sizeof(inputs0));
	inputs0[0].type = INPUT_KEYBOARD;
	inputs0[0].ki.wVk = VK_RETURN;
	UINT uSent0 = SendInput(ARRAYSIZE(inputs0), inputs0, sizeof(INPUT));
	Sleep(1000);

	wstring str = L"Design4"s;
	int len = str.length();
	if (len == 0) return;

	std::vector<INPUT> in(len * 2);
	ZeroMemory(&in[0], in.size() * sizeof(INPUT));

	int i = 0, idx = 0;
	while (i < len)
	{
		WORD ch = (WORD)str[i++];

		if ((ch < 0xD800) || (ch > 0xDFFF))
		{
			in[idx].type = INPUT_KEYBOARD;
			in[idx].ki.wScan = ch;
			in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
			++idx;

			in[idx] = in[idx - 1];
			in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
			++idx;
		}
		else
		{
			in[idx].type = INPUT_KEYBOARD;
			in[idx].ki.wScan = ch;
			in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
			++idx;

			in[idx].type = INPUT_KEYBOARD;
			in[idx].ki.wScan = (WORD)str[i++];
			in[idx].ki.dwFlags = KEYEVENTF_UNICODE;
			++idx;

			in[idx] = in[idx - 2];
			in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
			++idx;

			in[idx] = in[idx - 2];
			in[idx].ki.dwFlags |= KEYEVENTF_KEYUP;
			++idx;
		}
	}
	SendInput(in.size(), &in[0], sizeof(INPUT));

	INPUT inputs2[1] = { 0 };
	ZeroMemory(inputs2, sizeof(inputs2));
	inputs2[0].type = INPUT_KEYBOARD;
	inputs2[0].ki.wVk = VK_RETURN;
	UINT uSent2 = SendInput(ARRAYSIZE(inputs2), inputs2, sizeof(INPUT));
	wstring sound_path = L"e:\\VS\\KeyLoger\\connected_sample.wav";
	//bool play= PlayFromTo(&sound_path[0], NULL, SND_FILENAME | SND_ASYNC);
	system("Pause");
};
