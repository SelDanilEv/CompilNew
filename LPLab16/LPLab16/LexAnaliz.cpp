#include "pch.h"
#include "LexAnaliz.h"
#include "In.h"
#include "Error.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"
#include <string>
#include <iostream>
#include <fstream>


namespace LexA
{
	struct MyAutomat                       //структура для автоматов
	{
		int automat[20];                        //массив автоматов
		char lexema[18] = { LEX_ID,LEX_INTEGER,LEX_STRING,
			LEX_FUNCTION,LEX_DECLARE,LEX_RETURN,LEX_PRINT,
			LEX_MAIN ,LEX_SEMICOLON,LEX_COMMA,LEX_LEFTBRACE,
			LEX_RIGHTBRACE,LEX_LEFTTHESIS,LEX_RIGHTTHESIS,
			LEX_EQUAL,LEX_PLUS,LEX_LITERAL,LEX_SHORT };
	}automats;


	IT::Entry myentryI;                   //вспомогательные сущности
	LT::Entry myentryL;


	std::string str;                       //буфер для инициализации
	void Update(std::string str) {                   //обновление состояния автоматов
		automats.automat[0] = 0;
		automats.automat[1] = FST::integer((char*)str.c_str());
		automats.automat[2] = FST::string((char*)str.c_str());
		automats.automat[3] = FST::function((char*)str.c_str());
		automats.automat[4] = FST::declare((char*)str.c_str());
		automats.automat[5] = FST::Return((char*)str.c_str());
		automats.automat[6] = FST::print((char*)str.c_str());
		automats.automat[7] = FST::main((char*)str.c_str());
		automats.automat[17] = FST::Short((char*)str.c_str());
	}

	unsigned char buff_name[ID_MAXSIZE];            //для идентификаторов
	unsigned char buff_name_str[ID_MAXSIZE];            //для идентификаторов
	std::string standartFunction[] = { "strlen","substr" };
	bool isAStandartFunction = false;
	int counterOfAreaOfVisibility = 0;
	int counterOfBracket = 0;
	short areaOfVisibilityLexAnaliz[5];
	short counterOfIntegerLiteral = 0;
	short counterOfStringLiteral = 0;
	std::string buffer;
	int bufferi;
	int bufferi1;
	bool bufferb;

	IT::IDDATATYPE iddatatype;                            //вспомогательные переменные для добавки в IT
	IT::IDTYPE idtype;

