#include "pch.h"
#include "LexAnaliz.h"

namespace FilesManager
{
	void WriteFiles(LexA::Tables tables)
	{
		std::ofstream fileLT;               //формрирование файлов таблиц
		fileLT.open("LT.txt");
		LT::showTable(tables.mylextable, fileLT);
		fileLT.close();

		std::ofstream fileLT_mini;
		fileLT_mini.open("LT_mini.txt");
		LT::showTable_mini(tables.mylextable, fileLT_mini);
		fileLT_mini.close();

		std::ofstream fileIT;
		fileIT.open("IT.txt");
		IT::showTable(tables.myidtable, fileIT);
		fileIT.close();

		std::cout << "\nFiles created\n\n";
	}
}