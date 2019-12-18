#pragma once
#include "Greibach.h"
#define GRB_ERROR_SERIES 130
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		8,									  // количество правил
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
			8,                                // 
			Rule::Chain(5, TS('s'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(6, TS('s'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('S')),
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,    // ошибочный оператор
			18,
			Rule::Chain(4, TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(3, TS('{'), NS('N'), TS('}')),
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('U'), TS(';')),
			Rule::Chain(4, TS('r'), NS('U'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(11, TS('c'), TS('('), NS('U'), NS('C'), NS('U'), TS(')'), TS('?'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(15, TS('c'), TS('('), NS('U'), NS('C'), NS('U'), TS(')'), TS('?'), TS('{'), NS('N'), TS('}'), TS('j'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(14, TS('c'), TS('('), NS('U'), NS('C'), NS('U'), TS(')'), TS('?'), TS('{'), NS('N'), TS('}'), TS('j'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('c'), TS('('), NS('U'), NS('C'), NS('U'), TS(')'), TS('?'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(8, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(9, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('o'), TS('('), NS('U'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('o'), TS('('), NS('U'), TS(')'), TS(';')),
			Rule::Chain(12, TS('m'), TS('('), NS('U'), TS(')'), TS('e'), TS('('), NS('U'), TS(')'), TS('$'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(13, TS('m'), TS('('), NS('U'), TS(')'), TS('e'), TS('('), NS('U'), TS(')'), TS('$'), TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,    // ошибка в выражении
			10,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			2,                                // 
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,    // оператор
			2,								  //
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('U'), GRB_ERROR_SERIES + 6,    // 
			2,								  //
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),
		Rule(
			NS('C'), GRB_ERROR_SERIES + 7,    // 
			2,								  //
			Rule::Chain(1, TS('v')),
			Rule::Chain(1, TS('y'))
		)
	);
}