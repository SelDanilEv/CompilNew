#pragma once
namespace FST
{
	struct RELATION					//�����:������ -> ������� ����� ��������� ��
	{
		char symbol;				//������ ��������	
		short nnode;				//����� ������� �������
		RELATION(
			char c = 0x00,			//������ ��������
			short ns = 0			//����� ������� �������
		);
	};

	struct NODE						//������� ����� ���������
	{
		short n_relation;			//���������� ����������� �����
		RELATION *relations;		//����������� �����
		NODE();
		NODE
		(short n,				//���������� ����������� �����
			RELATION rel, ...		//������ �����
		);
	};

	struct FST						//������������������� �������� �������
	{
		char* string;				//������� (������,����������� 0�00)
		short position;				//������� ������� � �������
		short nstates;				//���������� ��������� ��������
		NODE* nodes;				//���� ���������: [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;				//��������� ��������� �������� �� ������ �������
		FST(
			char* s,				//������� (������, ���������� 0�00)
			short ns,				//���������� ��������� ��������
			NODE n, ...				//������ ��������� (���� ���������)
		);
	};

	int getPosition(FST& fst);
	bool execute(FST& fst);
	int little(char* str);
	int text(char* str);
	int function(char* str);
	int New(char* str);
	int Return(char* str);
	int output(char* str);
	int start(char* str);
	int from(char* str);
	int to(char* str);
	int check(char* str);
	int Not(char* str);
	int id(char* str);
	//int Short(char* str);
	bool literalInt(char* str);
}
