#include "stdafx.h"
#include <iostream>

extern "C"
{
	char*  _stdcall copytxt(char* str1, char* str2)
	{
			return strcpy(str1, str2);
	}

	char* _stdcall txtcon(char* str1, char* str2)
	{
		char* buf = new char[255];
		strcpy(buf, str2);
		strcat(buf, str1);
		return buf;
	}

	int __stdcall outtxt(char* value)
	{
		setlocale(0, "");
		std::cout << value << std::endl;
		return 0;
	}

	int __stdcall outlit(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
}