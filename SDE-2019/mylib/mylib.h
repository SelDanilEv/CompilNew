#pragma once

extern "C"
{
	char* _stdcall cleartxt(char* str1);
	int _stdcall textlenght(char* str1);
	int _stdcall sleep();
	char* _stdcall copytxt(char* str1, char* str2);
	char* _stdcall txtcon(char* str1, char* str2, char*buf);
	int __stdcall outtxt(char* value);
	int __stdcall outlit(int value);
}