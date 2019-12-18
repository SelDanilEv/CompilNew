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
#include <math.h>

namespace LexA
{
	struct MyAutomat                       //структура для автоматов
	{
		int automat[24];                        //массив автоматов

		char lexema[24] = {
			LEX_LITTLE,LEX_TEXT,LEX_FUNCTION,
			LEX_START,LEX_NEW,LEX_RETURN,
			LEX_OUTPUT,LEX_ID,LEX_LITERAL,
			LEX_SEMICOLON,LEX_COMMA,LEX_LEFTBRACE,
			LEX_RIGHTBRACE,LEX_LEFTTHESIS,LEX_RIGHTTHESIS,
			LEX_EQUAL,LEX_OPERATOR,LEX_FROM,
			LEX_TO,LEX_ENDCONDCYCL,LEX_CHECK,
			LEX_ENDCHECK,LEX_NOT,LEX_OPERCHECK
		};

		char value[24] = {
			'l','t',' ',
			' ',' ',' ',
			' ',' ',' ',
			' ',' ',' ',
			' ',' ',' ',
			' ',' ',' ',
			' ','$',' ',
			'?',' ',' '
		};
	}automats;

	unsigned char buff_name[ID_MAXSIZE];            //для идентификаторов
	unsigned char buff_name_str[ID_MAXSIZE];            //для идентификаторов
	std::string standartFunction[] = { "copytxt","textlenght" };
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

	IT::Entry myentryI;                   //вспомогательные сущности
	LT::Entry myentryL;

	std::string str;                       //буфер для инициализации

	void Update(std::string str, int numbOfLex) {                   //обновление состояния автоматов
		switch (numbOfLex)
		{
		case 0:
			automats.automat[0] = FST::little((char*)str.c_str());
			break;
		case 1:
			automats.automat[1] = FST::text((char*)str.c_str());
			break;
		case 2:
			automats.automat[2] = FST::function((char*)str.c_str());
			break;
		case 3:
			automats.automat[3] = FST::start((char*)str.c_str());
			break;
		case 4:
			automats.automat[4] = FST::New((char*)str.c_str());
			break;
		case 5:
			automats.automat[5] = FST::Return((char*)str.c_str());
			break;
		case 6:
			automats.automat[6] = FST::output((char*)str.c_str());
			break;
		case 7:
			automats.automat[7] = FST::id((char*)str.c_str());
			break;
		case 17:
			automats.automat[17] = FST::from((char*)str.c_str());
			break;
		case 18:
			automats.automat[18] = FST::to((char*)str.c_str());
			break;
		case 20:
			automats.automat[20] = FST::check((char*)str.c_str());
			break;
		case 22:
			automats.automat[22] = FST::Not((char*)str.c_str());
			break;
		default:
			break;
		}
	}

	void addToLT(int identifyLex, int currentLine, LT::LexTable &lextable, LT::Entry entryL)
	{
		entryL.lexema = automats.lexema[identifyLex];
		if (identifyLex != 16&& identifyLex != 23)
			entryL.value = automats.value[identifyLex];
		if (isAStandartFunction)
			entryL.value = LEX_LIBFUNCTION;
		entryL.sn = currentLine;
		LT::Add(lextable, entryL);
	}


	bool FindIDByLexAndArea(LT::LexTable &lextable, IT::IdTable&idtable, std::string str) {
		short* areaOfV = new short[5];
		std::string b_str="";
		for (int i = 0; i < MAXSIZEIDENTIFICATOR && i < str.length(); i++)
		{
			b_str += str[i];
		}
		for (int i = 0; i < 5; i++)
			areaOfV[i] = areaOfVisibilityLexAnaliz[i];  //копия области видимости
		bufferi = 4;
		while (IT::IsIdWithAreaOfVisibility(idtable, (unsigned char*)str.c_str(), areaOfV) == TI_NULLIDX &&
			IT::IsIdWithAreaOfVisibility(idtable, (unsigned char*)b_str.c_str(), areaOfV) == TI_NULLIDX) {   //поиск подходящего идентификатора
			areaOfV[bufferi--] = 0;
			if (bufferi < 0)return true;
		}
		myentryL.idxTI = IT::IsIdWithAreaOfVisibility(idtable, (unsigned char*)str.c_str(), areaOfV);
		if(myentryL.idxTI==-1)
			myentryL.idxTI = IT::IsIdWithAreaOfVisibility(idtable, (unsigned char*)b_str.c_str(), areaOfV);
		return false;
	}

