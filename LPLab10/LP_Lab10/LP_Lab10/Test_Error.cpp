#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "Error.h"		//обработка ошибок
#include "Parm.h"		//обработка параметров
#include "Log.h"		//работа с протоколом
#include "In.h"			//ввод исходного файла

//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "rus");
//	std::cout << " ----------тест Error::geterror    ---" << std::endl << std::endl;
//	try { throw ERROR_THROW(100); }
//	catch (Error::ERROR e)
//	{
//		std::cout << "Ошибка " << e.id << ":" << e.message << std::endl << std::endl;
//	};
//
//	try { throw ERROR_THROW_IN(111, 7, 7); }
//	catch (Error::ERROR e)
//	{
//		std::cout << "Ошибка " << e.id << ":" << e.message
//			<< ", строка " << e.inext.line
//			<< ",позиция " << e.inext.col << std::endl << std::endl;
//	};
//
//	system("pause");
//	return 0;
//}


