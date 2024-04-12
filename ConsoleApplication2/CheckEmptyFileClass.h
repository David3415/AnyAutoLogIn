#pragma once
#include <Windows.h>
#include "ShellAPI.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
class CheckEmptyFileClass
{
public:
	bool CheckEmptyFileVoid(wstring path);
	wfstream _fin;
};