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
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in, parm.out);
		LexA::Tables myTables = LexA::analyze(In::getInfo().currentLine, (char *)In::getInfo().fulltext.c_str());                 //запуск лексического анализатора
		
		FilesManager::WriteFiles(myTables,log);

		std::ofstream filetrace;
		filetrace.open("trace.txt");
		MFST_TRACE_START
		MFST::Mfst mfst(myTables, GRB::getGreibach());
		if (!mfst.start(filetrace))
			throw ERROR_THROW(136);
		filetrace << "\n\n";
		mfst.savededucation();
		mfst.printrules(log);
		filetrace.close();

		Semantic::CheckSemanticBeforePolish(myTables);
		myTables = DoPolish(myTables);
		FilesManager::WriteFiles(myTables);

		Semantic::CheckSemanticAfterPolish(myTables);
		Generation::Generate(myTables);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	return 0;
}