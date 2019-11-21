#include "pch.h"
#include <iomanip>

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) throw ERROR_THROW(160);
		IdTable Table;
		Table.maxsize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size > idtable.maxsize) throw ERROR_THROW(161);
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, unsigned char id[ID_MAXSIZE])           //возращает номер в таблице
	{
		bool rc = false;
		for (int i = 0; i < idtable.size; i++)
		{
			if (_mbscmp(idtable.table[i].id, id) == 0)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	int IsIdWithAreaOfVisibility(IdTable& idtable, unsigned char id[ID_MAXSIZE], short area[5])           //возращает номер в таблице
	{
		bool rc;
		for (int i = 0; i < idtable.size; i++)
		{
			rc = true;
			if (_mbscmp(idtable.table[i].id, id) == 0)
			{
				if (idtable.table[i].areaOfVisibility[1] != 0) {
					for (int q = 0; q < 5; q++)
						if (idtable.table[i].areaOfVisibility[q] != area[q])
						{
							rc = false;
						}
				}
				if (rc)
					return i;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}

	void showTable(IdTable& idtable, std::ofstream& file)                     //функция вывода 
	{
		int iddatatype;
		int idtype;
		int counter = 0;

		file << std::setfill('=') << std::setw(25) << "ID TABLE" << std::setw(16) << "\n\n";              //вывод преамбулы
		file << std::setfill(' ') << std::setw(10) << "Name" << std::setw(15) << "Type" << std::setw(15) << "Data type" <<
			std::setw(19) << "First in LT" << std::setw(21) << "Value" << "\n\n";

		for (int i = 0; i < idtable.size; i++)                                 //вывод таблицы
		{
			iddatatype = idtable.table[i].iddatatype;
			idtype = idtable.table[i].idtype;
			file << std::setfill(' ') << std::setw(3) << i;
			file << std::setfill(' ') << std::setw(10) << idtable.table[i].id << std::setw(15);

			switch (idtype)
			{
			case 1:
				file << std::setfill(' ') << "variable" << std::setw(15);
				break;
			case 2:
				file << std::setfill(' ') << "function" << std::setw(15);
				break;
			case 3:
				file << std::setfill(' ') << "parameter" << std::setw(15);
				break;
			case 4:
				file << std::setfill(' ') << "literal" << std::setw(15);
				break;
			case 0:
				file << std::setfill(' ') << "error" << std::setw(15);
				break;

			}

			switch (iddatatype)
			{
			case 1:
				file << std::setfill(' ') << "little" << std::setw(15);
				break;
			case 2:
				file << std::setfill(' ') << "text" << std::setw(15);
				break;
			/*case 3:
				file << std::setfill(' ') << "short" << std::setw(15);
				break;*/
			case 0:
				file << std::setfill(' ') << "error" << std::setw(15);
				break;
			}

			file << std::setfill(' ') << idtable.table[i].idxfirstLE << std::setw(25);


			if (idtype != 4)
				switch (iddatatype)
				{
				case 1:
					file << '0';
					break;
				case 3:
					file << '0';
					break;
				case 2:
					file << "NV";
					break;
				default:
					break;
				}
			else {
				if (iddatatype == 1)
					file << idtable.table[i].value.vint;
				else
					file << idtable.table[i].value.vstr.str;
			}

			counter = 1;
			file << std::setfill(' ') << std::setw(15) << '0';
			while (idtable.table[i].areaOfVisibility[counter] != NULL)
			{
				file << " " << idtable.table[i].areaOfVisibility[counter];
				counter++;
			}

			file << std::endl;
		}
	}
}