#include "pch.h"
#include "FST.h"
#include <iostream>

int check (char* str) {
	FST::FST fst(
		str,
		7,
		//0
		FST::NODE(8, FST::RELATION('W', 0), FST::RELATION('_', 0), FST::RELATION('r', 0), FST::RELATION('s', 0), FST::RELATION('d', 0), FST::RELATION('w', 0), FST::RELATION('W', 1),FST::RELATION('5',4)),
		//1
		FST::NODE(4, FST::RELATION('_', 2), FST::RELATION('r', 3), FST::RELATION('s', 3), FST::RELATION('_', 4)),
		//2
		FST::NODE(3, FST::RELATION('_', 2), FST::RELATION('r', 3), FST::RELATION('s', 3)),
		//3
		FST::NODE(4, FST::RELATION('r', 3), FST::RELATION('s', 3), FST::RELATION('_', 4), FST::RELATION('\0', 4)),
		//4
		FST::NODE(3, FST::RELATION('_', 4), FST::RELATION('d', 5), FST::RELATION('\0', 4)),
		//5
		FST::NODE(1, FST::RELATION('w', 6)),
		//6
		FST::NODE(1, FST::RELATION('_', 6)),
		FST::NODE()
	);
	if (FST::execute(fst))
		//std::cout << "Цепочка " << fst.string << " распознана" << std::endl;
		return 1;
	else
		return 0;
	//else std::cout << "Цепочка " << fst.string << " не распознана " << std::endl;
}




int main()
{
	std::string str1=
	setlocale(LC_ALL, "Rus");
	if (check((char *)"W_rr___dw_") == 1)std::cout << "Цепочка " << " распознана" << std::endl;
	else std::cout << "Цепочка " << " не распознана " << std::endl;
	if (check((char *)"W_sr__dw__") == 1)std::cout << "Цепочка " << " распознана" << std::endl;
	else std::cout << "Цепочка " << " не распознана " << std::endl;
	if (check((char *)"W_rr__Y_dw_") == 1)std::cout << "Цепочка " << " распознана" << std::endl;
	else std::cout << "Цепочка " << " не распознана " << std::endl;
	if (check((char *)"5") == 1)std::cout << "Цепочка " << " распознана" << std::endl;
	else std::cout << check((char *)"5") << std::endl;
	system("pause");
	return 0;
}
