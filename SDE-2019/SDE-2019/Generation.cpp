#include "pch.h"
#include "Generation.h"

namespace Generation
{
	std::string WriteSegment(OneSegment segment)
	{
		return ("\n." + segment.Name + '\n' + segment.Code);
	}

	int buffer = 0;
	OneSegment Stack = { "stack","4096" };
	OneSegment Const = { "const" };
	OneSegment Data = { "data" };
	OneSegment Code = { "code" };
	std::string helpstr = "";
	std::string helpstr1 = "";
	std::string helpstr2 = "";  //

	void Generate(LexA::Tables tables)
	{
		LT::LexTable lextable = tables.mylextable;
		IT::IdTable idtable = tables.myidtable;
		std::string Proto;
		std::string fullCode = "";

		LT::Entry helpLEntry;
		IT::Entry helpIEntry;


		Proto = "\nExitProcess PROTO : DWORD\n";//дописать

		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype != IT::F)
			{
				helpIEntry = idtable.table[i];
				buffer = 0;
				helpstr = "\t";
				switch (idtable.table[i].idtype)
				{
				case IT::V:
					while (helpIEntry.id[buffer] != NULL && helpIEntry.id[buffer] != '\0')
					{
						helpstr += helpIEntry.id[buffer++];
					}
					for (int k = 0; k < 5; k++)
						helpstr += std::to_string(helpIEntry.areaOfVisibility[k]);
					if (helpIEntry.iddatatype == IT::LIT)
						helpstr += " dword 0\n";
					if (helpIEntry.iddatatype == IT::TXT)
					{
						helpstr += " byte 255 dup(0)\n";
					}
					Data.Code += helpstr;
					break;
				case IT::L:
					while (helpIEntry.id[buffer] != NULL && helpIEntry.id[buffer] != '\0')
					{
						helpstr += helpIEntry.id[buffer++];
					}
					if (helpIEntry.iddatatype == IT::LIT)
						helpstr += " dword " + std::to_string(helpIEntry.value.vint) + '\n';
					if (helpIEntry.iddatatype == IT::TXT)
					{
						helpstr += " byte ";
						for (int k = 0; k < helpIEntry.value.vstr.len; k++)
							helpstr += helpIEntry.value.vstr.str[k];
						helpstr += ", 0\n";
					}
					Const.Code += helpstr;
					break;
				default:
					break;
				}
			}
			else   //если функция
			{
				if (lextable.table[idtable.table[i].idxfirstLE].lexema != LEX_START)
				{
					GenerateFunction(idtable, lextable, helpIEntry, i);
				}
			}
		}

		fullCode += BEFORE_DATA + Proto + WriteSegment(Stack) + WriteSegment(Const) +
			WriteSegment(Data) + WriteSegment(Code);
		std::ofstream fileASM;
		fileASM.open(ASM_FILE_PATH);
		fileASM << fullCode;
		fileASM.close();
	}

	void GenerateFunction(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i)
	{
		GenerateHat(idtable, lextable, helpIEntry, i);
		GenerateBody(idtable, lextable, helpIEntry, i);
	}

	void GenerateHat(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i) {
		helpIEntry = idtable.table[i];
		buffer = 0;
		helpstr = "proc_";
		while (helpIEntry.id[buffer] != NULL)
		{
			helpstr += helpIEntry.id[buffer++];
		}
		helpstr += " proc";
		buffer = i + 2;
		while (lextable.table[buffer].lexema != LEX_RIGHTTHESIS)
		{
			if (lextable.table[buffer].lexema == LEX_ID)
			{
				if (buffer != i + 3)helpstr += ", ";
				helpstr += "parameter_";
				int m = 0;
				while (idtable.table[lextable.table[buffer].idxTI].id[m] != NULL)
				{
					helpstr += helpIEntry.id[m++];
				}
				helpstr += " : ";
				if (idtable.table[lextable.table[buffer].idxTI].iddatatype == IT::LIT)
					helpstr += "dword";
				else
					helpstr += "byte";
			}
			buffer++;
		}
		helpstr += '\n';
		Code.Code += helpstr;
	}

	void GenerateBody(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i) {
		LT::Entry* LEntries;
		LT::Entry Empty;
		int counterLEntries = 0;
		int exit = 1;
		int startLex = idtable.table[i].idxfirstLE;
		int currentLex = startLex;
		while (lextable.table[currentLex].lexema != LEX_LEFTBRACE)currentLex++;
		int currentLine = lextable.table[++currentLex].sn;
		int lastLine = currentLine;
		while (exit != 0)
		{
			switch (lextable.table[currentLex].lexema)
			{
			case LEX_RIGHTBRACE:
				exit--;
				break;
			case LEX_LEFTBRACE:
				exit++;
				break;
			default:
				currentLine = lextable.table[++currentLex].sn;
				if (lastLine == currentLine)
				{
					helpstr += lextable.table[currentLex].lexema;
					LEntries[counterLEntries++] = lextable.table[currentLex];
				}
				else
				{
					switch (helpstr[0])
					{
					case LEX_NEW:
						break;
					case LEX_ID:
						GenerateExpression(LEntries, counterLEntries, idtable);
						break;
					default:
						break;
					}
					for (int k = counterLEntries - 1; k >= 0; k--) LEntries[k] = Empty;
					helpstr.clear();
				}
				break;
			}
			currentLex++;
		}
	}

	void GenerateExpression(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable)
	{
		helpstr2 = "";
		helpstr.clear();
		Expressions newExpressions;
		ForExpression tempexpr;
		std::string object = "";
		buffer = 0;
		while (idtable.table[LEntries[0].idxTI].id[buffer] != NULL && idtable.table[LEntries[0].idxTI].id[buffer])
		{
			object += idtable.table[LEntries[0].idxTI].id[buffer++];
		}
		for (int m = 0; m < 5; m++)
			object += std::to_string(idtable.table[LEntries[0].idxTI].areaOfVisibility[m]);

		for (int k = 0; k < counterLEntries - 1; k++) {
			if (LEntries[k].lexema = LATTICE)counterLEntries--;
		}
		newExpressions.size = counterLEntries - 1;

		for (int k = 2; k < counterLEntries - 1; k++) {
			switch (LEntries[k].lexema)
			{
			case LEX_OPERATOR:
				newExpressions.Elements[k].name = LEntries[k].value;
				newExpressions.Elements[k].index = k;
				newExpressions.Elements[k].cvalue = o;
				break;
			case LEX_ID:
				newExpressions.Elements[k].cvalue = i;
				newExpressions.Elements[k].index = k;
				buffer = 0;
				newExpressions.Elements[k].name = "";
				while (idtable.table[LEntries[k].idxTI].id[buffer] != NULL && idtable.table[LEntries[k].idxTI].id[buffer])
				{
					newExpressions.Elements[k].name += idtable.table[LEntries[k].idxTI].id[buffer++];
				}
				for (int m = 0; m < 5; m++)
					newExpressions.Elements[k].name += std::to_string(idtable.table[LEntries[k].idxTI].areaOfVisibility[m]);
				break;
			case LEX_LITERAL:
				newExpressions.Elements[k].cvalue = i;
				newExpressions.Elements[k].index = k;
				buffer = 0;
				newExpressions.Elements[k].name = "";
				while (idtable.table[LEntries[k].idxTI].id[buffer] != NULL && idtable.table[LEntries[k].idxTI].id[buffer])
				{
					newExpressions.Elements[k].name += idtable.table[LEntries[k].idxTI].id[buffer++];
				}
				break;
			default:
				break;
			}
		}
		while (newExpressions.size != 1) {
			int k = newExpressions.size;
			while (newExpressions.Elements[k].cvalue != o || newExpressions.Elements[k - 1].cvalue != i || newExpressions.Elements[k - 2].cvalue != i)
			{
				k--;
			}
			tempexpr = doTreade(newExpressions, k);

		}

	}

	ForExpression doTreade(Expressions expr, int k) {
		ForExpression rc;
		helpstr2 += "\tmov eax,"+expr.Elements[k-1].name+'\n';
		helpstr2 += "\tmov ebx,"+expr.Elements[k-2].name+'\n';
		switch (expr.Elements[k].name[0])
		{
		case '+':
			break;
			helpstr2 += "\tadd eax,ebx\n";
		case '-':
			break;
			helpstr2 += "\tsub eax,ebx\n";
		case '/':
			break;
			helpstr2 += "\tdiv ebx\n";
		case '%':
			break;
			helpstr2 += "\tdiv ebx\n";
			helpstr2 += "\tmov eax,edx\n";
		case '*':
			helpstr2 += "\tmul eax,ebx\n";
			break;
		default:
			break;
		}


		return rc;
	}

	//void generateExpression(std::vector<LT::Entry>& tempEntries, std::string& Code , int idxTI, IT::IdTable idtable, IT::IDDATATYPE type)
	//{
	//	int begin = 0; int end = 0; int count = 0;
	//	for (size_t j = 0; j < tempEntries.size(); j++)
	//	{
	//		if (tempEntries[j].lexema == '@')
	//		{
	//			count = int(tempEntries[j + 1].lexema);
	//			begin = j - count - 1;
	//		}
	//		if (tempEntries[j].lexema == '_')
	//		{
	//			end = j - 1;
	//		}
	//		if (begin && end && count != 1 && strcmp((const char*)idtable.table[tempEntries[begin - 1].idxTI].id, "strcon") != 0)
	//		{
	//			while (end >= begin)
	//			{
	//				std::swap(tempEntries[begin++], tempEntries[end--]);
	//			}
	//			end = 0;
	//			begin = 0;
	//		}

	//	}
	//	for (size_t i = 0; i < tempEntries.size(); i++)
	//	{
	//		switch (tempEntries[i].lexema)
	//		{
	//		case LEX_LITERAL:
	//		case LEX_ID:		helpstr += (generateInstructions(PUSH, tempEntries[i].idxTI, idtable));	break;
	//		case LEX_SEMICOLON: CS.add(generateInstructions(SEM, idxTI, idtable));	break;
	//		case LEX_PLUS:		if (type == IT::LIT)
	//			CS.add(generateInstructions(ADD, tempEntries[i].idxTI, idtable));
	//							else
	//			CS.add(generateInstructions(ADDSTR, tempEntries[i].idxTI, idtable));	break;
	//		case LEX_STAR:		CS.add(generateInstructions(MUL, tempEntries[i].idxTI, idtable));	break;
	//		case LEX_MINUS:		CS.add(generateInstructions(DIFF, tempEntries[i].idxTI, idtable));	break;
	//		case LEX_DIRSLASH:	CS.add(generateInstructions(DIV, tempEntries[i].idxTI, idtable));	break;
	//		case '!':			CS.add(generateInstructions(UDIFF, NULL, idtable));	break;
	//		case '_':			CS.add(generateInstructions(CALL, tempEntries[i].idxTI, idtable));	break;
	//		}
	//	};
	//	tempEntries.clear();
	//}

	//std::string	generateInstructions(INSTRUCTIONTYPE t, int idxTI, IT::IdTable iT, IT::IDDATATYPE type, std::string fucn_name)
	//{
	//	std::string str; static int ret = 0;
	//	switch (t)
	//	{
	//	case FUNC:
	//		str += "\n\n"; str += fucn_name; str += " PROC";
	//		return str;
	//		break;
	//	case PARM:
	//		str += ", "; str += iT.table[idxTI].id; str += " : ";
	//		switch (type)
	//		{
	//		case IT::TXT: str += "DWORD"; ret += 4;  return str; break;
	//		case IT::LIT: str += "SDWORD"; ret += 4;   return str; break;
	//		}
	//		break;
	//	case PUSH:	if ((iT.table[idxTI].iddatatype == IT::LIT || iT.table[idxTI].idtype == IT::P) && iT.table[idxTI].idtype != IT::F)
	//	{
	//		str += "\n\tpush "; str += iT.table[idxTI].id;
	//	}
	//				else if (iT.table[idxTI].idtype != IT::F)
	//	{
	//		str += "\n\tpush offset ";	str += iT.table[idxTI].id;
	//	}
	//				return str;
	//				break;
	//	case RET:	if (idxTI)
	//		return "\n\tpush 0\n\tcall ExitProcess\n";
	//				else
	//	{
	//		char str[30]; char buf[4];
	//		std::strcpy(str, "\n\tpop eax\n\tret ");
	//		_itoa(ret, buf, 10);
	//		std::strcat(str, buf);
	//		std::strcat(str, "\n");
	//		ret = 0;
	//		return str;  break;
	//	}
	//	case ADD:	return "\n\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
	//	case ADDSTR:	return "\n\tcall strcon\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
	//	case UDIFF: return "\n\tpop eax\n\tneg eax\n\tpush eax";
	//	case DIFF:	return "\n\tpop eax\n\tneg eax\n\tpop ebx\n\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
	//	case MUL:	return "\n\tpop eax\n\tpop ebx\n\timul eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax"; break;
	//	case DIV:	return "\n\tpop ebx\n\tpop eax\n\ttest ebx,ebx\n\tjz EXIT_DIV_ON_NULL\n\tcdq\n\tidiv ebx\n\tpush eax"; break;
	//	case ENDP:	str += "\n"; str += fucn_name; str += " ENDP";
	//		switch ((strcmp(fucn_name.c_str(), "main") == 0) ? true : false)
	//		{
	//		case true: str += "\nend main"; return str;
	//		case false:						return str;
	//		}
	//		break;
	//	case PRNT:	if (type == IT::TXT)
	//		return "\n\tcall outstr\n";
	//				else
	//		return "\n\tcall outint\n"; break;
	//	case SEM:	if (idxTI != -1 && iT.table[idxTI].iddatatype == IT::LIT && iT.table[idxTI].idtype != IT::F) {
	//		str += "\n\tpop "; str += iT.table[idxTI].id;
	//	}
	//				else if (idxTI != -1 && iT.table[idxTI].iddatatype == IT::TXT) {  // Если это строковый литерал
	//		str += "\n\tpush offset "; str += iT.table[idxTI].id;
	//		str += "\n\tcall copystr\n";
	//	}	return str; break;

	//	case CALL:  str += "\n\tcall "; str += iT.table[idxTI].id;
	//		str += "\n\tpush eax";
	//		return str; break;
	//	}
	//}

};