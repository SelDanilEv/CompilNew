#include "pch.h"
#include <cstring>
namespace Error
{
	// серии ошибок:  0 -  99 - системные ошибки
	//				100 - 109 - ошибки параметров
	//				110 - 129 - ошибки лексического анализа
	//				130 - 149 - ошибки синтаксического анализа
	//				150 - 169 - ошибки семантического анализа
	//				170 - 200 - ошибки другие

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),		// код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY(2, "Деление на ноль"),
		ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY(101,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(102,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(103,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Превышен максимльный размер таблицы лексем"),
		ERROR_ENTRY(111,"Таблица лексем переполнена"),
		ERROR_ENTRY(112,"Не найден конец строкового литерала"),
		ERROR_ENTRY(113,"Неправильно объявление числового литерала"),
		ERROR_ENTRY(114,"Превышен максимльный размер таблицы идентификаторов"),
		ERROR_ENTRY(115,"Таблица идентификаторов переполнена"),
		ERROR_ENTRY(116,"Ошибка лексического анализа"),
		ERROR_ENTRY(117,"Имя идентификатора задано неверно"),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY(130,"Неверная структура программы"),
		ERROR_ENTRY(131,"Ошибка в выражении"),
		ERROR_ENTRY(132,"Ошибочный оператор"),
		ERROR_ENTRY(133,"Ошибка в параметрах функции"),
		ERROR_ENTRY(134,"Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(135,"Ошибочный оператор"),
		ERROR_ENTRY(136,"Ошибка в синтаксическом анализе.За подробной информацией обратитесь к файлу trace"),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY(150,"Функция start должна быть определена только 1 раз"),
		ERROR_ENTRY(151,"Определение функции start не обнаружена"),
		ERROR_ENTRY(152,"Повторное объявление переменной в данной области видимости"),
		ERROR_ENTRY(153,"Используется не объявленная переменная"),
		ERROR_ENTRY(154,"Неверное объявление переменной"),
		ERROR_ENTRY(155,"Неверные типы параметров"),
		ERROR_ENTRY(156,"Неверное количество параметров"),
		ERROR_ENTRY(157,"Несоответсвие типов"),
		ERROR_ENTRY(158,"Превышено максимальное колличество передаваемых параметров при определении функции"),
		ERROR_ENTRY(159,"Превышено максимальное колличество передаваемых параметров при вызове функции"),
		ERROR_ENTRY(160,"Функция не возращает значение"),
		ERROR_ENTRY(161,"Тип возращаемого значения не соответсвует типу функции"),
		ERROR_ENTRY(162,"Превышено максимальное количество опердов для выражения"),
		ERROR_ENTRY(163,"Параметры цикла могут быть только типа little"),
		ERROR_ENTRY(164,"К операндам типа text применим только оператор + "),
		ERROR_ENTRY(165,"Вложенные циклы не поддерживаются"),
		ERROR_ENTRY(166,"Параметры условного оператора должны быть типа little"),
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
		ERROR_ENTRY_NODEF(199,"Ошибка в построении польской записи")
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