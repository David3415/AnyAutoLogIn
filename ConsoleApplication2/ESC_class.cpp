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
#include <openssl/md5.h>
#include "SelectFileClass.h"
#include "ESC_class.h"
#include <thread>

using namespace std;


void ESC_class::EscVoid() {
	SelectFileClass selectFileClass{};
	char key{};

	while (true) {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << this_thread::get_id() << '\n';
		/*if (GetAsyncKeyState(VK_F1))
		{
			PROCESSENTRY32 entry{};
			entry.dwSize = sizeof(PROCESSENTRY32);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);


			if (Process32First(snapshot, &entry) == TRUE)
			{
				while (Process32Next(snapshot, &entry) == TRUE)
				{
					if (_wcsicmp(entry.szExeFile, L"WndFolderWatcher.exe") == 0)
					{
						HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

						exit(0);

						CloseHandle(hProcess);
					}
				}
			}
		}
		else */if (GetAsyncKeyState(VK_F12))
		{
			selectFileClass.SelectFileVoid();
		}
	}
}