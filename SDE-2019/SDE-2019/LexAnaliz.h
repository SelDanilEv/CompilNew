#pragma once

namespace LexA
{
	void analyze(int currentLine, char *fulltextch);

	struct Tables
	{
		LT::LexTable mylextable;
		IT::IdTable myidtable;
	};
}