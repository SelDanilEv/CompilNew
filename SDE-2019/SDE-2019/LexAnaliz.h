#pragma once
#define MAXSIZEIDENTIFICATOR 10

namespace LexA
{
	struct Tables
	{
		LT::LexTable mylextable;
		IT::IdTable myidtable;
	};

	Tables analyze(int currentLine, char *fulltextch);
}