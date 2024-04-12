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
#include "KeyboardLayoutClass.h"


void KeyboardLayoutClass::langSwitch() {
	HKL lang = GetKeyboardLayout(GetCurrentThreadId());///сменим раскладку на 
	wcout << LOWORD(lang) << '\t' << HIWORD(lang);
	if (LOWORD(lang) != 1033) {
		lang = LoadKeyboardLayout(L"0000409c", KLF_ACTIVATE);///
		PostMessage(GetConsoleWindow(), WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)lang);///
	}
}
