#pragma once
#include <Windows.h>
#include <iostream>
#include<fstream>
#include <filesystem>
#include "ESC_class.h"
extern WCHAR my_documents[MAX_PATH];//
using namespace std;
//static  WCHAR my_documents1[MAX_PATH];
class  OpenMyDocsClass {
public:
	void UpdateDelay();
	void OpenMyDocsVoid();
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
};
