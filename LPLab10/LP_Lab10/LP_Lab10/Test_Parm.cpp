#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "Error.h"		//обработка ошибок
#include "Parm.h"		//обработка параметров
#include "Log.h"		//работа с протоколом
#include "In.h"			//ввод исходного файла
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "rus");
//	std::cout << " ----------тест Parm::getparm    ---" << std::endl << std::endl;
//	try
//	{
//		Parm::PARM parm = Parm::getparm(argc, argv);
//		std::wcout << "-in:" << parm.in << ", -out: " << parm.out << ", -log: " << parm.log <<std::endl << std::endl;
//	}
//	catch (Error::ERROR e)
//	{
//		std::cout << "Ошибка " << e.id << ":" << e.message << std::endl << std::endl;
//	};
//
//	system("pause");
//	return 0;
//}
//
//
