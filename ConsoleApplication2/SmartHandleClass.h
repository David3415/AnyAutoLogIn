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

template <typename T>
class SmartHandleClass
{
public:
	SmartHandle(HANDLE handle) ;
	~SmartHandle(); 
	operator bool();
	operator HANDLE();
	HANDLE handle();

private:
	HANDLE _handle;
};

