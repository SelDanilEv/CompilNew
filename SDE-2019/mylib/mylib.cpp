#include "stdafx.h"
#include "mylib.h"
#include <iostream>
#include <Windows.h>
#pragma warning(disable: 4996)


extern "C"
{
	char* _stdcall cleartxt(char* str1)
	{
		short i = 0;
		while (*(str1 + i) != NULL)
		{
			*(str1 + i) = NULL;
			i++;
		}
		return str1;
	}

	int _stdcall textlenght(char* str1) {
		int i=0;
		while (*(str1 + i) != NULL)
		{
			
			i++;
		}
		return i;
	}

	int _stdcall sleep() {
		system("pause");
		return 1;
	}

	char* _stdcall copytxt(char* str1, char* str2)
	{
		return strcpy(str1, str2);
	}

	char* _stdcall txtcon(char* str1, char* str2, char*buf)
	{
		strcpy(buf, str2);
		strcat(buf, str1);
		return buf;
	}

	int __stdcall outtxt(char* value)
	{
		std::cout << value << std::endl;
		return 1;
	}

	int __stdcall outlit(int value)
	{
		std::cout << value << std::endl;
		return 1;
	}
}