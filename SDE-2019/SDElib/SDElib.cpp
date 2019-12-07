#include "pch.h"
#include "SDElib.h"
#include <iostream>
#include <math.h>
#include <Windows.h>

#pragma warning(disable: 4996)

extern "C"
{
	char* _stdcall textcopy(char* str1, char* str2)
	{
		if (!str1 || !str2)
		{
			std::cout << "ERROR: Null string pointer in textcopy function!" << std::endl;
			system("pause");
			return NULL;
		}
		else
			return strcpy(str1, str2);
	}

	int _stdcall textlenght(char* str)
	{
		if (!str)
		{
			std::cout << "ERROR: Null string pointer in textcopy function!" << std::endl;
			system("pause");
		}
		std::string stri = str;  // сработает только если str имеет \0
		return stri.length();
	}

	void _stdcall outtxt(char* s)
	{
		if (s != nullptr)
			std::cout << s << std::endl;
		else
			std::cout << "Empty line!";
	}
	void _stdcall outlit(int i)
	{
		std::cout << i << std::endl;
	}
}