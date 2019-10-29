#pragma once
#define ID_MAXSIZE		32			// максимальное количество символов в идентификаторе
#define TI_MAXSIZE		4096		// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0x00000000	// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT	0x00		// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffffffff	// нет элкмента таблицы идентификаторов
#define TI_STR_MAXSIZE	255			// 

namespace IT			// таблица идентификаторов
{
	enum IDDATATYPE { INT = 1, STR = 2 ,SHR =3 ,Err=0};			// типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, E = 0 };	// типы идентификаторов: переменна€, функци€, параметр, литерал,арифм операци€

	struct Entry	// строка таблицы идентификаторов
	{
		short areaOfVisibility[5] = { 0 };
		int	idxfirstLE;			// индекс первой строки в таблице лексем
		unsigned char id[ID_MAXSIZE];		// индентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE	iddatatype;			// тип данных
		IDTYPE		idtype;				// тип идентификатора
		union
		{
			int vint;					// значение integer
			short vshr;					// значение integer
			struct
			{
				int len;						// количество символов в string
				unsigned char str[TI_STR_MAXSIZE - 1];	// символы string
			} vstr;				// значение string
		} value;		// значение идентификатора
	};

	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxsize;			// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxsize
		Entry* table;			// массив строк таблицы идентификаторов
	};

	IdTable Create(				// создать таблицу идентификаторов
		int size				// емкость таблицы идентификаторов < TI_MAXSIZE
	);

	void Add(				// добавить строку в таблицу идентификаторов
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		Entry entry			// строка таблицы идентификаторов
	);

	Entry GetEntry(			// получить строку таблицы идентификаторов
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		int n				// номер получаемой строки
	);

	int IsId(				// возврат: номер строки (если есть), TI_NULLIDX (если нет)
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		unsigned char id[ID_MAXSIZE]	// идентификатор
	);

	int IsIdWithAreaOfVisibility(				// возврат: номер строки (если есть), TI_NULLIDX (если нет) с с областью видимости
		IdTable& idtable,	// экземпл€р таблицы идентификаторов
		unsigned char id[ID_MAXSIZE],	// идентификатор
		short area[5]	// область видимости
	);

	void Delete(IdTable& idtable);	// удалить таблицу лексем (освободить пам€ть)
	void showTable(IdTable& idtable, std::ofstream &file);
};