#include "pch.h"
#include "LexAnaliz.h"
#include "Log.h"

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
	}

	void WriteFiles(LexA::Tables tables, std::ofstream& filetrace)
	{
		filetrace << "\n\n";
		std::ofstream fileLT;               //формрирование файлов таблиц
		fileLT.open("LT.txt");
		LT::showTable(tables.mylextable, fileLT);
		LT::showTable(tables.mylextable, filetrace);
		fileLT.close();
		filetrace << "\n\n";
		std::ofstream fileLT_mini;
		fileLT_mini.open("LT_mini.txt");
		LT::showTable_mini(tables.mylextable, fileLT_mini);
		LT::showTable_mini(tables.mylextable, filetrace);
		fileLT_mini.close();
		filetrace << "\n\n";
		std::ofstream fileIT;
		fileIT.open("IT.txt");
		IT::showTable(tables.myidtable, fileIT);
		IT::showTable(tables.myidtable, filetrace);
		fileIT.close();
		filetrace << "\n\n";

	}

	void WriteFiles(LexA::Tables tables, Log::LOG& log)
	{
		*log.stream << "\n\n";
		std::ofstream fileLT;               //формрирование файлов таблиц
		fileLT.open("LT.txt");
		LT::showTable(tables.mylextable, fileLT);
		LT::showTable(tables.mylextable,*log.stream);
		fileLT.close();
		*log.stream << "\n\n";
		std::ofstream fileLT_mini;
		fileLT_mini.open("LT_mini.txt");
		LT::showTable_mini(tables.mylextable, fileLT_mini);
		LT::showTable_mini(tables.mylextable, *log.stream);
		fileLT_mini.close();
		*log.stream << "\n\n";
		std::ofstream fileIT;
		fileIT.open("IT.txt");
		IT::showTable(tables.myidtable, fileIT);
		IT::showTable(tables.myidtable, *log.stream);
		fileIT.close();
		*log.stream << "\n\n";
	}
}