#include "pch.h"
#include "FST.h"
#include "LT.h"
#include <cstring>
#include <iostream>
#include <algorithm>

namespace FST
{
	int little(char* str) {
		FST fst(
			str,
			7,
			NODE(1, RELATION('l', 1)),
			NODE(1, RELATION('i', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('t', 4)),
			NODE(1, RELATION('l', 5)),
			NODE(1, RELATION('e', 6)),
			NODE()
		);
		if (execute(fst))return 0; else return -1;
	}

	int text(char* str) {
		FST fst(
			str,
			5,
			NODE(1, RELATION('t', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('x', 3)),
			NODE(1, RELATION('t', 4)),
			NODE()
		);
		if (execute(fst))return 1; else return -1;
	}

	int function(char* str) {
		FST fst(
			str,
			9,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('n', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('t', 5)),
			NODE(1, RELATION('i', 6)),
			NODE(1, RELATION('o', 7)),
			NODE(1, RELATION('n', 8)),
			NODE()
		);
		if (execute(fst))return 2; else return -1;
	}

	int start(char* str) {
		FST fst(
			str,
			6,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('a', 3)),
			NODE(1, RELATION('r', 4)),
			NODE(1, RELATION('t', 5)),
			NODE()
		);
		if (execute(fst))return 3; else return -1;
	}

	int New(char* str) {
		FST fst(
			str,
			4,
			NODE(1, RELATION('n', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('w', 3)),
			NODE()
		);
		if (execute(fst))return 4; else return -1;
	}

	int Return(char* str) {
		FST fst(
			str,
			7,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('n', 6)),
			NODE()
		);
		if (execute(fst))return 5; else return -1;
	}

	int output(char* str) {
		FST fst(
			str,
			7,
			NODE(1, RELATION('o', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('p', 4)),
			NODE(1, RELATION('u', 5)),
			NODE(1, RELATION('t', 6)),
			NODE()
		);
		if (execute(fst))return 6; else return -1;
	}

	int from(char* str) {
		FST fst(
			str,
			5,
			NODE(1, RELATION('f', 1)),
			NODE(1, RELATION('r', 2)),
			NODE(1, RELATION('o', 3)),
			NODE(1, RELATION('m', 4)),
			NODE()
		);
		if (execute(fst))return 17; else return -1;
	}

	int to(char* str) {
		FST fst(
			str,
			3,
			NODE(1, RELATION('t', 1)),
			NODE(1, RELATION('o', 2)),
			NODE()
		);
		if (execute(fst))return 18; else return -1;
	}

	int check(char* str) {
		FST fst(
			str,
			6,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('e', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('k', 5)),
			NODE()
		);
		if (execute(fst))return 20; else return -1;
	}

	int Not(char* str) {
		FST fst(
			str,
			4,
			NODE(1, RELATION('n', 1)),
			NODE(1, RELATION('o', 2)),
			NODE(1, RELATION('t', 3)),
			NODE()
		);
		if (execute(fst))return 22; else return -1;
	}

	int id(char* str) {
		FST fst(
			str,
			3,
			NODE(52,
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),
				RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),
				RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1),

				RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),
				RELATION('y', 2), RELATION('z', 2)),
			NODE(72,
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),
				RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),
				RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1),
				RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1),
				RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),

				RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),
				RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),
				RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),
				RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),
				RELATION('y', 2), RELATION('z', 2),
				RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2), RELATION('6', 2),
				RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2)),
			NODE()
		);
		if (execute(fst))return 7; else return -1;
	}



	bool literalInt(char* str)
	{
		FST fst(
			str,
			3,
			NODE(62,
				RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),
				RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0), RELATION('0', 0),
				RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
				RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),
				RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2),
				RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2),
				RELATION('!', 1), RELATION('-', 1)
			),
			NODE(20,
				RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
				RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),
				RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2),
				RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2)
			),
			NODE()
		);
		if (execute(fst))
			return true;
		else return false;
	}


	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE()
	{
		n_relation = 0;
		relations = nullptr;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++)
			relations[i] = p[i];
	};

	FST::FST(char* s, short ns, NODE n, ...)
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++)
			nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	};
	bool step(FST& fst, short* &rstates)
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
		};
		return rc;
	};
	bool execute(FST& fst)
	{
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short)*fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};
	int getPosition(FST& fst) {
		execute(fst);
		return fst.position;
	}
}