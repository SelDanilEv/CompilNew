#include "pch.h"

namespace Semantic
{
	void CheckSemantic(LexA::Tables myTables) 
	{
		std::string mainFunctionStrName = "start";           //проверка на существованик функции main
		if (IT::IsId(myTables.myidtable, (unsigned char*)mainFunctionStrName.c_str()) == TI_NULLIDX) throw ERROR_THROW(123);
		//check parameters
		for (int i = 0; i < myTables.mylextable.size; i++) {       // семантика проверки
			if (myTables.mylextable.table[i].idxTI != LT_TI_NULLIDX && myTables.mylextable.table[i].lexema != LEX_START)    //!!!!!!Работает тольк после синтаксического анализа!!!!!!!!!!
			{
				if (myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idtype == IT::F)
				{
					int k = i;
					int counterMain = 0;
					int counterObs = 0;
					IT::IDDATATYPE *typeParamMainFunc = new IT::IDDATATYPE[10];
					IT::IDDATATYPE *typeParamObsFunc = new IT::IDDATATYPE[10];

					for (int q = 0; q < 10; q++)
					{
						typeParamMainFunc[q] = typeParamObsFunc[q] = IT::Err;
					}

					while (myTables.mylextable.table[++k].lexema != LEX_RIGHTTHESIS)    //наблюдаемая функция
					{
						if (myTables.mylextable.table[k].lexema == LEX_LITERAL || myTables.mylextable.table[k].lexema == LEX_ID)
						{
							typeParamObsFunc[counterObs++] = myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype;
						}
					}

					k = myTables.myidtable.table[myTables.mylextable.table[i].idxTI].idxfirstLE;  // take numb in lex table

					while (myTables.mylextable.table[++k].lexema != LEX_RIGHTTHESIS)    //главная функция
					{
						if (myTables.mylextable.table[k].lexema == LEX_LITERAL || myTables.mylextable.table[k].lexema == LEX_ID)
						{
							typeParamMainFunc[counterMain++] = myTables.myidtable.table[myTables.mylextable.table[k].idxTI].iddatatype;
						}
					}

					// check
					bool flag = false;
					for (int q = 0; q < 10; q++)
					{
						if ((typeParamMainFunc[q] != typeParamObsFunc[q]))
							flag = true;
					}

					if (flag)
						throw ERROR_THROW(129);
				}
			}
		}

	}
}