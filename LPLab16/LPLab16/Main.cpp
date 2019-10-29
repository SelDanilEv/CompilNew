#include "pch.h"
<<<<<<< HEAD
#include <tchar.h>
=======
#include <iostream>
#include <locale>
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2

int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
<<<<<<< HEAD
		In::IN in = In::getin(parm.in, parm.out);

		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);                
=======
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
<<<<<<< HEAD
=======

>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
	return 0;
}