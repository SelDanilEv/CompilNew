#include "CodeGeneration.h"
#include <stack>

namespace CodeGeneration
{
	void CodeGeneration(LexA::Tables lex)
	{
		std::string outstr="";
		outstr += ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\t	includelib ../Debug/Standard_Library.lib\n\tExitProcess PROTO :DWORD\n\n";
		outstr += "\toutc PROTO: DWORD\n\toutd PROTO: DWORD\n\tstrl PROTO: DWORD\n\tpower PROTO: DWORD, :DWORD\n";
		outstr += "\n.stack 4096\n";

		outstr += ".const\n";
		for (int i = 0; i < lex.myidtable.size; i++)
		{
			if (lex.myidtable.table[i].idtype == IT::L)
			{
				outstr += "\t" +std::to_string(*lex.myidtable.table[i].id);
				if (lex.myidtable.table[i].iddatatype == IT::TXT)
				{
					outstr += " BYTE " +std::to_string(*lex.myidtable.table[i].value.vstr.str) + ", 0\n";
				}
				if (lex.myidtable.table[i].iddatatype == IT::LIT)
				{
					outstr += " DWORD " + lex.myidtable.table[i].value.vint + '\n';
				}
			}
		}

		outstr += ".data\n";
		for (int i = 0; i < lex.mylextable.size; i++)
		{
			if (lex.mylextable.table[i].lexema == LEX_NEW)
			{
				while (lex.myidtable.table[lex.mylextable.table[i + 1].idxTI].idtype == IT::V)
				{
					outstr += "\t" +std::to_string(*lex.myidtable.table[lex.mylextable.table[i + 1].idxTI].id);
					if (lex.myidtable.table[lex.mylextable.table[i + 1].idxTI].iddatatype == IT::TXT)
					{
						outstr += " DWORD ?\n";
					}
					if (lex.myidtable.table[lex.mylextable.table[i + 1].idxTI].iddatatype == IT::LIT)
					{
						outstr += " SDWORD ?\n";
					}
					i += 2;
				}
			}
		}

		std::stack<std::string> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0;
		std::string strret = "",
			func_name = "";					// имя локальной функции
		bool flag_func = false,					// внутри локальной функции?
			flag_ret = false,					// был ret?
			flag_body = false,					// внутри главной функции?
			flag_if = false,					// внутри if?
			flag_then = false,					// внутри then?
			flag_else = false;					// внутри then/else?
		outstr += "\n.code\n\n";
		for (int i = 0; i < lex.mylextable.size; i++)
		{
			switch (lex.mylextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				outstr += (func_name = std::to_string(*lex.myidtable.table[lex.mylextable.table[++i].idxTI].id)) + " PROC ";
				while (lex.mylextable.table[i].lexema != LEX_RIGHTTHESIS)
				{
					if (lex.myidtable.table[lex.mylextable.table[i].idxTI].idtype == IT::P)
					{
						outstr += std::to_string(*lex.myidtable.table[lex.mylextable.table[i].idxTI].id) + " : ";
						if (lex.myidtable.table[lex.mylextable.table[i++].idxTI].iddatatype == IT::LIT)
						{
							outstr += "SDWORD";
						}
						else
						{
							outstr += "DWORD";
						}
					}
					if (lex.mylextable.table[i].lexema == LEX_COMMA)
					{
						outstr += ", ";
					}
					i++;
				}
				flag_func = true;
				outstr += '\n';
				break;
			}
			case LEX_START:
			{
				flag_body = true;
				outstr += "main PROC\n";
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.mylextable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (lex.mylextable.table[i].lexema)
					{
					case LEX_ID:
					case LEX_LITERAL:
					{
						outstr += "\tpush " +std::to_string(*lex.myidtable.table[lex.mylextable.table[i].idxTI].id) + '\n';
						stk.push(std::to_string(*lex.myidtable.table[lex.mylextable.table[i].idxTI].id));
						break;
					}
					case lex:
					{
						outstr += "\tpush offset " + lex.myidtable.table[lex.mylextable.table[i].idxTI].id + '\n';
						stk.push("offset " + lex.myidtable.table[lex.mylextable.table[i].idxTI].id);
						break;
					}
					case LEX_SUBST:
					{
						for (int j = 1; j <= lex.mylextable.table[i].priority; j++)
						{
							outstr += "\tpop edx\n";
						}
						for (int j = 1; j <= lex.mylextable.table[i].priority; j++)
						{
							outstr += "\tpush " + stk.top() + '\n';
							stk.pop();
						}
						outstr += "\t\tcall " + lex.myidtable.table[lex.mylextable.table[i].idxTI].id + "\n\tpush eax\n";
						break;
					}
					case LEX_OPERATOR:
					{
						switch (lex.myidtable.table[lex.mylextable.table[i].idxTI].id[0])
						{
						case '*':
						{
							outstr += "\tpop eax\n\tpop ebx\n";
							outstr += "\tmul ebx\n\tpush eax\n";
							break;
						}
						case '+':
						{
							outstr += "\tpop eax\n\tpop ebx\n";
							outstr += "\tadd eax, ebx\n\tpush eax\n";
							break;
						}
						case '-':
						{
							outstr += "\tpop ebx\n\tpop eax\n";
							outstr += "\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						}
						break;
					}
					}
					i++;
				}
				outstr += "\tpop " +std::to_string(*lex.myidtable.table[lex.mylextable.table[result_position].idxTI].id) + "\n";
				break;
			}
			case LEX_RETURN:
			{
				outstr += "\tpush ";
				i++;
				if (lex.myidtable.table[lex.mylextable.table[i].idxTI].idtype == IT::L)
				{
					outstr += lex.myidtable.table[lex.mylextable.table[i++].idxTI].value.vint + '\n';
				}
				else
				{
					outstr += std::to_string(*lex.myidtable.table[lex.mylextable.table[i++].idxTI].id) + '\n';
				}
				if (flag_func)
				{
					outstr += "\t\tjmp local" + num_of_ret + '\n';
					flag_ret = true;
				}
				if (flag_body)
				{
					outstr += "\t\tjmp theend\n";
					flag_ret = true;
				}
				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (flag_body && !flag_then && !flag_else && !flag_func)
				{
					if (flag_ret)
					{
						outstr += "theend:\n";
						flag_ret = false;
					}
					outstr += "\tcall ExitProcess\nmain ENDP\nend main";
				}
				if (flag_func)
				{
					if (flag_ret)
					{
						outstr += "local" + std::to_string(num_of_ret++) + ":\n";
						outstr += "\tpop eax\n\tret\n";
						flag_ret = false;
					}
					outstr += func_name + " ENDP\n\n";
					flag_func = false;
				}
				if (flag_then)
				{
					flag_then = false;
					if (flag_else)
					{
						outstr += "\tjmp e" + num_of_ends + '\n';
						flag_else = false;
					}
					outstr += "m" + std::to_string(num_of_points++) + ":\n";
				}
				if (flag_else)
				{
					flag_else = false;
					outstr += "e" + std::to_string(num_of_ends++) + ":\n";
				}
				break;
			}
			case LEX_LEFTTHESIS:
			{
				if (flag_if)
				{//if
					outstr += "\tmov eax, " +std::to_string(*lex.myidtable.table[lex.mylextable.table[i + 1].idxTI].id) + '\n';
					outstr += "\tcmp eax, " + std::to_string(*lex.myidtable.table[lex.mylextable.table[i + 3].idxTI].id) + '\n';
					
					outstr += "\t\tje m" + num_of_points + 1 + '\n';
					
					flag_if = false;
				}
				break;
			}
			}
		}
	}
}