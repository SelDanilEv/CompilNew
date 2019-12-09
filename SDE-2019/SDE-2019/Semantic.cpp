#include "pch.h"

namespace Semantic
{
	void CheckSemanticAfterPolish(LexA::Tables myTables)
	{
		int counter = 0;
		int k;
		for (int i = 0; i < myTables.mylextable.size; i++) {       // семантика проверки
			switch (myTables.mylextable.table[i].lexema)
			{
			case LEX_FROM:
				if (myTables.myidtable.table[myTables.mylextable.table[i + 2].idxTI].iddatatype != IT::LIT || myTables.myidtable.table[myTables.mylextable.table[i + 6].idxTI].iddatatype != IT::LIT)
					throw ERROR_THROW_IN(163, myTables.mylextable.table[i].sn, 0);
				k = i;
				while(myTables.mylextable.table[++k].lexema==LEX_RIGHTBRACE&&counter==1)
					switch (myTables.mylextable.table[k].lexema)
					{
					case LEX_FROM:
						throw ERROR_THROW_IN(168, myTables.mylextable.table[k].sn,0);
						break;
					case LEX_LEFTBRACE:
						counter++;
						break;
					case LEX_RIGHTBRACE	:
						counter--;
						break;
					default:
						break;
					}
				break;
			case LEX_EQUAL:            //проверка на соответсвие типов в выражении
			{
				if (myTables.mylextable.table[i - 3].lexema == LEX_CHECK) {
					if (myTables.myidtable.table[myTables.mylextable.table[i - 1].idxTI].iddatatype != IT::LIT ||
						myTables.myidtable.table[myTables.mylextable.table[i + 1].idxTI].iddatatype != IT::LIT)
						throw ERROR_THROW_IN(166, myTables.mylextable.table[i].sn, 0);
					break;
				}
				int j = i;
				bool isText = false;
				IT::IDDATATYPE mainType;
				//if (myTables.mylextable.table[i - 1].value == LEX_LIBFUNCTION) 

				mainType = myTables.myidtable.table[myTables.mylextable.table[i - 1].idxTI].iddatatype;
				std::stack<IT::IDDATATYPE> tempStack;
				IT::IDDATATYPE tempType;

				if (mainType == IT::TXT)
					isText = true;

				while (myTables.mylextable.table[++j].lexema != LEX_SEMICOLON && myTables.mylextable.table[j].lexema != LATTICE)
				{
					if (myTables.mylextable.table[j].lexema == LEX_OPERATOR&&isText)
						if (myTables.mylextable.table[j].value != '+')
							throw ERROR_THROW_IN(164, myTables.mylextable.table[j].sn, 0);
					if (myTables.mylextable.table[j].lexema == POLISHFUNCTION)
					{
						std::string tempstr = ""; tempstr += myTables.mylextable.table[j + 1].lexema;
						int x = atoi(tempstr.c_str());
						for (int q = 0; q < x; q++)
							tempStack.pop();
					}
					switch (myTables.mylextable.table[j].idxTI)
					{
					case -1:
					case LT_TI_NULLIDX:
						break;
					case -2:
						tempStack.push(IT::LIT);
						break;
					case -3:
						tempStack.push(IT::TXT);
						break;
					default:
						tempStack.push(myTables.myidtable.table[myTables.mylextable.table[j].idxTI].iddatatype);
						break;
					}

				}
				for (int q = 0; q < tempStack.size(); q++)
				{
					tempType = tempStack.top(); tempStack.pop();
					if (mainType != tempType)
						throw ERROR_THROW_IN(157, myTables.mylextable.table[i].sn, 0);
				}
				break;
			}
			default:
				break;
			}
		}
	}

