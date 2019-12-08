#include "pch.h"

namespace Semantic
{
	void CheckSemanticAfterPolish(LexA::Tables myTables)
	{
		for (int i = 0; i < myTables.mylextable.size; i++) {       // семантика проверки
			switch (myTables.mylextable.table[i].lexema)
			{
			case LEX_EQUAL:            //проверка на соответсвие типов в выражении
			{
				int j = i;
				IT::IDDATATYPE mainType = myTables.myidtable.table[myTables.mylextable.table[i - 1].idxTI].iddatatype;
				std::stack<IT::IDDATATYPE> tempStack;
				IT::IDDATATYPE tempType;
				while (myTables.mylextable.table[++j].lexema != LEX_SEMICOLON)
				{
					bool correct = false;
					if (myTables.mylextable.table[j].lexema == POLISHFUNCTION)
					{
						std::string tempstr = ""; tempstr += myTables.mylextable.table[j + 1].lexema;
						int x = atoi(tempstr.c_str());
						for (int q = 0; q < x; q++)
							tempStack.pop();
						correct = true;
					}
					if (myTables.mylextable.table[j].idxTI != LT_TI_NULLIDX&& myTables.mylextable.table[j].idxTI != -1)
						tempStack.push(myTables.myidtable.table[myTables.mylextable.table[j].idxTI].iddatatype);
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
			if (myTables.mylextable.table[i].lexema == LEX_EQUAL)
			{
				int k = i;
				int counter = 0;
				while (myTables.mylextable.table[k++].lexema != LEX_SEMICOLON) {
					if (myTables.mylextable.table[k].lexema == LEX_ID || myTables.mylextable.table[k].lexema == LEX_LITERAL)
						counter++;
				}
				if (counter > 8)
					throw ERROR_THROW_IN(162, myTables.mylextable.table[i].sn, 0);
			}

			if (myTables.mylextable.table[i].idxTI != LT_TI_NULLIDX)    //!!!!!!Работает тольк после синтаксического анализа!!!!!!!!!!
			{
				if (myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idtype == IT::F)
				{
					if(myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idxfirstLE==i){
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