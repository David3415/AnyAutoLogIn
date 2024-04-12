#include <Windows.h>
#include <iostream>
#include<fstream>
#include <filesystem>
#include <string>
#include <TCHAR.h>
#include <stdio.h>
#include <strsafe.h>
#include "ESC_class.h"
#include "OpenMyDocsClass.h"
#include "SearchFileClass.h"
#include "SelectFileDLGClass.h"
#include "CheckEmptyFileClass.h"
#include <thread>
#include <mutex>


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
using namespace std;

mutex _mutex;
SelectFileDLGClass selectFileDLGClass;
CheckEmptyFileClass checkEmptyFileClass;
void OpenMyDocsClass::UpdateDelay() {

	//my_documents[MAX_PATH] = { 'd' };
}

void OpenMyDocsClass::OpenMyDocsVoid() {



	//WCHAR my_documents[MAX_PATH] = { };// 
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) {
		std::cerr << "Error: \"my_documents\" folder is inaccessible" << result << "\n";
		system("pause");
		exit(0);
	}

	//L"c:\\Users\\dgagi\\Desktop\\KeyLoger.txt"s
	wcscat_s(my_documents, L"\\KeyLogerDB3.txt");
	wfstream _fin;

	if (!filesystem::exists(my_documents)) {
		cout << '\n' << "docsFileOpenErr!" << '\n' << "file KeyLogerDB.txt doesn't exists" << '\n';
		cout << "Wanna create? y/n" << '\n';
		char createFileBool;
		cin >> createFileBool;
		if (createFileBool == 'n') {
			exit(0);
		}

		const TCHAR szKeyLogerFileName[] = L"KeyLogerDB.dat";
		if (createFileBool == 'y') {

			HANDLE hFile = CreateFile(my_documents, GENERIC_READ, 0, NULL,
				CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

			if (INVALID_HANDLE_VALUE == hFile) {
				_tprintf(TEXT("App failure"));
				CloseHandle(hFile);
				return;
			}
			if (!hFile) {
				cout << "hFile was not created";
				CloseHandle(hFile);
				return;
			};
			CloseHandle(hFile);
		}
		_mutex.lock();

		cout << '\n' << "this_thread::id: " << this_thread::get_id();

		thread th_SFDC(&SelectFileDLGClass::SelectFileDLGVoid, selectFileDLGClass);
		th_SFDC.join();
		_mutex.unlock();
		_fin.close();
	}
	else {
		bool check = checkEmptyFileClass.CheckEmptyFileVoid(my_documents);
		if (!check) {
			_mutex.lock();
			cout << '\n' << "this_thread::id: " << this_thread::get_id();
			thread th_SFDC(&SelectFileDLGClass::SelectFileDLGVoid, selectFileDLGClass);
			th_SFDC.join();
			_mutex.unlock();
		}
	}

};



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
