#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "Error.h"		//��������� ������
#include "Parm.h"		//��������� ����������
#include "Log.h"		//������ � ����������
#include "In.h"			//���� ��������� �����

//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "rus");
//	std::cout << " ----------���� Error::geterror    ---" << std::endl << std::endl;
//	try { throw ERROR_THROW(100); }
//	catch (Error::ERROR e)
//	{
//		std::cout << "������ " << e.id << ":" << e.message << std::endl << std::endl;
//	};
//
//	try { throw ERROR_THROW_IN(111, 7, 7); }
//	catch (Error::ERROR e)
//	{
//		std::cout << "������ " << e.id << ":" << e.message
//			<< ", ������ " << e.inext.line
//			<< ",������� " << e.inext.col << std::endl << std::endl;
//	};
//
//	system("pause");
//	return 0;
//}


