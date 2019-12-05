#include "pch.h"
#include "Generation.h"

namespace Generation
{
	std::string WriteSegment(OneSegment segment)
	{
		return ("\n." + segment.Name + '\n' + segment.Code);
	}

	void Generate(LexA::Tables tables)
	{
		LT::LexTable lextable = tables.mylextable;
		IT::IdTable idtable = tables.myidtable;
		std::string Proto;
		std::string fullCode="";

		LT::Entry helpLEntry;
		IT::Entry helpIEntry;
		std::string helpstr = "";
		int buffer = 0;

		OneSegment Stack = { "stack","4096" };
		OneSegment Const = { "const" };
		OneSegment Data = { "data" };
		OneSegment Code = { "code" };

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
					while (helpIEntry.id[buffer] != NULL&& helpIEntry.id[buffer] != '\0')
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
			else
			{

			}
		}

		for (int i = 0; i < lextable.size; i++)
		{
			switch (lextable.table[i].lexema)
			{
			case LEX_LITERAL:
			{

			}
			break;
			case LEX_ID:
			{
				if (helpIEntry.idtype == IT::F && helpIEntry.areaOfVisibility[1] == 0) //напишем прототип
				{
					/*helpstr = "function_";
					while (helpIEntry.id[buffer] != NULL)
					{
						helpstr += helpIEntry.id[buffer];
						buffer++;
					}
					helpstr += " proc, ";
					buffer = i + 1;
					while (lextable.table[buffer].lexema != LEX_RIGHTTHESIS)
					{
						if (buffer != i + 3)helpstr += ',';
						if (lextable.table[buffer].lexema == LEX_ID)
						{
							helpstr += "parameter_";
							int m = 0;
							while (helpIEntry.id[m] != NULL)
							{
								helpstr += helpIEntry.id[m++];
							}
							helpstr += " : ";
							if (idtable.table[lextable.table[buffer].idxTI].iddatatype == IT::LIT)
								helpstr += "dword";
							else
								helpstr += "byte";
						}
					}*/
					//генерация
				}
				else
				{

				}

			}
			break;
			default:
				break;
			}
		}

		fullCode += BEFORE_DATA + Proto + WriteSegment(Stack) + WriteSegment(Const) +
			WriteSegment(Data) + WriteSegment(Code);
		std::ofstream fileASM;
		fileASM.open(ASM_FILE_PATH);
		fileASM << fullCode;
		fileASM.close();
	}
};