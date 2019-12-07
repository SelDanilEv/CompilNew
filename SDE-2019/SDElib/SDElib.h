#pragma once

extern "C"
{
	char* _stdcall copystr(char*, char*);
	int _stdcall textlenght(char* str);
	void _stdcall outtxt(char*);
	void _stdcall outlit(int);
}