	void addNewInIT(IT::IdTable &myidtable, LT::LexTable &mylextable) {

		idtype = IT::E;
		iddatatype = IT::Err;

		if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_FUNCTION)
			idtype = IT::F;
		else
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_NEW)
				idtype = IT::V;
			else
				if (((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_LEFTTHESIS) || ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_COMMA))
					idtype = IT::P;

		if (idtype == IT::F)
		{
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).value == 'l')
				iddatatype = IT::LIT;
			if ((LT::GetEntry(mylextable, mylextable.size - 2)).value == 't')
				iddatatype = IT::TXT;
		}
		else
		{
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).value == 'l')
			{
				iddatatype = IT::LIT;
				myentryI.value.vint = 0;
			}
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).value == 't')
			{
				iddatatype = IT::TXT;
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
			for (int i = 0; i < MAXSIZEIDENTIFICATOR; i++)
				myentryI.id[i] = buff_name[i];               //в таблицу идентификаторов
		myentryI.iddatatype = iddatatype;
		myentryI.idtype = idtype;
		IT::Add(myidtable, myentryI);
		myentryL.idxTI = myidtable.size - 1;
	}

	Tables analyze(int currentLine, char *fulltextch)                         //функция анализа
	{
		std::string fulltext = fulltextch;                         //исходный текст
		std::string onelex[300];                                 //массив лексем(будущий)
		int amountOfLex = 0;                              //кол во лексем
		//char symvols[] = "?$;,{}()+-%*/=\n\t";                        //символы сепараторы
		int *linesForLex = new int[currentLine];                  //массив содержит инфу о строках
		currentLine = 0;
		int LexInIT;                                      // какая строка в IT для лексемы

		bool isLiteral = false;
		bool isComent = false;
		int sizeofLit = 0;


		for (int counter = 0; counter < fulltext.size(); counter++)           //парсер для текста
		{
			switch (fulltext[counter])
			{
			case '^':
				if (!isLiteral && !isComent)
					isComent = true;
				break;
			case '-':
				if (!isLiteral && !isComent)
					if (onelex[amountOfLex - 1] == "=" || onelex[amountOfLex - 1] == "(")
					{
						onelex[amountOfLex] += fulltext[counter];
						break;
					}
			case '?':
			case '$':
			case ';':
			case ',':
			case '{':
			case '}':
			case '(':
			case ')':
			case '>':
			case '<':
			case '+':
			case '%':
			case '*':
			case '/':
			case '=':
				if (!isLiteral && !isComent)
				{
					if (onelex[amountOfLex] != "")
						amountOfLex++;
					onelex[amountOfLex] += fulltext[counter];
				}
			case ' ':
			case '\n':
				if (!isLiteral&&fulltext[counter] == '\n')
					if (!isComent)
					{
						linesForLex[currentLine] = amountOfLex;
						currentLine++;
					}
					else
					{
						isComent = false;
					}
			case '\t':
				if (!isComent)
					if (!isLiteral)
					{
						if (onelex[amountOfLex] != "")
							amountOfLex++;
					}
					else
					{
						sizeofLit++;
						if (sizeofLit > 255)
							throw ERROR_THROW_IN(118, currentLine, 0);
						onelex[amountOfLex] += fulltext[counter];

					}
				break;
			case '\'':
				if (!isComent)
				{
					isLiteral = !isLiteral;
					sizeofLit = 0;
				}
			default:
				if (!isComent)
					onelex[amountOfLex] += fulltext[counter];
				break;
			}
			//if ((!strchr(symvols, fulltext[counter]) && fulltext[counter] != SPACE && fulltext[counter] != '\t'))
			//{
			//	if (fulltext[counter] == '\'')
			//	{
			//		int sizeofLit = 0;
			//		onelex[amountOfLex] = fulltext[counter];
			//		counter++;
			//		if (fulltext[counter] != '\'')
			//			do
			//			{
			//				if (sizeofLit > 255)
			//					throw ERROR_THROW_IN(118, currentLine, 0);
			//				sizeofLit++;
			//				onelex[amountOfLex] += fulltext[counter];
			//				counter++;
			//			} while (fulltext[counter - 1] != '\'' && (fulltext[counter - 1] != '\n'));
			//			counter--;
			//	}
			//	else
			//	{
			//		onelex[amountOfLex] += fulltext[counter];
			//	}
			//}
			//else
			//{
			//	if (fulltext[counter] != NEWLINE)            //новая строка
			//	{
			//		if (fulltext[counter] != SPACE && fulltext[counter] != '\t')
			//		{
			//			if ((fulltext[counter - 1] != '\t'&&fulltext[counter - 1] != SPACE && !strchr(symvols, fulltext[counter - 1])) && fulltext[counter - 1] != LEX_ENDCONDCYCL)
			//				amountOfLex++;
			//			onelex[amountOfLex] = fulltext[counter];
			//			amountOfLex++;
			//		}
			//		else {
			//			if (fulltext[counter - 1] != SPACE && fulltext[counter - 1] != '\t' && !strchr(symvols, fulltext[counter - 1]))
			//				amountOfLex++;
			//		}
			//	}
			//	else {
			//		linesForLex[currentLine] = amountOfLex;
			//		currentLine++;
			//		if (onelex[amountOfLex] != "")
			//			amountOfLex++;
			//	}
			//}
		}

		Tables myTables;
		myTables.myidtable = IT::Create(amountOfLex);                         //создания таблиц
		myTables.mylextable = LT::Create(amountOfLex);

		for (int i = 0; i < MAXSIZEIDENTIFICATOR; i++)                //обнуление буфера имен
		{
			buff_name[i] = NULL;
		}

		currentLine = 0;

		int identifyLex = 0;         // предопределение автомата

		for (int i = 0; i < 5; i++)
			myentryI.areaOfVisibility[i] = areaOfVisibilityLexAnaliz[i];
		myentryI.id[0] = 'b';
		myentryI.id[1] = 'u';
		myentryI.id[2] = 'f';
		myentryI.id[3] = 'f';
		myentryI.id[4] = 'e';
		myentryI.id[5] = 'r';
		myentryI.iddatatype = IT::LIT;
		myentryI.idtype = IT::V;
		myentryI.idxfirstLE = -1;
		myentryI.value.vint = 0;
		IT::Add(myTables.myidtable, myentryI);

		for (int i = 0; i < amountOfLex; i++) {
			while (linesForLex[currentLine] <= i)         // повышение строки
			{
				currentLine++;
			}
			for (int i = 0; i < 15; i++)
				myentryI.id[i] = NULL;
			char temp = onelex[i][0];                          //первая буква лексемы
			str = onelex[i];

			if (str == "")break;//checker

			identifyLex = 0;
			int lex[3];	//0-little  1-text 2-function 3-start  4-new  5-return  6-print  7-id 8-literal 9-;  10-,  11-{  12-}  13-(  14-)  15-=  16-(+-*/) 17-from 18-to 19-$ 20-check 21-? 22-not 23-<>
			lex[0] = -1; lex[1] = -1; lex[2] = -1;

			switch (temp)       //определение возможного типа лексемы
			{
			case '>':
			case '<':
				lex[0] = 23;
				break;
			case 'l':
				lex[0] = 0;       //little
				break;
			case 't':
				lex[0] = 1;      //text
				lex[1] = 18;
				break;
			case 'f':
				lex[0] = 2;
				lex[1] = 17;
				break;
			case 'c':
				lex[0] = 20;
				break;
			case 's':
				lex[0] = 3;
				break;
			case 'n':
				lex[0] = 4;
				lex[1] = 22;
				break;
			case 'r':
				lex[0] = 5;
				break;
			case 'o':
				lex[0] = 6;
				break;
			case LEX_SEMICOLON:
				lex[0] = 9;
				break;
			case LEX_COMMA:
				lex[0] = 10;
				break;
			case LEX_LEFTBRACE:
				lex[0] = 11;
				break;
			case LEX_RIGHTBRACE:
				lex[0] = 12;
				break;
			case LEX_LEFTTHESIS:
				lex[0] = 13;
				break;
			case LEX_RIGHTTHESIS:
				lex[0] = 14;
				break;
			case LEX_EQUAL:
				lex[0] = 15;
				break;
			case ('+'):
				lex[0] = 16;
				break;
			case '-':
				lex[0] = 16;
				lex[1] = 8;
				break;
			case '*':
				lex[0] = 16;
				break;
			case '%':
				lex[0] = 16;
				break;
			case '/':
				lex[0] = 16;
				break;
			case LEX_ENDCONDCYCL:
				lex[0] = 19;
				break;
			case LEX_ENDCHECK:
				lex[0] = 21;
				break;
			case '!':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '\'':
				lex[0] = 8;
				break;
			default:
				break;
			}      //определение возможного типа лексемы

			for (int i = 0; i < 3; i++)
			{
				if (lex[i] != 7 && lex[i] > -1)
					if (lex[i] < 7 || lex[i] == 17 || lex[i] == 18 || lex[i] == 20 || lex[i] == 22)         //если можно разобрать автоматом
					{
						Update(str, lex[i]);
						if (automats.automat[lex[i]] == lex[i])          //проверка подошел ли автомат
						{
							identifyLex = lex[i];
							break;
						}
						else
							lex[i] = -1;
					}
					else
					{
						if (str.length() == 1 && lex[i] == 8 && str[0] == '-')
							identifyLex = 16;
						else
							identifyLex = lex[i];                      //по номеру
					}
			}

			if (lex[0] == -1 && lex[1] == -1 && lex[2] == -1) identifyLex = 7;

			if (identifyLex == 7 && !isAStandartFunction&&str != "buffer") {
				Update(str, 7);
				if (automats.automat[7] != 7)
					throw ERROR_THROW_IN(117, currentLine, 0);
			}

			isAStandartFunction = false;
			for (int i = 0; i < 2; i++)
			{
				if (str == standartFunction[i]) isAStandartFunction = true;
			}

			for (int i = 0; i < str.length() && i < MAXSIZEIDENTIFICATOR; i++)            //берем имя
				buff_name[i] = str[i];
			for (int i = MAXSIZEIDENTIFICATOR; i >= str.length(); i--)
				buff_name[i] = NULL;
			for (int i = 0; i < str.length(); i++)
				buff_name_str[i] = str[i];
			for (int i = 15; i >= str.length(); i--)
				buff_name_str[i] = NULL;

			switch (identifyLex)
			{
			case 3:
				if (IT::IsId(myTables.myidtable, buff_name) != TI_NULLIDX)
				{
					throw ERROR_THROW_IN(150, currentLine, 0);
				}
				myentryI.areaOfVisibility[0] = 0;
				for (int q = 0; q < MAXSIZEIDENTIFICATOR; q++)
					myentryI.id[q] = buff_name[q];
				myentryI.iddatatype = IT::LIT;
				myentryI.idtype = IT::F;
				myentryI.value.vint = 0;
				myentryI.idxfirstLE = myTables.mylextable.size;
				IT::Add(myTables.myidtable, myentryI);
				myentryL.idxTI = myTables.myidtable.size - 1;
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			case 11:                                                         //область видимости
				counterOfBracket++;
				counterOfAreaOfVisibility++;
				if (counterOfAreaOfVisibility > 4)
					throw ERROR_THROW_IN(119, currentLine, 0);
				myentryI.areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
				areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = counterOfBracket;
				bufferi = myTables.mylextable.size;
				while (myTables.mylextable.table[bufferi].lexema != LEX_LEFTTHESIS && myTables.mylextable.table[bufferi].lexema != LEX_START &&
					myTables.mylextable.table[bufferi].lexema != LEX_SEMICOLON && myTables.mylextable.table[bufferi].lexema != LEX_ENDCONDCYCL &&
					myTables.mylextable.table[bufferi].lexema != LEX_ENDCHECK && myTables.mylextable.table[bufferi].lexema != LEX_RIGHTBRACE)
				{
					if (myTables.mylextable.table[bufferi].lexema == LEX_ID)
						myTables.myidtable.table[myTables.mylextable.table[bufferi].idxTI].areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
					bufferi--;
				}
				myentryL.idxTI = LT_TI_NULLIDX;
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			case 12:
				areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = NULL;
				myentryI.areaOfVisibility[counterOfAreaOfVisibility] = NULL;
				counterOfAreaOfVisibility--;
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			case 8:                                                             //литералы
				myentryI.idxfirstLE = myTables.mylextable.size;
				if (str[0] == '\'')                         //строковые
				{
					if (str[str.length() - 1] != '\'')throw ERROR_THROW_IN(112, currentLine, 0);
					myentryI.value.vstr.len = str.length();
					for (int i = 0; i < str.length(); i++)
						myentryI.value.vstr.str[i] = str[i];
					for (int i = ID_MAXSIZE; i >= str.length(); i--)
						myentryI.value.vstr.str[i] = NULL;
					myentryI.id[0] = 'T';
					buffer = std::to_string(counterOfStringLiteral++);
					for (int i = 0; i < buffer.length(); i++)
						myentryI.id[i + 1] = buffer[i];
					for (int i = ID_MAXSIZE - 1; i >= buffer.length(); i--)
						myentryI.id[i + 1] = NULL;
					myentryI.iddatatype = IT::TXT;
				}
				else                               //целочисленные
				{
					if (!FST::literalInt((char*)str.c_str())) throw ERROR_THROW_IN(113, currentLine, 0);
					if (str[0] == '!')
					{
						int n = 0;
						int numb = 0;
						int counter = 0;
						while (str[n] != NULL)
						{
							str[n] = str[n + 1];
							n++;
						}
						for (int p = n - 2; p >= 0; p--)
						{
							if (str[p] == '1')
								numb += pow(2, counter);
							counter++;
						}
						myentryI.value.vint = numb;
					}
					else
						myentryI.value.vint = std::stoi(str);
					myentryI.id[0] = 'L';
					buffer = std::to_string(counterOfIntegerLiteral++);
					for (int i = 0; i < buffer.length(); i++)
						myentryI.id[i + 1] = buffer[i];
					for (int i = ID_MAXSIZE - 1; i >= buffer.length(); i--)
						myentryI.id[i + 1] = NULL;
					myentryI.iddatatype = IT::LIT;

				}
				myentryI.idtype = IT::L;
				IT::Add(myTables.myidtable, myentryI);                        //добавить в IT
				myentryL.idxTI = myTables.myidtable.size - 1;
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			case 7:
				if ((LT::GetEntry(myTables.mylextable, myTables.mylextable.size - 2)).lexema == LEX_NEW ||
					(LT::GetEntry(myTables.mylextable, myTables.mylextable.size - 2)).lexema == LEX_TYPES ||
					(LT::GetEntry(myTables.mylextable, myTables.mylextable.size - 1)).lexema == LEX_TYPES)
				{
					if (IT::IsId(myTables.myidtable, buff_name) == TI_NULLIDX && IT::IsId(myTables.myidtable, buff_name_str) == TI_NULLIDX)      //было ли уже в таблице идентификаторов   
					{
						addNewInIT(myTables.myidtable, myTables.mylextable);
						if (myentryI.iddatatype == IT::Err || myentryI.idtype == IT::E)
							throw ERROR_THROW_IN(154, currentLine, 0);
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
								for (int w = 0; w < MAXSIZEIDENTIFICATOR; w++)
									buffer += myTables.myidtable.table[y].id[w];
								if (std::strcmp(str.c_str(), buffer.c_str()) == 0)        //если названия сошлись
								{
									bufferb = false;
									for (int q = 0; q < 5; q++)        //добавление всех где не совпадает область видимости
									{
										if (myTables.myidtable.table[y].areaOfVisibility[q] != areaOfVisibilityLexAnaliz[q])
										{
											bufferb = true;
										}
									}
								}
							}
							if (bufferb)
								addNewInIT(myTables.myidtable, myTables.mylextable);
							else throw ERROR_THROW_IN(152, currentLine, 0);

							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.myidtable, buff_name, areaOfVisibilityLexAnaliz);
							myentryL.idxTI = LexInIT;
						}
					}
				}
				else
				{
					if (!isAStandartFunction)               //если не стандартная функция             
					{
						bufferb = FindIDByLexAndArea(myTables.mylextable, myTables.myidtable, str);
					}
					else
					{
						if (str == "textlenght")myentryL.idxTI = -2;
						else myentryL.idxTI = -3;
					}
					if (bufferb)throw ERROR_THROW_IN(153, currentLine, 0);    //необъявленная переменная
				}
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			default:        //если не start  {}  id
				if (identifyLex == 16||identifyLex==23)
					myentryL.value = str[0];
				myentryL.idxTI = LT_TI_NULLIDX;              //просто в таблицу лексем
				addToLT(identifyLex, currentLine, myTables.mylextable, myentryL);
				break;
			}
		}

		return myTables;
	}
}