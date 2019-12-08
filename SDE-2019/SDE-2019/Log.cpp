#include "pch.h"
#include "Log.h"

#include <ctime>

namespace Log             //������������ ����� Log
{
	LOG Log::getlog(wchar_t logfile[])
	{
		LOG res;
		res.stream = new std::ofstream;   //�������� ������
		res.stream->open(logfile);
		if (!res.stream)
			throw ERROR_THROW(103);
		wcscpy_s(res.logfile, logfile);    //�������� � ���
		return res;
	}
	void WriteLine(LOG log, const char * c, ...)
	{
		const char **ptr = &c;     //������� ���������
		while (strlen(*ptr))         //�� �""
		{
			*log.stream << *ptr;
			++ptr;                    //���� ��������
		}
		*log.stream << std::endl;
	}
	void WriteLine(LOG log, const wchar_t * c, ...)
	{
		const wchar_t **ptr = &c;
		while (wcslen(*ptr))
		{
			char out[PARM_MAX_SIZE];
			size_t charsConverted = 0;								 //wchar_t* � char
			wcstombs_s(&charsConverted, out, *ptr, PARM_MAX_SIZE);	  //������ � ������ ��������������� ������
			*log.stream << out;									    // ������
			++ptr;
		}
		*log.stream << std::endl;
	}
	void WriteLog(LOG log)
	{
		time_t  t = time(nullptr);
		tm  now;
		localtime_s(&now, &t);										//������� ���
		char date[PARM_MAX_SIZE];									//������ ��� ������ �������
		strftime(date, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);	//������� ������������� ��������� tm � ������ c ���� ���-��� �������� ��� ����������� PARM_MAX_SIZE
		*log.stream << "---- �������� ------- ����: " << date << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)            //������ ���������
	{
		*log.stream << "---- ��������� -------" << std::endl;
		char out[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, out, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << out << std::endl;
	}
	void WriteIn(LOG log, In::IN in)                       //������ � ����
	{
		*log.stream << "======= �������� ������ =====" << std::endl;
		*log.stream << "���������� ��������: " << in.size << std::endl;
		*log.stream << "���������������:     " << in.ignor << std::endl;
		*log.stream << "���������� �����:    " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)             //������
	{
		if (log.stream == nullptr || !log.stream->is_open())
		{
			std::cout << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		}
		else
		{
			*log.stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		}
	}
	void Close(LOG log)            //�������� ������
	{
		if (log.stream != nullptr)
		{
			log.stream->close();
			delete log.stream;
		}
	}

};
