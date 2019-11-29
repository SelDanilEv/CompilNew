#include "pch.h"
#include <iostream>
#include <locale>

int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, L"����", L" ��� ������", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		LexA::Tables myTables = LexA::analyze(In::getInfo().currentLine, (char *)In::getInfo().fulltext.c_str());                 //������ ������������ �����������
		Semantic::CheckSemantic(myTables);
		DoPolish(myTables);

		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	return 0;
}