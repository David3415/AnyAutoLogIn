#include <Windows.h>
#include "ShellAPI.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include "CheckEmptyFileClass.h"


 bool CheckEmptyFileClass::CheckEmptyFileVoid(wstring path) {
	wfstream _fin;
	_fin.open(path, wfstream::in | wfstream::out | wfstream::app);
	wstring _temp{};
	getline(_fin, _temp);
	if (count(_temp.begin(), _temp.end(), ' ') != 2) {
		//wcout << L"err";
		return 0;
	}
	return 1;
};