	void CheckSemanticBeforePolish(LexA::Tables myTables)
	{
		std::string mainFunctionStrName = "start";           //проверка на существованик функции main
		if (IT::IsId(myTables.myidtable, (unsigned char*)mainFunctionStrName.c_str()) == TI_NULLIDX) throw ERROR_THROW(151);
		//check parameters
		for (int i = 0; i < myTables.mylextable.size; i++) {       // семантика проверки
			if (myTables.mylextable.table[i].lexema == LEX_DIRSLASH && myTables.mylextable.table[i].value == '/')
			{
				if (myTables.mylextable.table[i + 1].idxTI != TI_NULLIDX) {
					if (myTables.mylextable.table[i + 1].lexema != LEX_LEFTTHESIS)
						if (myTables.myidtable.table[myTables.mylextable.table[i + 1].idxTI].iddatatype == IT::LIT && myTables.myidtable.table[myTables.mylextable.table[i + 1].idxTI].idtype == IT::L) {
							if (myTables.myidtable.table[myTables.mylextable.table[i + 1].idxTI].value.vint == 0)
								throw ERROR_THROW_IN(2, myTables.mylextable.table[i].sn, 0);
						}
				}
			}


			if (myTables.mylextable.table[i].lexema == LEX_EQUAL && myTables.mylextable.table[i-3].lexema != LEX_CHECK)
			{
				int k = i;
				int counter = 0;
				bool isCheckLibFunction = false;
				int stateCheckLibFunction = -1;
				int neededParams = 0;
				while (myTables.mylextable.table[k++].lexema != LEX_SEMICOLON) {
					if (myTables.mylextable.table[k].value == LEX_LIBFUNCTION) {
						if (myTables.mylextable.table[k].idxTI == -2) {
							stateCheckLibFunction = 0;
							neededParams = 1;
						}
						else {
							stateCheckLibFunction = 1;
							neededParams = 2;
						}
						isCheckLibFunction = true;
					}
					if (myTables.mylextable.table[k].lexema == LEX_RIGHTTHESIS)isCheckLibFunction = false;
					if ((myTables.mylextable.table[k].lexema == LEX_ID || myTables.mylextable.table[k].lexema == LEX_LITERAL) && myTables.mylextable.table[k].value != LEX_LIBFUNCTION)
					{
						if (isCheckLibFunction) {
							neededParams--;
							if (stateCheckLibFunction == 0) {
								if (myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype != IT::TXT)
									throw ERROR_THROW_IN(155, myTables.mylextable.table[k].sn, 0);
							}
							else {
								if (myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype != IT::TXT)
									throw ERROR_THROW_IN(155, myTables.mylextable.table[k].sn, 0);
							}
						}
						counter++;
					}
				}
				if (neededParams != 0)
					throw ERROR_THROW_IN(156, myTables.mylextable.table[i].sn, 0);
				if (counter > 8)
					throw ERROR_THROW_IN(162, myTables.mylextable.table[i].sn, 0);
			}


			if (myTables.mylextable.table[i].idxTI != LT_TI_NULLIDX)    //!!!!!!Работает тольк после синтаксического анализа!!!!!!!!!!
			{
				if (myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idtype == IT::F)
				{
					if (myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idxfirstLE == i) {
						int k = i;
						IT::IDDATATYPE funcType = myTables.myidtable.table[myTables.mylextable.table[i].idxTI].iddatatype;
						IT::IDDATATYPE returnedType;
						while (myTables.mylextable.table[k].lexema != LEX_LEFTBRACE)
							k++;
						int numbOfBraces = 1;
						bool isreturn = false;
						while (numbOfBraces != 0) {
							switch (myTables.mylextable.table[++k].lexema)
							{
							case LEX_LEFTBRACE:
								numbOfBraces++;
								break;
							case LEX_RIGHTBRACE:
								numbOfBraces--;
								break;
							case LEX_RETURN:
								isreturn = true;
								k++;
								returnedType = myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype;
								numbOfBraces = 0;
								break;
							default:
								break;
							}
						}
						if (!isreturn)
							throw ERROR_THROW_IN(160, myTables.mylextable.table[i].sn, 0);
						if (funcType != returnedType)
							throw ERROR_THROW_IN(161, myTables.mylextable.table[i].sn, 0);
					}
				}
				if (myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idtype == IT::F && myTables.mylextable.table[i].lexema != LEX_START)
				{
					int k = i;
					int counterMain = 0;
					int counterObs = 0;
					IT::IDDATATYPE *typeParamMainFunc = new IT::IDDATATYPE[8];
					IT::IDDATATYPE *typeParamObsFunc = new IT::IDDATATYPE[8];

					for (int q = 0; q < 8; q++)
					{
						typeParamMainFunc[q] = typeParamObsFunc[q] = IT::Err;
					}

					while (myTables.mylextable.table[++k].lexema != LEX_RIGHTTHESIS)    //наблюдаемая функция
					{
						if (myTables.mylextable.table[k].lexema == LEX_LITERAL || myTables.mylextable.table[k].lexema == LEX_ID)
						{
							typeParamObsFunc[counterObs++] = myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype;
							if (counterObs > 8)
								throw ERROR_THROW_IN(158, myTables.mylextable.table[i].sn, 0);
						}
					}

					k = myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idxfirstLE;  // take numb in lex table

					while (myTables.mylextable.table[++k].lexema != LEX_RIGHTTHESIS)    //главная функция
					{
						if (myTables.mylextable.table[k].lexema == LEX_LITERAL || myTables.mylextable.table[k].lexema == LEX_ID) {
							typeParamMainFunc[counterMain++] = myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype;
							if (counterMain > 8)
								throw ERROR_THROW_IN(159, myTables.mylextable.table[i].sn, 0);
						}
					}

					// check
					bool flag = false;
					for (int q = 0; q < 8; q++)
					{
						if ((typeParamMainFunc[q] == IT::Err&&typeParamObsFunc[q] != IT::Err) || (typeParamMainFunc[q] != IT::Err&&typeParamObsFunc[q] == IT::Err))
							throw ERROR_THROW_IN(156, myTables.mylextable.table[i].sn, 0);

						if ((typeParamMainFunc[q] != typeParamObsFunc[q]))
							flag = true;
					}

					if (flag)
						throw ERROR_THROW_IN(155, myTables.mylextable.table[i].sn, 0);
				}
			}
		}

	}
}