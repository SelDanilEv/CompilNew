#pragma once

namespace LexA
{
	void analyze(int currentLine, char *fulltextch);
<<<<<<< HEAD
	struct Tables
	{
		IT::IdTable idtable;
		LT::LexTable lextable;
=======

	struct Tables
	{
		LT::LexTable mylextable;
		IT::IdTable myidtable;
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
	};
}