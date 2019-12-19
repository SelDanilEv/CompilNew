#include "pch.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE) throw ERROR_THROW(110);
		LexTable Table;
		Table.maxsize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size > lextable.maxsize) throw ERROR_THROW(111);
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}

	void showTable(LexTable lextable, std::ofstream &file)		// вывод таблицы лексем
	{
		file << std::setfill('=')<<std::setw(25)<<"LEX TABLE"<<std::setw(16)<<"\n\n";
		file <<"Num"<< std::setfill(' ') << std::setw(10)<<"Line"<<std::setw(9)<<"Lexema"<<std::setw(13)<<"ID in IT"<<std::setw(9)<<"value"<< "\n\n";
		for (int i = 0; i < lextable.size; i++)
		{
			file << std::setw(3) << i << std::setfill(' ') << std::setw(8) << lextable.table[i].sn+1 <<
				std::setw(8) << lextable.table[i].lexema << std::setw(13);
			if(lextable.table[i].idxTI != LT_TI_NULLIDX)
				file<< lextable.table[i].idxTI;
			else
				file << ' ';
			file << std::setw(11) << lextable.table[i].value << std::setw(20);
			file << std::endl;
		}
	}

	void showTable_mini(LexTable lextable, std::ofstream &file)
	{
		file << std::setfill('=')  << std::setw(25) << "LEX TABLE mini" << std::setw(16) << "\n\n";
		short line = 0;
		for (int i = 0; i < lextable.size; i++)
		{
			while (lextable.table[i].sn != line) 
			{
				line++;
				file << '\n';
			}
			file << lextable.table[i].lexema ;
		}
	}
}