#include "pch.h"
<<<<<<< HEAD
#include <string>
=======
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
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2


namespace LexA
{
	struct MyAutomat                       //��������� ��� ���������
	{
		int automat[20];                        //������ ���������
		char lexema[18] = { LEX_ID,LEX_INTEGER,LEX_STRING,
			LEX_FUNCTION,LEX_DECLARE,LEX_RETURN,LEX_PRINT,
			LEX_MAIN ,LEX_SEMICOLON,LEX_COMMA,LEX_LEFTBRACE,
			LEX_RIGHTBRACE,LEX_LEFTTHESIS,LEX_RIGHTTHESIS,
			LEX_EQUAL,LEX_PLUS,LEX_LITERAL,LEX_SHORT };
	}automats;


	IT::Entry myentryI;                   //��������������� ��������
	LT::Entry myentryL;


	std::string str;                       //����� ��� �������������
	void Update(std::string str) {                   //���������� ��������� ���������
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

	unsigned char buff_name[ID_MAXSIZE];            //��� ���������������
	unsigned char buff_name_str[ID_MAXSIZE];            //��� ���������������
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

	IT::IDDATATYPE iddatatype;                            //��������������� ���������� ��� ������� � IT
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
<<<<<<< HEAD
				if (((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_LEFTTHESIS) || ((LT::GetEntry(mylextable, mylextable.size - 2)).lexema == LEX_COMMA))
=======
				if (((LT::GetEntry(mylextable, mylextable.size -2)).lexema == LEX_LEFTTHESIS) || ((LT::GetEntry(mylextable, mylextable.size -2)).lexema == LEX_COMMA))
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
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
<<<<<<< HEAD
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).value == LEX_INTEGER)
=======
			if ((LT::GetEntry(mylextable, mylextable.size - 1)).lexema == LEX_INTEGER)
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
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
		if (isAStandartFunction)                         //���� ��� ����������� �������
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
				myentryI.id[i] = buff_name[i];               //� ������� ���������������
		myentryI.iddatatype = iddatatype;
		myentryI.idtype = idtype;
		IT::Add(myidtable, myentryI);
		myentryL.idxTI = myidtable.size - 1;
	}

	void analyze(int currentLine, char *fulltextch)                         //������� �������
	{
<<<<<<< HEAD

		std::string fulltext = fulltextch;                         //�������� �����
		std::string onelex[300];                                 //������ ������(�������)
=======
		Tables myTables;

		std::string fulltext = fulltextch;                         //�������� �����
		std::string onelex[250];                                 //������ ������(�������)
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
		int amountOfLex = 0;                              //��� �� ������
		char symvols[] = ";,{}()+-*/=\n";                          //������� ����������
		int *linesForLex = new int[currentLine];                  //������ �������� ���� � �������
		currentLine = 0;

		int LexInIT;                                      // ����� ������ � IT ��� �������

		for (int counter = 0; counter < fulltext.size(); counter++)      //������ ��� ������
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
						throw ERROR_THROW(444)    //���������� ������
						counter--;
				}
				else
				{
					onelex[amountOfLex] += fulltext[counter];
				}
			}
			else
			{
				if (fulltext[counter] != NEWLINE)            //����� ������
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

<<<<<<< HEAD
		Tables myTables;

		myTables.idtable = IT::Create(amountOfLex);                         //�������� ������
		myTables.lextable = LT::Create(amountOfLex);

=======

		myTables.myidtable = IT::Create(amountOfLex);                         //�������� ������
		myTables.mylextable = LT::Create(amountOfLex);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2

		for (int i = 0; i < 5; i++)                //��������� ������ ����
		{
			buff_name[i] = NULL;
		}

		currentLine = 0;

		int identifyLex = 0;         // ��������������� ��������
		for (int i = 0; i < amountOfLex; i++) {
			while (linesForLex[currentLine] <= i)         // ��������� ������
			{
				currentLine++;
			}

			char temp = onelex[i][0];                          //������ ����� �������
			str = onelex[i];
			identifyLex = 0;
			int lex[3];	//0-�����  1-int 2-string 3-����  4-�����  5-������  6-�����  7-�� �   8-;  9-,  10-{  11-}  12-(   13-)   14-=  15-(+-*/)  16-�������
			lex[0] = 0; lex[1] = 0; lex[2] = 0;
			if (temp == '1' || temp == '2' || temp == '3' || temp == '4' || temp == '5' || temp == '6' || temp == '7' || temp == '8' || temp == '9' || temp == '0' || temp == '\'')lex[0] = 16; else {
				switch (temp)       //����������� ���������� ���� �������
				{
				case LEX_ID:
					lex[0] = 1;
					break;
				case LEX_STRING:
					lex[0] = 2;
					lex[1] = 17;
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
<<<<<<< HEAD
				case LEX_SEMICOLON:
=======
				case LEX_SEMICOLON :
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
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
				}      //����������� ���������� ���� �������
			}
			for (int i = 0; i < 3; i++)
			{
				if (lex[i] != 0)
					if ((lex[i] < 8 && lex[i]>0) || lex[i] == 17)         //���� ����� ��������� ���������
					{
						Update(str);
						if (automats.automat[lex[i]] == lex[i])          //�������� ������� �� �������
							identifyLex = lex[i];
					}
					else
					{
						identifyLex = lex[i];                      //�� ������
					}
				else
					lex[i] = 0;
			}


			isAStandartFunction = false;
			for (int i = 0; i < standartFunction->length(); i++)
			{
				if (str == standartFunction[i]) isAStandartFunction = true;
			}

			for (int i = 0; i < str.length() && i < 5; i++)            //����� ���
				buff_name[i] = str[i];
			for (int i = 4; i >= str.length(); i--)
				buff_name[i] = NULL;

<<<<<<< HEAD
			if (identifyLex == 0 || identifyLex == 16 || identifyLex == 10 || identifyLex == 11 || identifyLex == 7)          //���� �������������
=======
			if (identifyLex == 0 || identifyLex == 16 || identifyLex == 10 || identifyLex == 11 || identifyLex == 7 )          //���� �������������
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
			{
				for (int i = 0; i < str.length(); i++)
					buff_name_str[i] = str[i];
				for (int i = 10; i >= str.length(); i--)
					buff_name_str[i] = NULL;
				switch (identifyLex)
				{
<<<<<<< HEAD
				case 7:
=======
				case 7 :
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
					myentryI.areaOfVisibility[0] = 0;
					for (int q = 0; q < 5; q++)
						myentryI.id[q] = buff_name[q];
					myentryI.iddatatype = IT::INT;
					myentryI.idtype = IT::F;
					myentryI.value.vint = 0;
<<<<<<< HEAD
					IT::Add(myTables.idtable, myentryI);
					myentryL.idxTI = myTables.idtable.size - 1;
=======
					IT::Add(myTables.myidtable, myentryI);
					myentryL.idxTI = myTables.myidtable.size - 1;
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
					break;
				case 10:                                                         //������� ���������
					counterOfBracket++;
					counterOfAreaOfVisibility++;
					myentryI.areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
					areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = counterOfBracket;
<<<<<<< HEAD
					bufferi = myTables.lextable.size;
					while (myTables.lextable.table[bufferi].lexema != LEX_LEFTTHESIS && myTables.lextable.table[bufferi].lexema != LEX_MAIN && myTables.lextable.table[bufferi].lexema != LEX_SEMICOLON)
					{
						if (myTables.lextable.table[bufferi].lexema == LEX_ID)
							myTables.idtable.table[myTables.lextable.table[bufferi].idxTI].areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
=======
					bufferi = myTables.mylextable.size;
					while (myTables.mylextable.table[bufferi].lexema != LEX_LEFTTHESIS && myTables.mylextable.table[bufferi].lexema != LEX_MAIN&& myTables.mylextable.table[bufferi].lexema != LEX_SEMICOLON)
					{
						if (myTables.mylextable.table[bufferi].lexema == LEX_ID)
							myTables.myidtable.table[myTables.mylextable.table[bufferi].idxTI].areaOfVisibility[counterOfAreaOfVisibility] = counterOfBracket;
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
						bufferi--;
					}
					break;
				case 11:
					areaOfVisibilityLexAnaliz[counterOfAreaOfVisibility] = NULL;
					myentryI.areaOfVisibility[counterOfAreaOfVisibility] = NULL;
					counterOfAreaOfVisibility--;
					break;
				case 16:                                                             //��������
<<<<<<< HEAD
					myentryI.idxfirstLE = myTables.lextable.size;
=======
					myentryI.idxfirstLE = myTables.mylextable.size;
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
					if (str[0] == '\'')                         //���������
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
					else                               //�������������
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
<<<<<<< HEAD
					IT::Add(myTables.idtable, myentryI);                        //�������� � IT
					myentryL.idxTI = myTables.idtable.size - 1;
					break;
				case 0:
					if (IT::IsId(myTables.idtable, buff_name) == TI_NULLIDX && IT::IsId(myTables.idtable, buff_name_str) == TI_NULLIDX)      //���� �� ��� � ������� ���������������   
					{
						addNewInIT(myTables.idtable, myTables.lextable);
=======
					IT::Add(myTables.myidtable, myentryI);                        //�������� � IT
					myentryL.idxTI = myTables.myidtable.size - 1;
					break;
				case 0:
					if (IT::IsId(myTables.myidtable, buff_name) == TI_NULLIDX && IT::IsId(myTables.myidtable, buff_name_str) == TI_NULLIDX)      //���� �� ��� � ������� ���������������   
					{
						addNewInIT(myTables.myidtable, myTables.mylextable);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
					}
					else
					{
						if (!isAStandartFunction)               //���� �� ����������� �������             
						{
							bufferb = true;
<<<<<<< HEAD
							for (int y = 0; y < myTables.idtable.size; y++)
=======
							for (int y = 0; y < myTables.myidtable.size; y++)
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
							{
								bufferi = 0;
								bufferi1 = 1;
								buffer = "";
								for (int w = 0; w < 5; w++)
<<<<<<< HEAD
									buffer += myTables.idtable.table[y].id[w];
								if (std::strcmp(str.c_str(), buffer.c_str()) == 0)        //���� �������� �������
								{
									while (myTables.idtable.table[y].areaOfVisibility[bufferi1] != 0)  //����� ������� �������� � ������� ��������� ��������������
										bufferi1++;                         //counterOfAreaOfVisibility ����� ���� ������� ��������� ������
									if (bufferi1 == counterOfAreaOfVisibility + 1) {                  //���� ��������� ���� 
										if (myTables.idtable.table[y].areaOfVisibility[bufferi1 - 1] == areaOfVisibilityLexAnaliz[bufferi1 - 1]) //������ ���� ����������
=======
									buffer += myTables.myidtable.table[y].id[w];
								if (std::strcmp(str.c_str(), buffer.c_str()) == 0)        //���� �������� �������
								{
									while (myTables.myidtable.table[y].areaOfVisibility[bufferi1] != 0)  //����� ������� �������� � ������� ��������� ��������������
										bufferi1++;                         //counterOfAreaOfVisibility ����� ���� ������� ��������� ������
									if (bufferi1 == counterOfAreaOfVisibility + 1) {                  //���� ��������� ���� 
										if (myTables.myidtable.table[y].areaOfVisibility[bufferi1 - 1] == areaOfVisibilityLexAnaliz[bufferi1 - 1]) //������ ���� ����������
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
											bufferb = false;
									}
									else {
										for (int q = 0; q < counterOfAreaOfVisibility + 1; q++)
<<<<<<< HEAD
											if (myTables.idtable.table[y].areaOfVisibility[q] != areaOfVisibilityLexAnaliz[q])
=======
											if (myTables.myidtable.table[y].areaOfVisibility[q] != areaOfVisibilityLexAnaliz[q])
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
												bufferb = false;
									}
								}
							}
							if (bufferb)
<<<<<<< HEAD
								addNewInIT(myTables.idtable, myTables.lextable);
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.idtable, buff_name, areaOfVisibilityLexAnaliz);
							myentryL.idxTI = LexInIT;
						}
						else {
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.idtable, buff_name_str, areaOfVisibilityLexAnaliz);
=======
								addNewInIT(myTables.myidtable, myTables.mylextable);
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.myidtable, buff_name, areaOfVisibilityLexAnaliz);
							myentryL.idxTI = LexInIT;
						}
						else {
							LexInIT = IT::IsIdWithAreaOfVisibility(myTables.myidtable, buff_name_str, areaOfVisibilityLexAnaliz);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
							myentryL.idxTI = LexInIT;
						}
					}
				}
				//� � ����� ������ � �������
				myentryL.lexema = automats.lexema[identifyLex];
				myentryL.sn = currentLine;
<<<<<<< HEAD
				LT::Add(myTables.lextable, myentryL);
=======
				LT::Add(myTables.mylextable, myentryL);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
			}
			else                        //���� �� �������������
			{
				if (identifyLex == 15)
					myentryL.value = str[0];
				if (identifyLex == 18) {
					identifyLex = 18;
				}
				myentryL.idxTI = LT_TI_NULLIDX;              //������ � ������� ������
				myentryL.lexema = automats.lexema[identifyLex];
				myentryL.sn = currentLine;
<<<<<<< HEAD
				LT::Add(myTables.lextable, myentryL);
=======
				LT::Add(myTables.mylextable, myentryL);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
				myentryL.value = SPACE;
			}
		}

<<<<<<< HEAD
		//polishNotation(16,myTables.lextable,myTables.idtable);
		//polishNotation(74,myTables.lextable,myTables.idtable);

		MFST_TRACE_START
		MFST::Mfst mfst(myTables, GRB::getGreibach());
		mfst.start();
		mfst.printrules();

		std::ofstream fileLT;               //������������� ������ ������
		fileLT.open("LT.txt");
		LT::showTable(myTables.lextable, fileLT);
=======
		//polishNotation(32,myTables.mylextable,myTables.myidtable);
		//polishNotation(62,myTables.mylextable,myTables.myidtable);

		std::ofstream fileLT;               //������������� ������ ������
		fileLT.open("LT.txt");
		LT::showTable(myTables.mylextable, fileLT);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
		fileLT.close();

		std::ofstream fileLT_mini;
		fileLT_mini.open("LT_mini.txt");
<<<<<<< HEAD
		LT::showTable_mini(myTables.lextable, fileLT_mini);
=======
		LT::showTable_mini(myTables.mylextable, fileLT_mini);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
		fileLT_mini.close();

		std::ofstream fileIT;
		fileIT.open("IT.txt");
<<<<<<< HEAD
		IT::showTable(myTables.idtable, fileIT);
=======
		IT::showTable(myTables.myidtable, fileIT);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
		fileIT.close();
		system("pause");
	}
}