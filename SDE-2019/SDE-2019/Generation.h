#pragma once
#define BEFORE_DATA ".586\n.model flat, stdcall\nincludelib SDElib.lib\nincludelib kernel32.lib\n"
#define TEXTMAXSIZE 255
#define ASM_FILE_PATH "../ASM/ASM.asm"

namespace Generation
{
	struct OneSegment {
		std::string Name;
		std::string Code;
	};
	std::string WriteSegment(OneSegment segment);


	enum exprvalue {
		o = 0,
		i,
	};

	void Generate(LexA::Tables);

	struct ForExpression {
		short index;
		std::string name=" ";
		exprvalue cvalue;
	};


	struct Expressions {
		ForExpression *Elements = new ForExpression[32];
		int size;
	};

	void GenerateBody(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i);
	ForExpression doTreade(Expressions expr, int k);
	void GenerateExpression(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable);
	void GenerateOutput(LT::Entry* LEntries, int counterLEntries, IT::IdTable idtable);
	void GenerateHat(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i);
	void GenerateFunction(IT::IdTable idtable, LT::LexTable lextable, IT::Entry helpIEntry, int i);

	//enum INSTRUCTIONTYPE
	//{                   // Типы инструкций
	//	PUSH = 0,		// помещение переменной в стек
	//	FUNC = 2,		// инициализация функции tfi
	//	RET = 3,		// возврат значения функции: return l/i/expression;
	//	PRNT = 4,		// вывод : print  l/i/expression;
	//	ADD = 5,		// +
	//	ADDSTR = 6,
	//	DIFF = 7,		// - бинарный
	//	UDIFF = 8,		// - унарный ( лексема - '!')
	//	DIV = 9,		// /
	//	MUL = 10,		// *
	//	SEM = 11,		// ;
	//	PARM = 12,		// параметр : (ti,...)
	//	CALL = 13,		// вызов функции : i(...)
	//	ENDP = 14,		// конец процедуры : fucn_name ENDP
	//};
}