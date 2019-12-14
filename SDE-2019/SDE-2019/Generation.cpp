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

	int countOfCycles = 1;
	int countOfChecks = 1;
	int numbOfBracesCyc;
	int numbOfBracesChc;
	bool IsCycleForIDAndLITERALS = false;
	bool IsCycle = false;
	bool IsCheckForIDAndLITERALS = false;
	bool IsCheck = false;
	bool isID;
	bool isCheck;
	bool thereisnot=false;

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

	std::string Generate(LexA::Tables tables)
	{
		lextable = tables.mylextable;
		idtable = tables.myidtable;
		std::string Proto;

		IT::Entry helpIEntry;


		Proto = "\nExitProcess PROTO : DWORD\nouttxt PROTO : DWORD\noutlit PROTO : SDWORD\ncopytxt PROTO : DWORD,:DWORD\ntxtcon PROTO : DWORD,:DWORD,:DWORD\ncleartxt PROTO : DWORD\nsleep PROTO\ntextlenght PROTO : DWORD\n";//дописать 
		Data.Code += "\tbuf byte 255 dup(0)\n";
		Const.Code += "\tmesdivbyzero byte 'Divide by zero',0\n";
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
						buffstr += " sdword ?\n";
					if (helpIEntry.iddatatype == IT::TXT)
					{
						buffstr += " byte 255 dup(0)\n";
					}
					Data.Code += buffstr;
					break;
				case IT::L:
					buffstr += GetName(i, false);
					if (helpIEntry.iddatatype == IT::LIT)
						buffstr += " sdword " + std::to_string(helpIEntry.value.vint) + '\n';
					if (helpIEntry.iddatatype == IT::TXT)
					{
						Data.Code += buffstr + "T byte 255 dup(0)\n";
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
		return BEFORE_DATA + Proto + WriteSegment(Stack) + WriteSegment(Const) +
			WriteSegment(Data) + WriteSegment(Code);
	}

	void GenerateFunction(int indexInLexTable)
	{
		while (!MainStack.empty())
			MainStack.pop();
		buffstr = "\n";
		int counter = 0;
		std::string object;
		std::string name;
		if (!isMain) {
			name = GetName(lextable.table[indexInLexTable].idxTI, false);
			buffstr = "\nproc_" + name + " proc";
			while (lextable.table[++indexInLexTable].lexema != LEX_LEFTBRACE)
			{
				if (lextable.table[indexInLexTable].lexema == LEX_ID)
				{
					buffstr += ", " + GetName(lextable.table[indexInLexTable].idxTI, true) + " : ";
					if (idtable.table[lextable.table[indexInLexTable].idxTI].iddatatype == IT::LIT)
						buffstr += "dword";
					else
						buffstr += "ptr dword";
				}
			}
		}
		else
		{
			buffstr += "\nmain proc\n\tSTART :";
			indexInLexTable += 2;
		}
		buffstr += '\n';
		if (isMain)indexInLexTable--;
		for (int i = indexInLexTable; i > 0; i++)
		{
			isID = false;
			if (counter < 0)i = -5;
			switch (lextable.table[i].lexema)
			{
			case LEX_RIGHTBRACE:
				counter--;
				if (IsCycle)
					if (counter == numbOfBracesCyc)
					{
						IsCycle = false;
						buffstr += "\tmov eax,cycleisneg" + std::to_string(countOfCycles - 1) + "\n\tcmp eax,0\n\tje iter" + std::to_string(countOfCycles - 1) +
							"\n\tsub buffer00000,1\n\tjmp enditer" + std::to_string(countOfCycles - 1) + "\niter" + std::to_string(countOfCycles - 1) + ":\n" +
							"\tadd buffer00000,1\n\tenditer" + std::to_string(countOfCycles - 1) + ":\njmp "+ (std::string)ASMCYCLE + std::to_string(countOfCycles - 1)+'\n'+
							(std::string)ASMCYCLEOUT + std::to_string(countOfCycles - 1) +":\n";
					}
				if(IsCheck)
					if (counter == numbOfBracesChc)
					{
						if (lextable.table[i + 1].lexema != LEX_NOT) {
							if (thereisnot == false) {
								buffstr += (std::string)ASMCHECKNOT + std::to_string(countOfChecks - 1) + " :\n";
							}
							else {
								buffstr += (std::string)ASMCHECK + std::to_string(countOfChecks - 1) + " :\n";
							}
							IsCheck = thereisnot = false;
						}
						else {
							thereisnot = true;
							buffstr +="jmp "+ (std::string)ASMCHECK + std::to_string(countOfChecks - 1) + "\n";
							buffstr += (std::string)ASMCHECKNOT + std::to_string(countOfChecks - 1) + " :\n";
						}
					}
				break;
			case LEX_LEFTBRACE:
				counter++;
				break;
			case LEX_FROM:
				IsCycleForIDAndLITERALS = IsCycle = true;
				numbOfBracesCyc = counter;
				break;
			case LEX_CHECK:
				IsCheckForIDAndLITERALS = IsCheck = true;
				numbOfBracesChc = counter;
				break;
			case LEX_ENDCONDCYCL:
				IsCycleForIDAndLITERALS = false;
				//buffstr += "\tpop eax\n\tpop ebx\n\tmov buffer00000,ebx\n\tsub eax,ebx\n\tmov ecx,eax\n";
				buffstr += "\tpop eax\n\tpop ebx\n\tmov edx,eax\n\tsub eax,ebx\n\tcmp eax,0\n\tjl negative" + std::to_string(countOfCycles) + "\n" +
					"\tmov buffer00000,ebx\n\tmov ecx,eax\n\tmov eax,0\n\tmov cycleisneg" + std::to_string(countOfCycles) +
					",eax\n\tjmp endcondcycle" + std::to_string(countOfCycles) +
					"\nnegative" + std::to_string(countOfCycles) + " :\n\tmov buffer00000,ebx\n\tneg eax\n\tmov ecx,eax\n\tadd ecx,1\n" +
					"\tmov eax,1\n\tmov cycleisneg" + std::to_string(countOfCycles) + ",eax\nendcondcycle" + std::to_string(countOfCycles) + " :\n\tpush ecx\n";
				Data.Code += "\tcycleisneg"+ std::to_string(countOfCycles) + " dword 0\n";
				buffstr += (std::string)ASMCYCLE + std::to_string(countOfCycles++) + ":"+ "\pop ecx\n\tcmp ecx,0\nje " + (std::string)ASMCYCLEOUT + std::to_string(countOfCycles - 1) +"\n\tsub ecx,1\n\tpush ecx\n";
				break;
			case LEX_ENDCHECK:
				buffstr += "\tpop eax\n\tpop ebx\n\tcmp eax,ebx\n\tjne "+
					(std::string)ASMCHECKNOT + std::to_string(countOfChecks++) +"\n";
				IsCheckForIDAndLITERALS = false;
				thereisnot = false;
				break;
			case LEX_EQUAL:
			{
				if (lextable.table[i - 3].lexema == LEX_CHECK)
					break;
				object = GetName(lextable.table[i - 1].idxTI, true);
				if (idtable.table[lextable.table[i - 1].idxTI].idtype == IT::V && !isMain)
					if(idtable.table[lextable.table[i - 1].idxTI].iddatatype!=IT::LIT)
					object = "offset " + object;
				bool TypeObject;  //true numb    false text
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::LIT)TypeObject = true; else TypeObject = false;
				while (lextable.table[i].lexema != LEX_SEMICOLON && lextable.table[i].lexema != LATTICE)
				{
					isID = false;
					switch (lextable.table[i].lexema)
					{
					case LEX_ID:
						isID = true;
					case LEX_LITERAL:
					{
						if (lextable.table[i].value == LEX_LIBFUNCTION) {
							switch (lextable.table[i].idxTI)
							{
							case -2:
								buffstr += "\tpush textlenght\n";
								MainStack.push("textlenght");
								break;
							case -3:
								buffstr += "\tpush copytxt\n";
								MainStack.push("copytxt");
							default:
								break;
							}
							break;
						}
						if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::LIT)
						{
							buffstr += "\tpush " + GetName(lextable.table[i].idxTI, isID) + '\n';
							MainStack.push(GetName(lextable.table[i].idxTI, isID));
						}
						if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::TXT)
						{
							if (isMain || isID == false) {
								if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::L) {
									buffstr += "\tpush offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
									MainStack.push("offset " + GetName(lextable.table[i].idxTI, isID));
								}
							}
							else {
								if (idtable.table[lextable.table[i].idxTI].idtype != IT::V)
								{
									buffstr += "\tpush " + GetName(lextable.table[i].idxTI, isID) + '\n';
									MainStack.push(GetName(lextable.table[i].idxTI, isID));
								}
								else {
									buffstr += "\tpush offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
									MainStack.push("offset " + GetName(lextable.table[i].idxTI, isID));
								}
							}
						}
						break;
					}
					case POLISHFUNCTION:
					{
						int j = i + 1;
						std::string x = ""; x += lextable.table[i + 1].lexema;
						std::stack<std::string> temp;
						std::string buf;
						std::string mainstacktop;
						int numbOfParameters = atoi(x.c_str());
						for (j = 0; j < numbOfParameters; j++)
						{
							buffstr += "\tpop edx\n";
						}
						for (j = 0; j < numbOfParameters; j++)
						{
							mainstacktop = MainStack.top();
							if (mainstacktop.size() > 8) {
								if (mainstacktop[7] == 'T'&&mainstacktop.size() < 12) {
									buffstr += "\tpush " + mainstacktop + "\n\tpush " + mainstacktop + 'T' +
										"\n\tcall copytxt\n\tpush " + mainstacktop + 'T' + '\n';
									MainStack.pop();
								}
								else {
									buffstr += "\tpush " + mainstacktop + '\n';
									MainStack.pop();
								}
							}
							else {
								buffstr += "\tpush " + mainstacktop + '\n';
								MainStack.pop();
							}
						}
						switch (lextable.table[i].idxTI)
						{
						case -2:
							buffstr += "\tcall textlenght\n\tpush eax\n";
							break;
						case -3:
							buffstr += "\tcall copytxt\n\tpush eax\n";
							break;
						default:
							buffstr += "\tcall proc_" + GetName(lextable.table[i].idxTI, false) + "\n\tpush eax\n";
							break;
						}
						i++;
						break;
					}
					case LEX_OPERATOR:
					{
						switch (lextable.table[i].value)
						{
						case '*':
						{
							buffstr += "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							break;
						}
						case '+':
						{
							if (idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::LIT)
							{
								buffstr += "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else
							{
								buffstr += "\tpop eax\n\tpop ebx\n";
								buffstr += "\tpush offset buf\n\tpush ebx\n\tpush eax\n";
								buffstr += "\tcall txtcon\n\tpush eax\n";
							}
							break;
						}
						case '-':
						{
							buffstr += "\tpop ebx\n\tpop eax\n\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						case '/':
							buffstr += "\tpop ebx\n\tpop eax\n\tcmp ebx,0\n\tje divbyzero\n\tmov edx,0\n\tidiv ebx\n\tpush eax\n";
							break;
						case '%':
							buffstr += "\tpop ebx\n\tpop eax\n\tcmp ebx,0\n\tje divbyzero\n\tmov edx,0\n\tidiv ebx\n\tpush edx\n";
							break;
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
					if (isMain)
						buffstr += "\tpush offset " + object + '\n';
					else
						buffstr += "\tpush " + object + '\n';
					buffstr += "\tcall copytxt\n";
				}
				break;
			case LEX_RETURN:
			{
				switch (lextable.table[++i].lexema)
				{
				case LEX_ID:
					isID = true;
				case LEX_LITERAL:
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::LIT)
						buffstr += "\tmov eax," + GetName(lextable.table[i].idxTI, isID) + '\n';
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::TXT)
						if (isMain)
							buffstr += "\tmov eax, offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
						else
							if (idtable.table[lextable.table[i].idxTI].idtype == IT::V)
								buffstr += "\tmov eax, offset " + GetName(lextable.table[i].idxTI, isID) + '\n';
							else
								buffstr += "\tmov eax, " + GetName(lextable.table[i].idxTI, isID) + '\n';
					if (!isMain) {
						buffstr += "jmp toend\ndivbyzero:\n\tpush offset mesdivbyzero\n\tcall outtxt\n\tcall sleep\n\tcall ExitProcess\ntoend:\n";
						buffstr += "\tret\n";
					}
					else
						buffstr += "\tpush 0\n";
				}
				break;
			}
			case LEX_OUTPUT:
			{
				std::string returned;
				if (idtable.table[lextable.table[i + 2].idxTI].iddatatype == IT::LIT) {
					if ((idtable.table[lextable.table[i + 2].idxTI].idtype == IT::V) || (idtable.table[lextable.table[i + 2].idxTI].idtype == IT::P))
						isID = true;
					returned = GetName(lextable.table[i + 2].idxTI, isID);
					buffstr += "\tpush " + returned + "\n\tcall outlit\n";
				}
				else {
					if ((idtable.table[lextable.table[i + 2].idxTI].idtype == IT::V) || (idtable.table[lextable.table[i + 2].idxTI].idtype == IT::P))
						isID = true;
					returned = GetName(lextable.table[i + 2].idxTI, isID);
					if (!isMain || isID == false)
						if (idtable.table[lextable.table[i + 2].idxTI].idtype != IT::P)
							buffstr += "\tpush offset " + returned + "\n\tcall outtxt\n";
						else
							buffstr += "\tpush " + returned + "\n\tcall outtxt\n";
					else
						buffstr += "\tpush offset " + returned + "\n\tcall outtxt\n";
				}
				break;
			}
			default:
				if (counter < 1)
					counter--;
				break;
			}
			case LEX_ID:
				isID = true;
			case LEX_LITERAL:
			{
				if (IsCycleForIDAndLITERALS|| IsCheckForIDAndLITERALS)
					if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::LIT)
						buffstr += "\tpush " + GetName(lextable.table[i].idxTI, isID) + '\n';
				break;
			}
			}
		}
		if (!isMain) {
			buffstr += "proc_" + name + " endp";
		}
		else {
			buffstr += "jmp toend\ndivbyzero:\n\tpush offset mesdivbyzero\n\tcall outtxt\ntoend:\n";
			buffstr += "\tcall sleep\n\tcall ExitProcess\nmain endp\nend main\n\n";
		}
		Code.Code += buffstr;
	}
}