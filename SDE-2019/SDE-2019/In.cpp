#include "pch.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "LexAnaliz.h"
#include <fstream>
#include <string>
#include <iostream>

namespace In
{
	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		std::string onestr;
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };// инициализация
		std::ifstream in(infile);// чтения
		std::ofstream out(outfile);// записи
		if (!out.is_open())
			throw ERROR_THROW(110);
		if (!in.is_open())
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())//пока открыт файл
		{
			Info.lines++;//кол-во линий
			std::getline(in, temp);//запись tеmp
			temp += "\n";//знак окончания строки
			fulltext += temp;
		}
		fulltext += ' ';
		Info.text = new unsigned char[fulltext.size() + 1];//выделяем память
		unsigned char * Ptemp = Info.text;//указатель на начало
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (Info.code[(unsigned char)fulltext[i]] == IN::F)
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)                    //проверка символов на допустимость
			}                              
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I)
				++Info.ignor;
			else if (Info.code[(unsigned char)fulltext[i]] != IN::T)
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];                 
				++Ptemp;
			}
			if (fulltext[i] == '\n')
			{
				currentLine++;                                  //подсчет строк
				currentCol = 0;
			}
			else
				currentCol++;
		}
		*Ptemp = IN_CODE_ENDL;
		Info.size = fulltext.size()-Info.lines;
		

		LexA::analyze(currentLine, (char *)fulltext.c_str());                 //запуск лексического анализатора

		out << Info.text;
		return Info;
	}
}