#include <Windows.h>
#include <iostream>
#include<fstream>
#include <filesystem>
#include <string>
#include "ESC_class.h"
#include "OpenMyDocsClass.h"
#include "SearchFileClass.h"

using namespace std;
namespace fs = std::filesystem;

void SearchFileClass::SearchFileVoid() {
	static const char* chFolderpath = "C:\\*";  // no need to copy this into a buffer, just use a const
	string data;  // you new data buffer

	HANDLE hFind;
	WIN32_FIND_DATAA data2; // <- WIN32_FIND_DATAA if using char strings (instead of TCHAR strings)

	hFind = FindFirstFileA(chFolderpath, &data2);  // <- FindFirstFileA if using char strings (instead of TCHAR strings)

	
	if (hFind != INVALID_HANDLE_VALUE)
	{
		// at this point, 'data2' actually contains the first entry, so you don't want to call FindNextFile until
		//  you record it.  A do/while loop is more appropriate than a while loop for this reason:
		do
		{
			if (data2.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				data += "<DIR>";  // strings use += instead of strcat

			data += data2.cFileName;
			data += '\n'; // you really only need '\n'.  \r\n is just for outputting to windows controls, really
		} while (FindNextFileA(hFind, &data2));  // FindNextFileA if using char strings (instead of TCHAR strings)

		FindClose(hFind);  // don't forget to close it when you're done!
	}
	//system("pause");
};