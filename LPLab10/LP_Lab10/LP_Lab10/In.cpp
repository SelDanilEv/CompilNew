#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include <fstream>
#include <string>
#include <iostream>

namespace In
{
	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		std::string onestr;
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };					// инициализация
		std::ifstream in(infile);									// чтения
		std::ofstream out(outfile);									// записи
		if (!out.is_open())											
			throw ERROR_THROW(110);
		if (!in.is_open())										
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())											//пока открыт файл
		{
			Info.lines++;											//кол-во линий
			std::getline(in, temp);									//запись tеmp
			temp += "\n";											//знак окончания строки
			fulltext += temp;
		}
		Info.text = new unsigned char[fulltext.size() + 1];			//выделяем память 
		unsigned char * Ptemp = Info.text;							//указатель на начало
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F) 
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I) 
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] == IN::T)
			{
				if (fulltext[i] == '|') {
					if (onestr.length() > 2) {
						if (FST::check((char*)onestr.c_str()) == 1) {         //отчет об ошибке
							out << "\nРаспознано";
						}
						else {
							out << "\nНе распознано";
							out << "Произошла ошибка разбора\n";
							out << "Проверьте ";
							out << (currentLine + 1);
							out << " строку\n";
							out << Info.text;
							throw ERROR_THROW_IN(113, currentLine + 1, currentCol);
						}
					}
					onestr.clear();
				}
				else {
					if (fulltext[i] != '\n')
						onestr = onestr + fulltext[i];
				}
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else													//отработка игнора
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')								//конец строки
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*Ptemp = IN_CODE_ENDL;										//конец стоки
		Info.size = strlen((char*)Info.text) - Info.lines;			//количество символо = количество всех элем - символ новой строки
		out << Info.text;
		return Info;
	}
}