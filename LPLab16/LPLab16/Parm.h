#pragma once
#define PARM_IN		L"-in:"
#define PARM_OUT	L"-out:"
#define PARM_LOG	L"-log:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".out"
#define PARM_LOG_DEFAULT_EXT L".log"

namespace Parm         //��������� 
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];       //����� ������
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
		PARM();
	};
	PARM getparm(int argc, _TCHAR** argv);    // ��������� � �������� �����������
<<<<<<< HEAD
};
=======
};
>>>>>>> 13b98efb756c1661bac5503f09b570e4133522f2
