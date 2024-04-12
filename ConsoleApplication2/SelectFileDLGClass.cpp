#ifdef UNICODE
#define tcout std::wcout
#elif
#define tcout std::cout
#endif // UNICODE
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "ShellAPI.h"
#include <string>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h>
#include <Tlhelp32.h>
#include <windowsx.h>
#include <algorithm>
#include <shobjidl.h> 
#include <shlobj.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <processthreadsapi.h>
#include "SelectFileDLGClass.h"
#include "SelectFileClass.h"
#include "OpenMyDocsClass.h"
#include "OldNewValStructClass.h"



constexpr auto hOK = 1010;
constexpr auto hEditButt = 1009;
using namespace std;

#define LOGINSIZE 10
#define PASSSIZE 10

OldNewValStructClass oldNewValStructClass;
wchar_t my_documents[MAX_PATH];
SelectFileClass selectFileClass;
OpenMyDocsClass openMyDocsClass;
POINT pt{};
bool oldTextBool = false;
wstring oldText;//  old text

//extern wstring my_string[5];
HWND hWndID[5]{};
HWND hWndUser[5]{};
HWND hWndUserID[5]{};
HWND hWndPass[5]{};
HWND hWndOK{};
HWND hWndEditButt{};

LPWSTR temp{};


char* buffer1{};

bool CheckCellVal(HWND _hWnd, LPWSTR val) {
	wstring tempVal = val;
	if (tempVal.size() != LOGINSIZE - 1) {
		MessageBoxW(NULL, L"Input 9-digit number", L"Err", 0);
		return 0;

	}
	return 1;
};

bool EditEnableVoid() {


	return 1;
}

LRESULT CALLBACK SelectFileDLGClass::SelectFileDLGCallback(HWND hWndSet, UINT uMsgSet, WPARAM wParam, LPARAM lParam) {
	wfstream _fout{};
	int g = 0;
	LPWSTR szFile = NULL;
	LPWSTR szSelectedFile{};
	HWND hwndOwner = NULL;
	wchar_t str[20];
	wstring my_string1[3];
	//my_documents[MAX_PATH] = {'f'};

	LPWSTR newVal1{}, newVal2{}, newVal3{};


	switch (wParam) {
	case hOK:
	{
		_fout.open(my_documents, fstream::in | fstream::out | fstream::trunc);
		if (!_fout.is_open()) {
			cout << '\n' << "WriteFileErr!" << '\n';
		};

		wchar_t* id_pass_w = oldNewValStructClass.SetTextVoid(hWndUserID[0], hWndPass[0]);

		/*char space[] = "S";
		char* p_space = space;*/

		//
		int len_IdPass = wcslen(id_pass_w);// кол. символов id_pass_w
		char* id_pass = (char*)malloc(len_IdPass + 1);//выделение памяти указателю на рез-т конвертации id_pass_w

		wcstombs(id_pass, id_pass_w, len_IdPass + 1); //Сама  конвертация id_pass_w


		int len_temp = strlen(buffer1);
		char* commonStr = (char*)malloc(len_temp + len_IdPass + 1);


		memcpy(commonStr, buffer1, len_temp + 1);
		//memcpy(commonStr + len_temp, p_space, 1);
		memcpy(commonStr + len_temp, id_pass, len_IdPass + 1);

		_fout << commonStr;
		_fout.close();
		//SendMessage(hWndSet, WM_CLOSE, 0, 0);
		PostMessage
		(
			hWndSet, WM_QUIT, wParam, lParam
		);

		/*DestroyWindow(hWndSet);
		PostQuitMessage(0);*/

		return 0;
	};
	break;
	}

	switch (uMsgSet)
	{
	case WM_CREATE:
	{
		for (int i = 0; i < 5; i++) {
			_itow(i + 1, str, 10);
			hWndID[i] = CreateWindowExW(0, L"EDIT", str, // 
				WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
				30, 40 + i * 40, 30, 30, hWndSet, reinterpret_cast<HMENU>(1001), NULL, NULL);

		}
		for (int i = 0; i < 1; i++) {
			hWndUser[i] = CreateWindowExW(0, L"EDIT", L"", // 
				WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
				70, 40 + i * 40, 400, 30, hWndSet, reinterpret_cast<HMENU>(1002), NULL, NULL);
		}
		//for (int i = 0; i < 5; i++) {
		hWndUserID[0] = CreateWindowExW(0, L"EDIT", L"", // 
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
			480, 40, 130, 30, hWndSet, reinterpret_cast<HMENU>(1003), NULL, NULL);

		//	for (int i = 0; i < 5; i++) {
		hWndPass[0] = CreateWindowExW(0, L"EDIT", L" ", // 
			WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
			620, 40, 130, 30, hWndSet, reinterpret_cast<HMENU>(1004), NULL, NULL);

		hWndEditButt = CreateWindowExW(0, L"BUTTON", L"EDIT ", // 
			WS_CHILD | WS_VISIBLE | BS_FLAT,
			550, 240, 90, 30, hWndSet, reinterpret_cast<HMENU>(1009), NULL, NULL);
		hWndOK = CreateWindowExW(0, L"BUTTON", L"OK ", // 
			WS_CHILD | WS_VISIBLE | BS_FLAT,
			660, 240, 90, 30, hWndSet, reinterpret_cast<HMENU>(1010), NULL, NULL);

		return 0;
	}
	break;

	/*case WM_DESTROY:
	{
		PostQuitMessage(0);
	}*/

	case WM_COMMAND:
	{
		if ((HIWORD(wParam) == EN_KILLFOCUS))// && (LOWORD(wParam) == hWndPass[0]))
		{
			TCHAR buf1[LOGINSIZE];
			GetWindowTextW(hWndUserID[0], buf1, LOGINSIZE);
			CheckCellVal(hWndUserID[0], buf1);
		}
		break;

	case WM_LBUTTONUP:
	{
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		//if (oldTextBool == false) {
		//	/*oldText = my_string[0];
		//	oldTextBool = true;*/
		//};

		if (pt.x > 70 && pt.x < 410 && pt.y>40 && pt.y < 80) {
			temp = selectFileClass.SelectFileVoid();
			size_t sz_temp = wcslen(temp);
			buffer1 = (char*)malloc(sz_temp + 10);
			wcstombs(buffer1, temp, sz_temp + 1);
			SetWindowTextA(hWndUser[0], buffer1);
			break;
		}
		if (pt.x > 480 && pt.x < 600 && pt.y>40 && pt.y < 80) {
			TCHAR buf[LOGINSIZE];
			Edit_Enable(hWndUserID[0], true);
			oldNewValStructClass.GetTextVoid(hWndUserID[0], buf);

			break;
		}
		if (pt.x > 610 && pt.x < 800 && pt.y>40 && pt.y < 80) {
			TCHAR buf[PASSSIZE];
			oldNewValStructClass.GetTextVoid(hWndPass[0], buf);
			Edit_Enable(hWndPass[0], true);
			break;
		}
	};
	return 0;
	}

	}
	return DefWindowProc(hWndSet, uMsgSet, wParam, lParam);
};


