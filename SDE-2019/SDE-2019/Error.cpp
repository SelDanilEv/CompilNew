#include "pch.h"
#include <cstring>
namespace Error
{
	// ����� ������:  0 -  99 - ��������� ������
	//				100 - 109 - ������ ����������
	//				110 - 129 - ������ ������������ �������
	//				130 - 149 - ������ ��������������� �������
	//				150 - 179 - ������ �������������� �������
	//				170 - 200 - ������ ������

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "SYSTEM: ������������ ��� ������"),		// ��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "SYSTEM: ��������� ����"),
		ERROR_ENTRY(2, "SYSTEM: ������� �� ����"),
		ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "PARAMETERS: �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "PARAMETERS: ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(102, "PARAMETERS: ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(103, "PARAMETERS: ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(104, "PARAMETERS: ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),
		ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"LEXICAL: �������� ����������� ������ ������� ������"),
		ERROR_ENTRY(111,"LEXICAL: ������� ������ �����������"),
		ERROR_ENTRY(112,"LEXICAL: �� ������ ����� ���������� �������� ��� ��������� ������� �������� ������"),
		ERROR_ENTRY(113,"LEXICAL: ����������� ���������� ��������� ��������"),
		ERROR_ENTRY(114,"LEXICAL: �������� ������������ ������ ������� ���������������"),
		ERROR_ENTRY(115,"LEXICAL: ������� ��������������� �����������"),
		ERROR_ENTRY(116,"LEXICAL: ������ ������������ �������"),
		ERROR_ENTRY(117,"LEXICAL: ��� �������������� ������ �������"),
		ERROR_ENTRY(118,"LEXICAL: �������� ������������ ������ ���������� ��������"),
		ERROR_ENTRY(119,"LEXICAL: ��������� ������������ ���������� ��������� ������"),
		ERROR_ENTRY_NODEF10(120),
		ERROR_ENTRY(130,"SYNTAX: �������� ��������� ���������"),
		ERROR_ENTRY(131,"SYNTAX: ������ � ���������"),
		ERROR_ENTRY(132,"SYNTAX: ��������� ��������"),
		ERROR_ENTRY(133,"SYNTAX: ������ � ���������� �������"),
		ERROR_ENTRY(134,"SYNTAX: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(135,"SYNTAX: ��������� ��������"),
		ERROR_ENTRY(136,"SYNTAX: ������ � �������������� �������.�� ��������� ����������� ���������� � ����� trace"),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY(150,"SEMANTICS: ������� start ������ ���� ���������� ������ 1 ���"),
		ERROR_ENTRY(151,"SEMANTICS: ����������� ������� start �� ���������o"),
		ERROR_ENTRY(152,"SEMANTICS: ��������� ���������� ���������� � ������ ������� ���������"),
		ERROR_ENTRY(153,"SEMANTICS: ������������ �� ����������� ����������"),
		ERROR_ENTRY(154,"SEMANTICS: �������� ���������� ����������"),
		ERROR_ENTRY(155,"SEMANTICS: �������� ���� ����������"),
		ERROR_ENTRY(156,"SEMANTICS: �������� ���������� ����������"),
		ERROR_ENTRY(157,"SEMANTICS: ������������� �����"),
		ERROR_ENTRY(158,"SEMANTICS: ��������� ������������ ����������� ������������ ���������� ��� ����������� �������"),
		ERROR_ENTRY(159,"SEMANTICS: ��������� ������������ ����������� ������������ ���������� ��� ������ �������"),
		ERROR_ENTRY(160,"SEMANTICS: ������� �� ��������� ��������"),
		ERROR_ENTRY(161,"SEMANTICS: ��� ������������ �������� �� ������������ ���� �������"),
		ERROR_ENTRY(162,"SEMANTICS: ��������� ������������ ���������� ������� ��� ���������"),
		ERROR_ENTRY(163,"SEMANTICS: ��������� ����� ����� ���� ������ ���� little"),
		ERROR_ENTRY(164,"SEMANTICS: � ��������� ���� text �������� ������ �������� + "),
		ERROR_ENTRY(165,"SEMANTICS: ��������� ����� �� ��������������"),
		ERROR_ENTRY(166,"SEMANTICS: ��������� ��������� ��������� ������ ���� ���� little"),
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
		ERROR_ENTRY_NODEF(199,"ADDITIONAL: ������ � ���������� �������� ������")
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