	void addNewInIT(IT::IdTable &myidtable, LT::LexTable &mylextable) {
		idtype = IT::E;
		iddatatype = IT::Err;
		if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_FUNCTION)
			idtype = IT::F;
		else
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_DECLARE)
				idtype = IT::V;
			else
				if (((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_LEFTTHESIS) || ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_COMMA))
					idtype = IT::P;

		if (idtype == IT::F)
		{
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_INTEGER)
				iddatatype = IT::INT;
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_STRING)
				iddatatype = IT::STR;
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_SHORT)
				iddatatype = IT::SHR;
		}
		else
		{
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_INTEGER)
			{
				iddatatype = IT::INT;
				myentryI.value.vint = 0;
			}
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_SHORT)
			{
				iddatatype = IT::SHR;
				myentryI.value.vshr = 0;
			}
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_STRING)
			{
				iddatatype = IT::STR;
				myentryI.value.vstr.len = 0;
				myentryI.value.vstr.str[0] = SPACE;
			}
		}
		myentryI.idxfirstLE = mylextable.size;
		if (isAStandartFunction)                         //если это стандартная функция
		{
			for (int i = 0; i < str.length() + 1; i++)
			{
				if (str.length() == i)
					myentryI.id[i] = '\0';
				else
					myentryI.id[i] = str[i];
			}
		}
		else
			for (int i = 0; i < 5; i++)
				myentryI.id[i] = buff_name[i];               //в таблицу идентификаторов
		myentryI.iddatatype = iddatatype;
		myentryI.idtype = idtype;
		IT::Add(myidtable, myentryI);
		myentryL.idxTI = myidtable.size - 1;
	}

	void analyze(int currentLine, char *fulltextch)                         //функция анализа
	{
		Tables myTables;

		std::string fulltext = fulltextch;                         //исходный текст
		std::string onelex[250];                                 //массив лексем(будущий)
		int amountOfLex = 0;                              //кол во лексем
		char symvols[] = ";,{}()+-*/=\n";                          //символы сепараторы
		int *linesForLex = new int[currentLine];                  //массив содержит инфу о строках
		currentLine = 0;

		int LexInIT;                                      // какая строка в IT для лексемы

		for (int counter = 0; counter < fulltext.size(); counter++)      //парсер для текста
		{
			if (!strchr(symvols, fulltext[counter]) && fulltext[counter] != SPACE)
			{
				if (fulltext[counter] == '\'')
				{
					onelex[amountOfLex] = fulltext[counter];
					counter++;
					if (fulltext[counter] != '\'')
						do
						{
							onelex[amountOfLex] += fulltext[counter];
							counter++;
						} while (fulltext[counter - 1] != '\'');
					else
						throw ERROR_THROW(444)    //переписать ошибку
						counter--;
				}
				else
				{
					onelex[amountOfLex] += fulltext[counter];
				}
			}
			else
			{
				if (fulltext[counter] != NEWLINE)            //новая строка
				{
					if (fulltext[counter] != SPACE)
					{
						if (fulltext[counter - 1] != SPACE && !strchr(symvols, fulltext[counter - 1]))
							amountOfLex++;
						onelex[amountOfLex] = fulltext[counter];
						amountOfLex++;
					}
					else {
						if (fulltext[counter - 1] != SPACE && !strchr(symvols, fulltext[counter - 1]))
							amountOfLex++;
					}
				}
				else {
					linesForLex[currentLine] = amountOfLex;
					currentLine++;
				}
			}
		}


		myTables.myidtable = IT::Create(amountOfLex);                         //создания таблиц
		myTables.mylextable = LT::Create(amountOfLex);

		for (int i = 0; i < 5; i++)                //обнуление буфера имен
		{
			buff_name[i] = NULL;
		}

		currentLine = 0;

		int identifyLex = 0;         // предопределение автомата
		for (int i = 0; i < amountOfLex; i++) {
			while (linesForLex[currentLine] <= i)         // повышение строки
			{
				currentLine++;
			}

			char temp = onelex[i][0];                          //первая буква лексемы
			str = onelex[i];
			identifyLex = 0;
			int lex[3];	//0-индеф  1-int 2-string 3-функ  4-инстр  5-возрат  6-вывод  7-гл ф   8-;  9-,  10-{  11-}  12-(   13-)   14-=  15-(+-*/)  16-литерал
			lex[0] = 0; lex[1] = 0; lex[2] = 0;
			if (temp == '1' || temp == '2' || temp == '3' || temp == '4' || temp == '5' || temp == '6' || temp == '7' || temp == '8' || temp == '9' || temp == '0' || temp == '\'')lex[0] = 16; else {
				switch (temp)       //определение возможного типа лексемы
				{
				case LEX_ID:
					lex[0] = 1;
					break;
				case 's':
					lex[0] = 2;      //string
					lex[1] = 17;       //short
					break;
				case LEX_FUNCTION:
					lex[0] = 3;
					break;
				case LEX_DECLARE:
					lex[0] = 4;
					break;
				case LEX_RETURN:
					lex[0] = 5;
					break;
				case LEX_PRINT:
					lex[0] = 6;
					break;
				case LEX_MAIN:
					lex[0] = 7;
					break;
				case LEX_SEMICOLON:
					lex[0] = 8;
					break;
				case LEX_COMMA:
					lex[0] = 9;
					break;
				case LEX_LEFTBRACE:
					lex[0] = 10;
					break;
				case LEX_RIGHTBRACE:
					lex[0] = 11;
					break;
				case LEX_LEFTTHESIS:
					lex[0] = 12;
					break;
				case LEX_RIGHTTHESIS:
					lex[0] = 13;
					break;
				case LEX_EQUAL:
					lex[0] = 14;
					break;
				case ('+'):
					lex[0] = 15;
					break;
				case '-':
					lex[0] = 15;
					break;
				case '*':
					lex[0] = 15;
					break;
				case '/':
					lex[0] = 15;
					break;
				default:
					break;
				}      //определение возможного типа лексемы
			}
			for (int i = 0; i < 3; i++)
			{
				if (lex[i] != 0)
					if ((lex[i] < 8 && lex[i]>0) || lex[i] == 17)         //если можно разобрать автоматом
					{
						Update(str);
						if (automats.automat[lex[i]] == lex[i])          //проверка подошел ли автомат
							identifyLex = lex[i];
					}
					else
					{
						identifyLex = lex[i];                      //по номеру
					}
				else
					lex[i] = 0;
			}


			isAStandartFunction = false;
			for (int i = 0; i < standartFunction->length(); i++)
			{
				if (str == standartFunction[i]) isAStandartFunction = true;
			}

			for (int i = 0; i < str.length() && i < 5; i++)            //берем имя
				buff_name[i] = str[i];
			for (int i = 4; i >= str.length(); i--)
				buff_name[i] = NULL;

			if (identifyLex == 0 || identifyLex == 16 || identifyLex == 10 || identifyLex == 11 || identifyLex == 7)          //если идентификатор
			{
				for (int i = 0; i < str.length(); i++)
					buff_name_str[i] = str[i];
				for (int i = 10; i >= str.length(); i--)
					buff_name_str[i] = NULL;
				switch (identifyLex)
				{
				case 7:
					myentryI.areaOfVisibility[0] = 0;
					for (int q = 0; q < 5; q++)
						myentryI.id[q] = buff_name[q];
					myentryI.iddatatype = IT::INT;
					myentryI.idtype = IT::F;
					myentryI.value.vint = 0;
					IT::Add(myTables.myidtable, myentryI);
					myentryL.idxTI = myTables.myidtable.size - 1;
					break;
				case 10:                                                         //область видимости
					counterOfBracket++;
					counterOfAreaOfVisibility++;
					myentryI.areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
					areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = counterOfBracket;
					bufferi = myTables.mylextable.size;
					while (myTables.mylextable.table[bufferi].lexema != LEX_LEFTTHESIS && myTables.mylextable.table[bufferi].lexema != LEX_MAIN && myTables.mylextable.table[bufferi].lexema != LEX_SEMICOLON)
					{
						if (myTables.mylextable.table[bufferi].lexema == LEX_ID)
							myTables.myidtable.table[myTables.mylextable.table[bufferi].idxTI].areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
						bufferi--;
					}
					break;
				case 11:
					areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = NULL;
					myentryI.areaOfVisibility[counterOfAreaOfVisibility] = NULL;
					counterOfAreaOfVisibility--;
					break;
				case 16:                                                             //литералы
					myentryI.idxfirstLE = myTables.mylextable.size;
					if (str[0] == '\'')                         //строковые
					{
						for (int i = 0; i < str.length(); i++)
							myentryI.value.vstr.str[i] = str[i];
						for (int i = ID_MAXSIZE; i >= str.length(); i--)
							myentryI.value.vstr.str[i] = NULL;
						myentryI.id[0] = 'S';
						buffer = std::to_string(counterOfStringLiteral++);
						for (int i = 0; i < buffer.length(); i++)
							myentryI.id[i + 1] = buffer[i];
						for (int i = ID_MAXSIZE - 1; i >= buffer.length(); i--)
							myentryI.id[i + 1] = NULL;
						myentryI.iddatatype = IT::STR;
					}
					else                               //целочисленные
					{
						if (!FST::literalInt((char*)str.c_str())) system("pause");
						myentryI.value.vint = std::stoi(str);
						myentryI.id[0] = 'I';
						buffer = std::to_string(counterOfIntegerLiteral++);
						for (int i = 0; i < buffer.length(); i++)
							myentryI.id[i + 1] = buffer[i];
						for (int i = ID_MAXSIZE - 1; i >= buffer.length(); i--)
							myentryI.id[i + 1] = NULL;
						myentryI.iddatatype = IT::INT;

					}
					myentryI.idtype = IT::L;
					IT::Add(myTables.myidtable, myentryI);                        //добавить в IT
					myentryL.idxTI = myTables.myidtable.size - 1;
					break;
				case 0:
					if (IT::IsId(myTables.myidtable, buff_name) == TI_NULLIDX && IT::IsId(myTables.myidtable, buff_name_str) == TI_NULLIDX)      //было ли уже в таблице идентификаторов   
					{
						addNewInIT(myTables.myidtable, myTables.mylextable);
					}
					else
					{
						if (!isAStandartFunction)               //если не стандартная функция             
						{
							bufferb = true;
							for (int y = 0; y < myTables.myidtable.size; y++)
							{
								bufferi = 0;
								bufferi1 = 1;
								buffer = "";
								for (int w = 0; w < 5; w++)
									buffer += myTables.myidtable.table[y].id[w];
								if (std::strcmp(str.c_str(), buffer.c_str()) == 0)        //если названия сошлись
								{
									while (myTables.myidtable.table[y].areaOfVisibility[bufferi1] != 0)  //узнаю сколько значащих в массиве видимости подозреваемого
										bufferi1++;                         //counterOfAreaOfVisibility какой край области видимости сейчас
									if (bufferi1 == counterOfAreaOfVisibility + 1) {                  //если одинокого цифр 
										if (myTables.myidtable.table[y].areaOfVisibility[bufferi1 - 1] == areaOfVisibilityLexAnaliz[bufferi1 - 1]) //запрет если одинаковык
											bufferb = false;
									}
									else {
										for (int q = 0; q < counterOfAreaOfVisibility + 1; q++)
											if (myTables.myidtable.table[y].areaOfVisibility[q] != areaOfVisibilityLexAnaliz[q])
												bufferb = false;
									}
								}
							}
							if (bufferb)
								addNewInIT(myTables.myidtable, myTables.mylextable);
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.myidtable, buff_name, areaOfVisibilityLexAnaliz);
							myentryL.idxTI = LexInIT;
						}
						else {
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.myidtable, buff_name_str, areaOfVisibilityLexAnaliz);
							myentryL.idxTI = LexInIT;
						}
					}
				}
				//и в любом случае в лексемы
				myentryL.lexema = automats.lexema[identifyLex];
				myentryL.sn = currentLine;
				LT::Add(myTables.mylextable, myentryL);
			}
			else                        //если не идентификатор
			{
				if (identifyLex == 15)
					myentryL.value = str[0];
				if (identifyLex == 18) {
					identifyLex = 18;
				}
				myentryL.idxTI = LT_TI_NULLIDX;              //просто в таблицу лексем
				myentryL.lexema = automats.lexema[identifyLex];
				myentryL.sn = currentLine;
				LT::Add(myTables.mylextable, myentryL);
				myentryL.value = SPACE;
			}
		}

		//polishNotation(17,myTables.mylextable,myTables.myidtable);
		//polishNotation(62,myTables.mylextable,myTables.myidtable);


		
		MFST_TRACE_START

		MFST::Mfst mfst(myTables, GRB::getGreibach());

		system("pause");
		mfst.start();
		std::cout << "\n\n";
		mfst.printrules();
		system("pause");

		std::ofstream fileLT;               //формрирование файлов таблиц
		fileLT.open("LT.txt");
		LT::showTable(myTables.mylextable, fileLT);
		fileLT.close();

		std::ofstream fileLT_mini;
		fileLT_mini.open("LT_mini.txt");
		LT::showTable_mini(myTables.mylextable, fileLT_mini);
		fileLT_mini.close();

		std::ofstream fileIT;
		fileIT.open("IT.txt");
		IT::showTable(myTables.myidtable, fileIT);
		fileIT.close();

		std::cout << "End of LexAnaliz\n";
		system("pause");
	}
}