int SelectFileDLGClass::SelectFileDLGVoid() {

	HINSTANCE histanceSet = GetModuleHandleW(NULL);
	WNDCLASSEX wclassSet = { 0 };          //Обнуляем структуру с самого начала, так как заполнять будем не все поля.
	wclassSet.cbSize = sizeof(WNDCLASSEX);      //По размеру структуры Windows определит, какая версия API была использована.
	wclassSet.style = CS_HREDRAW | CS_VREDRAW;    //Говорим окну перерисовываться при изменении размеров окна.
	wclassSet.lpfnWndProc = &SelectFileDLGClass::SelectFileDLGCallback;      //Указываем функцию обработки сообщений.
	wclassSet.hCursor = LoadCursor(NULL, IDC_ARROW);
	wclassSet.hInstance = histanceSet;        //Указываем хендл приложения.
	wclassSet.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW);    //GetStockObject возвращает хендл на белую кисточку, для фона окна
	wclassSet.lpszClassName = L"SELFILEFORM";      //Имя данного класса, должно быть уникальным, иначе, если класс с таким именем уже зарегестрирован, то в регистрации будет отказано.
	//Регистрируем класс окна.
	RegisterClassEx(&wclassSet);

	HWND hWndSet = CreateWindowExW(
		0,
		L"SELFILEFORM",                //Имя класса.
		L"Settings",                //Заголовок окна.
		WS_SYSMENU,          //Тип окна, влияет на отображение системного меню, кнопок в верхнем правом углу и т.п.
		150, 115,                  //Координаты окна.
		800, 320,                //Ширина окна.
		0,                    //Ссылка на родительское окно.
		0,                    //Хендл меню.
		histanceSet,                //Хендл приложения, получаем его функцией GetModuleHandleW.
		0
	);
	ShowWindow(hWndSet, SW_SHOW);
	UpdateWindow(hWndSet);

	MSG uMsgSet = {};
	while (GetMessage(&uMsgSet, hWndSet, 0, 0)) {
		TranslateMessage(&uMsgSet);  //Преобразуем виртуальную клавишу в ASCII-код и посылаем сообщение WM_CHAR (тут не нужно.Необходимо, если надо работать с текстом, вводимым с клавиатуры)
		DispatchMessage(&uMsgSet);  //Передаем сообщения для обработки в "главную функцию обработки сообщений"
	}
	return static_cast<int>(uMsgSet.wParam);
}