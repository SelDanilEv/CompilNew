#include "pch.h"
#include <cstring>
namespace Error
{
	// серии ошибок:  0 -  99 - системные ошибки
	//				100 - 109 - ошибки параметров
	//				110 - 129 - ошибки лексического анализа
	//				130 - 149 - ошибки синтаксического анализа
	//				150 - 179 - ошибки семантического анализа
	//				170 - 200 - ошибки другие

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "SYSTEM: Недопустимый код ошибки"),		// код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "SYSTEM: Системный сбой"),
		ERROR_ENTRY(2, "SYSTEM: Деление на ноль"),
		ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "PARAMETERS: Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "PARAMETERS: Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(102, "PARAMETERS: Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(103, "PARAMETERS: Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(104, "PARAMETERS: Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"LEXICAL: Превышен максимльный размер таблицы лексем"),
		ERROR_ENTRY(111,"LEXICAL: Таблица лексем переполнена"),
		ERROR_ENTRY(112,"LEXICAL: Не найден конец строкового литерала или строковый литерал является пустым"),
		ERROR_ENTRY(113,"LEXICAL: Неправильно объявление числового литерала"),
		ERROR_ENTRY(114,"LEXICAL: Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(115,"LEXICAL: Таблица идентификаторов переполнена"),
		ERROR_ENTRY(116,"LEXICAL: Ошибка лексического анализа"),
		ERROR_ENTRY(117,"LEXICAL: Имя идентификатора задано неверно"),
		ERROR_ENTRY(118,"LEXICAL: Превышен максимальный размер строкового литерала"),
		ERROR_ENTRY(119,"LEXICAL: Превышено максимальное количество вложенных блоков"),
		ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY(130,"SYNTAX: Неверная структура программы"),
		ERROR_ENTRY(131,"SYNTAX: Ошибка в выражении"),
		ERROR_ENTRY(132,"SYNTAX: Ошибочный оператор"),
		ERROR_ENTRY(133,"SYNTAX: Ошибка в параметрах функции"),
		ERROR_ENTRY(134,"SYNTAX: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(135,"SYNTAX: Ошибочный оператор"),
		ERROR_ENTRY(136,"SYNTAX: Ошибка в синтаксическом анализе.За подробной информацией обратитесь к файлу trace"),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY(150,"SEMANTICS: Функция start должна быть определена только 1 раз"),
		ERROR_ENTRY(151,"SEMANTICS: Определение функции start не обнаруженo"),
		ERROR_ENTRY(152,"SEMANTICS: Повторное объявление переменной в данной области видимости"),
		ERROR_ENTRY(153,"SEMANTICS: Используется не объявленная переменная"),
		ERROR_ENTRY(154,"SEMANTICS: Неверное объявление переменной"),
		ERROR_ENTRY(155,"SEMANTICS: Неверные типы параметров"),
		ERROR_ENTRY(156,"SEMANTICS: Неверное количество параметров"),
		ERROR_ENTRY(157,"SEMANTICS: Несоответсвие типов"),
		ERROR_ENTRY(158,"SEMANTICS: Превышено максимальное колличество передаваемых параметров при определении функции"),
		ERROR_ENTRY(159,"SEMANTICS: Превышено максимальное колличество передаваемых параметров при вызове функции"),
		ERROR_ENTRY(160,"SEMANTICS: Функция не возращает значение"),
		ERROR_ENTRY(161,"SEMANTICS: Тип возращаемого значения не соответсвует типу функции"),
		ERROR_ENTRY(162,"SEMANTICS: Превышено максимальное количество опердов для выражения"),
		ERROR_ENTRY(163,"SEMANTICS: Параметры цикла могут быть только типа little"),
		ERROR_ENTRY(164,"SEMANTICS: К операндам типа text применим только оператор + "),
		ERROR_ENTRY(165,"SEMANTICS: Вложенные циклы не поддерживаются"),
		ERROR_ENTRY(166,"SEMANTICS: Параметры условного оператора должны быть типа little"),
		ERROR_ENTRY_NODEF(167),
		ERROR_ENTRY_NODEF(168),
		ERROR_ENTRY_NODEF(169),
		ERROR_ENTRY_NODEF(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF(190),
		ERROR_ENTRY_NODEF(191),
		ERROR_ENTRY_NODEF(192),
		ERROR_ENTRY_NODEF(193),
		ERROR_ENTRY_NODEF(194),
		ERROR_ENTRY_NODEF(195),
		ERROR_ENTRY_NODEF(196),
		ERROR_ENTRY_NODEF(197),
		ERROR_ENTRY_NODEF(198),
		ERROR_ENTRY_NODEF(199,"ADDITIONAL: Ошибка в построении польской записи")
	};

	ERROR geterror(int id)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		er.id = id;
		er.inext.col = er.inext.line = 0;
		strcpy_s(er.message, errors[id].message);
		return er;
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR er;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		er.id = id;
		er.inext.line = line + 1;
		er.inext.col = col;
		strcpy_s(er.message, errors[id].message);
		return er;
	}
};