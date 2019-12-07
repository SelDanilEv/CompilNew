#include "pch.h"
#include "Generation.h"
#include <stdlib.h>

namespace Generation
{

	std::string WriteSegment(OneSegment segment)
	{
		return ("\n." + segment.Name + '\n' + segment.Code);
	}

	int buffer = 0;
	bool isMain = false;
	OneSegment Stack = { "stack 4096" };
	OneSegment Const = { "const" };
	OneSegment Data = { "data" };
	OneSegment Code = { "code" };

	LT::LexTable lextable;
	IT::IdTable idtable;

	std::stack<std::string> MainStack;

	std::string buffstr = "";

	std::string GetName(int indexInIdTable, bool Variable)
	{
		std::string rc = "";
		rc += (std::string)(char*)idtable.table[indexInIdTable].id;
		if (Variable)
			for (int i = 0; i < 5; i++)
				rc += std::to_string(idtable.table[indexInIdTable].areaOfVisibility[i]);
		return rc;
	}

	void Generate(LexA::Tables tables)
	{
		lextable = tables.mylextable;
		idtable = tables.myidtable;
		std::string Proto;

		IT::Entry helpIEntry;


		Proto = "\nExitProcess PROTO : DWORD\nouttxt PROTO : DWORD\noutlit PROTO : SDWORD\n\tcopytxt PROTO : DWORD,:DWORD\n\ttxtcon PROTO : DWORD,:DWORD\n";//дописать 

		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype != IT::F)
			{
				helpIEntry = idtable.table[i];
				buffer = 0;
				buffstr = "\t";
				switch (idtable.table[i].idtype)
				{
				case IT::V:
					buffstr += GetName(i, true);
					if (helpIEntry.iddatatype == IT::LIT)
						buffstr += " dword ?\n";
					if (helpIEntry.iddatatype == IT::TXT)
					{
						buffstr += " byte 255 dup(0)\n";
					}
					Data.Code += buffstr;
					break;
				case IT::L:
					buffstr += GetName(i, false);
					if (helpIEntry.iddatatype == IT::LIT)
						buffstr += " dword " + std::to_string(helpIEntry.value.vint) + '\n';
					if (helpIEntry.iddatatype == IT::TXT)
					{
						buffstr += " byte ";
						for (int k = 0; k < helpIEntry.value.vstr.len; k++)
							buffstr += helpIEntry.value.vstr.str[k];
						buffstr += ", 0\n";
					}
					Const.Code += buffstr;
					break;
				default:
					break;
				}
			}
			else   //если функция
			{
				if (lextable.table[idtable.table[i].idxfirstLE].lexema == LEX_START)
					isMain = true;
				int lexposition = idtable.table[i].idxfirstLE;
				GenerateFunction(lexposition);
			}
		}
		std::ofstream fileASM;
		fileASM.open(ASM_FILE_PATH);
		fileASM << BEFORE_DATA + Proto + WriteSegment(Stack) + WriteSegment(Const) +
			WriteSegment(Data) + WriteSegment(Code);
		fileASM.close();
	}

	void GenerateFunction(int indexInLexTable)
	{
		while (!MainStack.empty())
			MainStack.pop();
		buffstr = "";
		int counter = 1;
		std::string object;
		std::string name;
		if (!isMain) {
			name = GetName(lextable.table[indexInLexTable].idxTI, false);
			buffstr = "proc_" + name + " proc";
			while (lextable.table[++indexInLexTable].lexema != LEX_LEFTBRACE)
			{
				if (lextable.table[indexInLexTable].lexema == LEX_ID)
				{
					buffstr += ", " + GetName(lextable.table[indexInLexTable].idxTI, true) + " : ";
					if (idtable.table[lextable.table[indexInLexTable].idxTI].iddatatype == IT::LIT)
						buffstr += "dword";
					else
						buffstr += "byte";
				}
			}
		}
		else
		{
			buffstr += "\nmain proc\n\tSTART :";
			indexInLexTable += 2;
		}
		buffstr += '\n';
		for (int i = indexInLexTable + 1; i > 0; i++)
		{
			if (counter < 1)i = -5;
			switch (lextable.table[i].lexema)
			{
			case LEX_RIGHTBRACE:
				counter--;
				break;
			case LEX_LEFTBRACE:
				counter++;
				break;
			case LEX_EQUAL:
			{
				object = GetName(lextable.table[i - 1].idxTI, true);
				bool TypeObject;  //true numb    false text
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::LIT)TypeObject = true; else TypeObject = false;
				while (lextable.table[i].lexema != LEX_SEMICOLON && lextable.table[i].lexema != LATTICE)
				{
					bool isID = false;
					switch (lextable.table[i].lexema)
					{
					case LEX_ID:
						isID = true;
					case LEX_LITERAL:
					{
						if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::LIT)
						{
							buffstr += "\tpush " + GetName(lextable.table[i].idxTI, isID) + '\n';
							MainStack.push(GetName(lextable.table[i].idxTI, isID));
						}
						if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::TXT)
						{
							buffstr += "\tpush offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
							MainStack.push("offset " + GetName(lextable.table[i].idxTI, isID));
						}
						break;
					}
					case POLISHFUNCTION:
					{
						int j = i + 1;
						std::string x = ""; x += lextable.table[i].lexema;
						int numbOfParameters = atoi(x.c_str());
						for (j = 0; j < numbOfParameters; j++)
							buffstr += "\tpop edx\n";
						for (j = 0; j < numbOfParameters; j++)
						{
							buffstr += "\tpush " + MainStack.top() + '\n';
							MainStack.pop();
						}
						buffstr += "\tcall proc_" + GetName(lextable.table[i].idxTI, false) + "\n\tpush eax\n";
						i++;
						break;
					}
					case LEX_OPERATOR:
					{
						switch (lextable.table[i].value)
						{
						case '*':
						{
							buffstr += "\tpop eax\n\tpop ebx\n";
							buffstr += "\tmul ebx\n\tpush eax\n";
							break;
						}
						case '+':
						{
							if (idtable.table[lextable.table[i-1].idxTI].iddatatype == IT::LIT)
							{
								buffstr += "\tpop eax\n\tpop ebx\n";
								buffstr += "\tadd eax, ebx\n\tpush eax\n";
							}
							else
							{
								buffstr += "\tpop eax\n\tpop ebx\n";
								buffstr += "\tcall txtcon\n\tpush eax\n";
							}
							break;
						}
						case '-':
						{
							buffstr += "\tpop ebx\n\tpop eax\n";
							buffstr += "\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						}
						break;
					}
					}
					i++;
				}
				if (TypeObject)
					buffstr += "\tpop " + object + '\n';
				else 
				{
					buffstr += "\tpush offset " + object + '\n';
					buffstr += "\tcall copytxt\n";
				}
				break;
			case LEX_RETURN:
			{
				bool isID = false;
				switch (lextable.table[++i].lexema)
				{
				case LEX_ID:
					isID = true;
				case LEX_LITERAL:
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::LIT)
						buffstr += "\tmov eax," + GetName(lextable.table[i].idxTI, isID) + '\n';
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::TXT)
						buffstr += "\tmov eax, offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
				}
				break;
			}
			case LEX_OUTPUT:
			{
				std::string returned;
				bool isID = false;
				if (idtable.table[lextable.table[i + 2].idxTI].iddatatype == IT::LIT) {
					if (idtable.table[lextable.table[i + 2].idxTI].idtype == IT::V) {
						isID = true;
						returned = GetName(lextable.table[i + 2].idxTI, isID);

						buffstr += "\tpush " + returned + "\n\tcall outlit \n";
					}
				}
				else {
					if (idtable.table[lextable.table[i + 2].idxTI].idtype == IT::V) {
						isID = true;
						returned = GetName(lextable.table[i + 2].idxTI, isID);

						buffstr += "\tpush offset " + returned + "\n\tcall outtxt \n";
					}
				}
				break;
			}
			default:
				if (counter < 1)
					counter--;
				break;
			}
			}
		}
		if (!isMain) {
			buffstr += "\tret\n";
			buffstr += "proc_" + name + " endp";
		}
		else {
			buffstr += "\tpush 0\n\tcall ExitProcess\nmain endp\nend main";
		}
		Code.Code += buffstr;
	}

	//void GenerateHat(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i) {
	//	if (!isMain)
	//	{
	//		helpIEntry = idtable.table[i];
	//		buffer = 0;
	//		buffstr = "proc_";
	//		while (helpIEntry.id[buffer] != NULL)
	//		{
	//			buffstr += helpIEntry.id[buffer++];
	//		}
	//		functionName = buffstr;
	//		buffstr += " proc";
	//		buffer = i + 2;
	//		while (lextable.table[buffer].lexema != LEX_RIGHTTHESIS)
	//		{
	//			if (lextable.table[buffer].lexema == LEX_ID)
	//			{
	//				if (buffer != i + 3)buffstr += ", ";
	//				int m = 0;
	//				while (idtable.table[lextable.table[buffer].idxTI].id[m] != NULL && idtable.table[lextable.table[buffer].idxTI].id[m] != '\0')
	//				{
	//					buffstr += idtable.table[lextable.table[buffer].idxTI].id[m++];
	//				}
	//				for (int k = 0; k < 5; k++)
	//					buffstr += std::to_string(idtable.table[lextable.table[buffer].idxTI].areaOfVisibility[k]);

	//				buffstr += " : ";
	//				if (idtable.table[lextable.table[buffer].idxTI].iddatatype == IT::LIT)
	//					buffstr += "dword";
	//				else
	//					buffstr += "byte";
	//			}
	//			buffer++;
	//		}
	//		buffstr += '\n';
	//		Code.Code += buffstr;
	//	}
	//	else {
	//		Code.Code += "\nmain proc\n\tSTART : \n";
	//	}
	//}

	//void GenerateBody(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i) {
	//	buffstr = "";
	//	int counterLEntries = 0;
	//	int exit = 1;
	//	int startLex = idtable.table[i].idxfirstLE;
	//	int currentLex = startLex;
	//	while (lextable.table[currentLex].lexema != LEX_LEFTBRACE)currentLex++;
	//	int currentLine = lextable.table[++currentLex].sn;
	//	int lastLine = currentLine;
	//	while (exit != 0)
	//	{
	//		switch (lextable.table[currentLex].lexema)
	//		{
	//		case LEX_RIGHTBRACE:
	//			exit--;
	//			break;
	//		case LEX_LEFTBRACE:
	//			exit++;
	//			break;
	//		default:
	//			currentLine = lextable.table[currentLex].sn;
	//			if (lastLine == currentLine)
	//			{
	//				buffstr += lextable.table[currentLex].lexema;
	//				LEntries[counterLEntries++] = lextable.table[currentLex];
	//			}
	//			else
	//			{
	//				switch (buffstr[0])
	//				{
	//				case LEX_NEW:
	//					break;
	//				case LEX_ID:
	//					GenerateExpression(LEntries, counterLEntries, idtable);
	//					break;
	//				case LEX_OUTPUT:
	//					GenerateOutput(LEntries, counterLEntries, idtable);
	//					break;
	//				case LEX_RETURN:
	//					GenerateReturn(LEntries, counterLEntries, idtable);
	//					break;
	//				default:
	//					break;
	//				}
	//				for (int k = counterLEntries - 1; k >= 0; k--) LEntries[k] = Empty;
	//				counterLEntries = 0;
	//				buffstr.clear();
	//				lastLine = currentLine;
	//				currentLex--;
	//			}
	//			break;
	//		}
	//		currentLex++;
	//	}
	//	{
	//		switch (buffstr[0])
	//		{
	//		case LEX_NEW:
	//			break;
	//		case LEX_ID:
	//			GenerateExpression(LEntries, counterLEntries, idtable);
	//			break;
	//		case LEX_OUTPUT:
	//			GenerateOutput(LEntries, counterLEntries, idtable);
	//			break;
	//		case LEX_RETURN:
	//			GenerateReturn(LEntries, counterLEntries, idtable);
	//			break;
	//		default:
	//			break;
	//		}
	//		for (int k = counterLEntries - 1; k >= 0; k--) LEntries[k] = Empty;
	//		counterLEntries = 0;
	//		buffstr.clear();
	//	}
	//	if (!isMain) {
	//		Code.Code += "\tret\n";
	//		Code.Code += functionName + " endp";
	//	}
	//	else {
	//		Code.Code += "\tpush 0\n\tcall ExitProcess\nmain endp\nend main";
	//	}
	//}

	//void GenerateReturn(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable) {
	//	buffstr2 = "";
	//	if (idtable.table[LEntries[1].idxTI].iddatatype == IT::LIT) {
	//		if (idtable.table[LEntries[1].idxTI].idtype == IT::V) {
	//			buffer = 0;
	//			while (idtable.table[LEntries[1].idxTI].id[buffer] != NULL && idtable.table[LEntries[1].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[1].idxTI].id[buffer++];
	//			}
	//			for (int m = 0; m < 5; m++)
	//				buffstr2 += std::to_string(idtable.table[LEntries[1].idxTI].areaOfVisibility[m]);
	//		}
	//		else {
	//			buffer = 0;
	//			while (idtable.table[LEntries[1].idxTI].id[buffer] != NULL && idtable.table[LEntries[1].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[1].idxTI].id[buffer++];
	//			}
	//		}
	//		Code.Code += "\tmov eax, " + buffstr2 + '\n';
	//	}
	//	else {
	//		if (idtable.table[LEntries[1].idxTI].idtype == IT::V) {
	//			buffer = 0;
	//			while (idtable.table[LEntries[1].idxTI].id[buffer] != NULL && idtable.table[LEntries[1].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[1].idxTI].id[buffer++];
	//			}
	//			for (int m = 0; m < 5; m++)
	//				buffstr2 += std::to_string(idtable.table[LEntries[1].idxTI].areaOfVisibility[m]);
	//		}
	//		else {
	//			buffer = 0;
	//			while (idtable.table[LEntries[1].idxTI].id[buffer] != NULL && idtable.table[LEntries[1].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[1].idxTI].id[buffer++];
	//			}
	//		}
	//		Code.Code += "\tmov eax, " + buffstr2 + '\n';
	//	}
	//}

	//void GenerateOutput(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable) {
	//	buffstr2 = "";
	//	if (idtable.table[LEntries[2].idxTI].iddatatype == IT::LIT) {
	//		if (idtable.table[LEntries[2].idxTI].idtype == IT::V) {
	//			buffer = 0;
	//			while (idtable.table[LEntries[2].idxTI].id[buffer] != NULL && idtable.table[LEntries[2].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[2].idxTI].id[buffer++];
	//			}
	//			for (int m = 0; m < 5; m++)
	//				buffstr2 += std::to_string(idtable.table[LEntries[2].idxTI].areaOfVisibility[m]);
	//		}
	//		else {
	//			buffer = 0;
	//			while (idtable.table[LEntries[2].idxTI].id[buffer] != NULL && idtable.table[LEntries[2].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[2].idxTI].id[buffer++];
	//			}
	//		}
	//		Code.Code += "\tpush " + buffstr2 + "\n\tcall outlit \n";
	//	}
	//	else {
	//		if (idtable.table[LEntries[2].idxTI].idtype == IT::V) {
	//			buffer = 0;
	//			while (idtable.table[LEntries[2].idxTI].id[buffer] != NULL && idtable.table[LEntries[2].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[2].idxTI].id[buffer++];
	//			}
	//			for (int m = 0; m < 5; m++)
	//				buffstr2 += std::to_string(idtable.table[LEntries[2].idxTI].areaOfVisibility[m]);
	//		}
	//		else {
	//			buffer = 0;
	//			while (idtable.table[LEntries[2].idxTI].id[buffer] != NULL && idtable.table[LEntries[2].idxTI].id[buffer])
	//			{
	//				buffstr2 += idtable.table[LEntries[2].idxTI].id[buffer++];
	//			}
	//		}
	//		Code.Code += "\tpush offset" + buffstr2 + "\n\tcall outlit \n";
	//	}
	//}

	//void GenerateExpression(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable)
	//{
	//	buffstr2 = "";
	//	buffstr.clear();
	//	Expressions newExpressions;
	//	ForExpression EmptyForEx;
	//	ForExpression tempexpr;
	//	std::string object = "";
	//	buffer = 0;
	//	while (idtable.table[LEntries[0].idxTI].id[buffer] != NULL && idtable.table[LEntries[0].idxTI].id[buffer])
	//	{
	//		object += idtable.table[LEntries[0].idxTI].id[buffer++];
	//	}
	//	for (int m = 0; m < 5; m++)
	//		object += std::to_string(idtable.table[LEntries[0].idxTI].areaOfVisibility[m]);

	//	for (int k = 0; k < counterLEntries + 1; k++) {
	//		if (LEntries[k].lexema == LATTICE)counterLEntries--;
	//	}

	//	newExpressions.size = counterLEntries - 1;
	//	int k;
	//	for (k = 2; k < counterLEntries + 1; k++) {
	//		switch (LEntries[k].lexema)
	//		{
	//		case LEX_OPERATOR:
	//			newExpressions.Elements[k].name = LEntries[k].value;
	//			newExpressions.Elements[k].index = k;
	//			newExpressions.Elements[k].cvalue = o;
	//			break;
	//		case LEX_ID:
	//			newExpressions.Elements[k].cvalue = i;
	//			newExpressions.Elements[k].index = k;
	//			buffer = 0;
	//			newExpressions.Elements[k].name = "";
	//			while (idtable.table[LEntries[k].idxTI].id[buffer] != NULL && idtable.table[LEntries[k].idxTI].id[buffer])
	//			{
	//				newExpressions.Elements[k].name += idtable.table[LEntries[k].idxTI].id[buffer++];
	//			}
	//			for (int m = 0; m < 5; m++)
	//				newExpressions.Elements[k].name += std::to_string(idtable.table[LEntries[k].idxTI].areaOfVisibility[m]);
	//			break;
	//		case LEX_LITERAL:
	//			newExpressions.Elements[k].cvalue = i;
	//			newExpressions.Elements[k].index = k;
	//			buffer = 0;
	//			newExpressions.Elements[k].name = "";
	//			while (idtable.table[LEntries[k].idxTI].id[buffer] != NULL && idtable.table[LEntries[k].idxTI].id[buffer])
	//			{
	//				newExpressions.Elements[k].name += idtable.table[LEntries[k].idxTI].id[buffer++];
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//	bool notrun = true;
	//	while (newExpressions.size != 3) {
	//		notrun = false;
	//		int k = newExpressions.size;
	//		while (newExpressions.Elements[k].cvalue != o || newExpressions.Elements[k - 1].cvalue != i || newExpressions.Elements[k - 2].cvalue != i)
	//		{
	//			k--;
	//		}
	//		tempexpr = doTreade(newExpressions, k);
	//		newExpressions.Elements[k - 2] = tempexpr;
	//		while (newExpressions.Elements[++k].name[0] != ' ')
	//			newExpressions.Elements[k - 2] = newExpressions.Elements[k];
	//		newExpressions.Elements[k] = newExpressions.Elements[k] = EmptyForEx;
	//		newExpressions.size -= 2;
	//	}
	//	if (notrun)         //если предыдущий цикл ни разу не запустился
	//	{
	//		buffstr1 = "";
	//		buffer = 0;
	//		while (idtable.table[LEntries[2].idxTI].id[buffer] != NULL && idtable.table[LEntries[2].idxTI].id[buffer])
	//		{
	//			buffstr1 += idtable.table[LEntries[2].idxTI].id[buffer++];
	//		}
	//		if (idtable.table[LEntries[2].idxTI].idtype != IT::L)
	//			for (int m = 0; m < 5; m++)
	//				buffstr1 += std::to_string(idtable.table[LEntries[2].idxTI].areaOfVisibility[m]);
	//		buffstr2 += "\tmov eax, " + buffstr1 + "\n";
	//		buffstr2 += "\tmov " + object + ",eax\n";
	//	}
	//	else
	//		buffstr2 += "\tmov " + object + ", eax\n";
	//	Code.Code += buffstr2;
	//}

	//ForExpression doTreade(Expressions expr, int k) {
	//	ForExpression rc;
	//	buffstr2 += "\tmov ebx," + expr.Elements[k - 1].name + '\n';
	//	if (expr.Elements[k - 2].name != "ecx")
	//		buffstr2 += "\tmov ecx," + expr.Elements[k - 2].name + '\n';
	//	switch (expr.Elements[k].name[0])
	//	{
	//	case '+':
	//		buffstr2 += "\tadd ecx,ebx\n";
	//		break;
	//	case '-':
	//		buffstr2 += "\tsub ecx,ebx\n";
	//		break;
	//	case '/':
	//		buffstr2 += "\tmov eax,ecx\n";
	//		buffstr2 += "\tmov edx,0\n";
	//		buffstr2 += "\tdiv ebx\n";
	//		buffstr2 += "\tmov ecx,eax\n";
	//		break;
	//	case '%':
	//		buffstr2 += "\tdiv ebx\n";
	//		buffstr2 += "\tmov ecx,edx\n";
	//		break;
	//	case '*':
	//		buffstr2 += "\tmov eax,ecx\n";
	//		buffstr2 += "\tmul ebx\n";
	//		break;
	//	default:
	//		break;
	//	}
	//	rc.cvalue = i;
	//	rc.index = expr.Elements[k - 2].index;
	//	rc.name = "eax";
	//	return rc;
	//}
}