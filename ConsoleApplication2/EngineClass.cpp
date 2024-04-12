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
#include "ConsoleApplication2.cpp"

using namespace std;


void StartBat() {
	WinExec("c:\\Users\\dgagi\\Desktop\\StartAnyDesk1.bat", SW_SHOW);
	Sleep(7000);
};

int EngineClass::EngineVoid() {
	StartBat();
	SmartHandle processSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	SmartHandle threadSnap(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0));
	if (!processSnap || !threadSnap) {
		return 1;
	}

	vector<ProcessInfo>processInfos;
	vector<THREADENTRY32>threads;

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

				Sleep(5000);
				if (processInfo.threads.size() < 27) {
					tcout << endl << "processInfo.threads.size()::" << processInfo.threads.size() << endl;
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, true, processInfo.pe.th32ProcessID);
					int boolTermProcRes = TerminateProcess(hProcess, 0);
					int Error = GetLastError();
					tcout << '\n' << "boolTermProcRes: " << boolTermProcRes << "   Error: " << Error << endl;
				}
				else {

					tcout << "SUCCESS";
					return 1;
				}
			}
			processCounter++;
		}
		//tcout << "     " << thread.th32ThreadID << endl;
		anyDeskWindowCounter++;
		//tcout << '\n' << "__END__" << endl;
	}
	return 0;
}
