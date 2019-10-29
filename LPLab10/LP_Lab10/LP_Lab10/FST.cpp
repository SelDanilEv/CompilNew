#include "stdafx.h"
#include "FST.h"
#include <cstring>
#include <iostream>
#include <algorithm>
namespace FST
{
	int check(char* str) {

	FST:FST fst(
		str,
		7,
		//0
		NODE(7, RELATION('W', 0), RELATION('_', 0), RELATION('r', 0), RELATION('s', 0), RELATION('d', 0), RELATION('w', 0), RELATION('W', 1)),
		//1
		NODE(4, RELATION('_', 2), RELATION('r', 3), RELATION('s', 3), RELATION('_', 4)),
		//2
		NODE(3, RELATION('_', 2), RELATION('r', 3), RELATION('s', 3)),
		//3
		NODE(3, RELATION('r', 3), RELATION('s', 3), RELATION('_', 4)),
		//4
		NODE(2, RELATION('_', 4), RELATION('d', 5)),
		//5
		NODE(2, RELATION('w', 6)),
		//6
		NODE(2, RELATION('_', 6)),
		NODE()
	);
		if (execute(fst)) {
			return 1;
		}
		//std::cout << "Цепочка " << fst.string << " распознана" << std::endl;
		else {
			return 0;
		}
		//std::cout << "Цепочка " << fst.string << " не распознана " << std::endl;
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
}




