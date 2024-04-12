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

using namespace std;

class LoginClass
{
public:
	void logInVoid();
	INPUT inputs0[1];
	UINT uSent0;
	wstring str;
	int len;
	//vector<INPUT> in(len * 2);
	int i, idx;
	WORD ch;
	INPUT inputs2[1] ;
	UINT uSent2;
	wstring sound_path;
};