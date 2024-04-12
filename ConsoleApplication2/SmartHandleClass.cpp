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
#include "SmartHandleClass.h"

using namespace std;

template <typename T>
SmartHandleClass::SmartHandle(HANDLE handle)
{
	_handle = handle;

}
template <typename T>

	~SmartHandle() {
		if (_handle) {
			CloseHandle(_handle);
		}
	}
	operator bool() {
		return _handle != 0;
	}
	operator HANDLE() {
		return _handle;
	}
	HANDLE handle()
	{
		return _handle;
	}

	HANDLE _handle = NULL;

}
struct ProcessInfo
{
	PROCESSENTRY32 pe;
	vector<THREADENTRY32>threads;
};