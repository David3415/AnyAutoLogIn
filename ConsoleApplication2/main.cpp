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
#include <conio.h>
#include <vector>
#include <windows.h>
#include <Tlhelp32.h>
#include <windowsx.h>
#include <algorithm>
#include <shobjidl.h> 
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <openssl/md5.h>
#include <stdio.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<fstream>
#include<thread>
#include <filesystem>
#include <condition_variable>
#include "ESC_class.h"
#include "OpenMyDocsClass.h"
#include "ESC_class.h"
#include "SelectFileDLGClass.h"
#include "KeyboardLayoutClass.h"

using namespace std;

int anyDeskWindowCounter{};

wstring my_string[5];
bool repeatCall = true;
mutex mtx;
//=============================================================================================================================
//================================================================= SmartHandle ==================================================
//=============================================================================================================================
class SmartHandle
{
public:
	SmartHandle(HANDLE handle) {
		_handle = handle;
	}
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
private:
	HANDLE _handle = NULL;
};

struct ProcessInfo
{
	PROCESSENTRY32 pe;
	vector<THREADENTRY32>threads;
};


//BOOL PlayFromTo(LPTSTR lpstrAlias, DWORD dwFrom, DWORD dwTo) {
//	return mciSendString(lpstrAlias, NULL, 0, NULL);
//	
//};



//=============================================================================================================================
//================================================================= logInVoid ==================================================
//=============================================================================================================================
void logInVoid() {
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
	//system("Pause");
	//exit(0);
}


//============================================================================================================================
//==============================================================   CALL MENU   ==================================================
//=============================================================================================================================
void CallMenu() {
	char openMenuChar{};
	SelectFileDLGClass selectFileDLGClass; unsigned int clockStartTime = 1;
	printf("2 sec to press \"a\ to call menu\"\n");
	while (true)//clockStartTime < 30000)
	{
		if (_kbhit()) {
			mtx.lock();
			cout << "!@#$%AAAAAAAA" << '\n';
			openMenuChar = _getch();
			if (openMenuChar == 97) {//|| openMenuChar == 244) {a
				SelectFileDLGClass selectFileDLGClass;
				selectFileDLGClass.SelectFileDLGVoid();
			}
			mtx.unlock();
		}
	}
}


//=============================================================================================================================
//================================================================= StartBat ==================================================
//=============================================================================================================================
void StartBat() {
	WinExec("c:\\Users\\dgagi\\Desktop\\StartAnyDesk.bat", SW_SHOW);
	Sleep(7000);
}


//=============================================================================================================================
//================================================================= Engine ==================================================
//=============================================================================================================================

int Engine() {
	
	StartBat();
	vector<ProcessInfo>processInfos;
	vector<THREADENTRY32>threads;
	while (true) {
		cout << "running" << '\n';
		processInfos.clear();
		threads.clear();
		cout << "!@#$% " << this_thread::get_id() << '\n';
		Sleep(3000);
		SmartHandle processSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
		SmartHandle threadSnap(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0));
		if (!processSnap || !threadSnap) {
			return 1;
		}



		THREADENTRY32 te{ sizeof(THREADENTRY32) };
		if (Thread32First(threadSnap, &te) == FALSE)
		{
			return 2;
		}
		do {
			threads.push_back(te);
		} while (Thread32Next(threadSnap, &te));

		PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };
		if (Process32First(processSnap, &pe) == FALSE)
		{
			return 2;
		}
		do {
			vector<THREADENTRY32>subThreads;
			for (const auto& thread : threads) {
				if (thread.th32OwnerProcessID == pe.th32ProcessID) {
					subThreads.push_back(thread);
				}
			}
			processInfos.push_back(ProcessInfo{ pe,subThreads });//=================== selected threads vec
		} while (Process32Next(processSnap, &pe));

		int processCounter = 0;

		for (const auto& processInfo : processInfos) {
			int threadsCounter = 0;
			//tcout << "     " << processInfo.pe.szExeFile << endl;
			if (processInfo.pe.szExeFile == L"AnyDesk.exe"s) {
				tcout << endl << "processCounter: " << processCounter << "    " << endl;
				//tcout << "!!!!!"<<endl;
				for (const auto& thread : processInfo.threads) {

					tcout << "     " << threadsCounter << "   " << thread.th32ThreadID << "  " << processInfo.pe.th32ProcessID << endl;
					threadsCounter++;
				}
				if (processCounter == 2) {
					//ConnectVoid(processInfo);
					tcout << '\n' << "proc to kill " << processInfo.pe.th32ProcessID << endl;

					if (processInfo.threads.size() < 29) {
						StartBat();
						//
						tcout << endl << "processInfo.threads.size()::" << processInfo.threads.size() << endl;
						HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, true, processInfo.pe.th32ProcessID);
						int boolTermProcRes = TerminateProcess(hProcess, 0);
						int Error = GetLastError();
						repeatCall = true;
						tcout << '\n' << "boolTermProcRes: " << boolTermProcRes << "   Error: " << Error << endl;

					}
					else {
						if (repeatCall) {
							tcout << "SUCCESS";
							logInVoid();
							repeatCall = false;
							//processCounter--;
						}
						cout << "!@#$%" << '\n';
						//return 1;
					}
				}
				processCounter++;
			}
			//tcout << "     " << thread.th32ThreadID << endl;
			anyDeskWindowCounter++;
			//tcout << '\n' << "__END__" << endl;
		}

	}
	return 0;
}


//=============================================================================================================================================
//================================================================= MAIN =====================================================
//=============================================================================================================================================
int main() {
	//----------------------------switch KeyBoard Layout to ENG -----------------------
	KeyboardLayoutClass::langSwitch();

	//----------------------------CHECK FOR EXISTING DB WHITH PATH, LOGIN, PASS ----------------------------
	OpenMyDocsClass openMyDocsClass;
	openMyDocsClass.OpenMyDocsVoid();

	//----------------------------STARTING MAIN ENGINE ---------------------------------------------------
	thread EngineThread(&Engine);


	//----------------------------STARTING THREAD FOR MENU  --------------------------------------------
	thread ThreadMenu(&CallMenu);

	EngineThread.join();
	ThreadMenu.join();

	/*thread esc_thread=ESC_class esc_class{};
	esc_class.EscVoid();*/
	/*int res = 0;
	while (res == 0)
	{
		anyDeskWindowCounter = 0;
		res = Engine();
	}
	logInVoid();*/
}



