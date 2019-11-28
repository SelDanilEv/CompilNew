#pragma once
namespace FST
{
	struct RELATION					//ребро:символ -> вершина графа переходов КА
	{
		char symbol;				//симпол перехода	
		short nnode;				//номер смежной вершины
		RELATION(
			char c = 0x00,			//символ перехода
			short ns = 0			//номер смежной вершины
		);
	};

	struct NODE						//вершина графа переходов
	{
		short n_relation;			//количество инцидентных ребер
		RELATION *relations;		//инцидентные ребра
		NODE();
		NODE
		(short n,				//количество инцидентных ребер
			RELATION rel, ...		//список ребер
		);
	};

	struct FST						//недетерминированный конечный автомат
	{
		char* string;				//цепочка (строка,завершается 0х00)
		short position;				//текущая позиция в цепочке
		short nstates;				//количество состояний автомата
		NODE* nodes;				//граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;				//возможные состояния автомата на данной позиции
		FST(
			char* s,				//цепочка (строка, завершаеся 0х00)
			short ns,				//количество состояний автомата
			NODE n, ...				//список состояний (граф переходов)
		);
	};

	int getPosition(FST& fst);
	bool execute(FST& fst);
	int little(char* str);
	int text(char* str);
	int function(char* str);
	int New(char* str);
	int Return(char* str);
	int output(char* str);
	int start(char* str);
	//int Short(char* str);
	bool literalInt(char* str);
}
