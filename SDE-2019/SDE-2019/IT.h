#pragma once
#define ID_MAXSIZE		32			// ������������ ���������� �������� � ��������������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x00000000	// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffffffff	// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255			// 

namespace IT			// ������� ���������������
{
	enum IDDATATYPE { LIT = 1, TXT = 2 /*,SHR =3 */,Err=0};			// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, E = 0 };	// ���� ���������������: ����������, �������, ��������, �������

	struct Entry	// ������ ������� ���������������
	{
		short areaOfVisibility[5] = { 0 };
		int	idxfirstLE;			// ������ ������ ������ � ������� ������
		unsigned char id[ID_MAXSIZE];		// �������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;			// ��� ������
		IDTYPE		idtype;				// ��� ��������������
		union
		{
			int vint;					// �������� integer
			short vshr;					// �������� integer
			struct
			{
				int len;						// ���������� �������� � string
				unsigned char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr;				// �������� string
		} value;		// �������� ��������������
	};

	struct IdTable				// ��������� ������� ���������������
	{
		int maxsize;			// ������� ������� ��������������� < TI_MAXSIZE
		int size;				// ������� ������ ������� ��������������� < maxsize
		Entry* table;			// ������ ����� ������� ���������������
	};

	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		Entry entry			// ������ ������� ���������������
	);

	Entry GetEntry(			// �������� ������ ������� ���������������
		IdTable& idtable,	// ��������� ������� ���������������
		int n				// ����� ���������� ������
	);

	int IsId(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
		IdTable& idtable,	// ��������� ������� ���������������
		unsigned char id[ID_MAXSIZE]	// �������������
	);

	int IsIdWithAreaOfVisibility(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���) � � �������� ���������
		IdTable& idtable,	// ��������� ������� ���������������
		unsigned char id[ID_MAXSIZE],	// �������������
		short area[5]	// ������� ���������
	);

	void Delete(IdTable& idtable);	// ������� ������� ������ (���������� ������)
	void showTable(IdTable& idtable, std::ofstream &file);
};