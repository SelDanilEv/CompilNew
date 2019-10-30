#pragma once
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов
#define LEX_INTEGER		't'	// лексема для integer
#define LEX_STRING		't'	// лексема для string
#define LEX_SHORT		't'	// лексема для short
#define LEX_ID			'i'	// лексема для идентификатора
#define LEX_LITERAL		'l'	// лексема для литерала
#define LEX_FUNCTION	'f'	// лексема для function
#define LEX_DECLARE		'd'	// лексема для declare
#define LEX_RETURN		'r'	// лексема для return
#define LEX_PRINT		'p'	// лексема для print
#define LEX_MAIN		'm'	// лексема для main
#define LEX_SEMICOLON	';'	// лексема для ;
#define LEX_COMMA		','	// лексема для ,
#define LEX_LEFTBRACE	'{'	// лексема для {
#define LEX_RIGHTBRACE	'}'	// лексема для }
#define LEX_LEFTTHESIS	'('	// лексема для (
#define LEX_RIGHTTHESIS	')'	// лексема для )
#define LEX_PLUS		'v'	// лексема для +
#define LEX_MINUS		'v'	// лексема для -
#define LEX_STAR		'v'	// лексема для *
#define LEX_DIRSLASH	'v'	// лексема для /
#define LEX_OPERATOR	'v'	// лексема для операторов
#define LEX_EQUAL		'=' // лексема для =
#define NEWLINE			'\n'// новая строка
#define LATTICE 		'#'// #
#define SPACE	 		' '// space

namespace LT		// таблица лексем
{
	struct Entry	// строка таблицы лексем
	{
		unsigned char lexema;	// лексема
		char value;
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
		int index;						// индекс для польской записи
		bool used = false;				// для польской записи
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(		// создать таблицу лексем
		int size			// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(				// добавить строку в таблицу лексем
		LexTable& lextable,	// экземпляр таблицы лексем
		Entry entry			// строка таблицы лексем
	);

	Entry GetEntry(			// получить строку таблицы лексем
		LexTable& lextable,	// экземпляр таблицы лексем
		int n				// номер получаемой строки
	);

	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить память)

	void showTable(LexTable lextable,std::ofstream &file);	// вывод таблицы лексем
	void showTable_mini(LexTable lextable,std::ofstream &file);	// вывод таблицы лексем легкий вид
};