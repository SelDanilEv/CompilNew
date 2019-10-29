#pragma once
#define IN_MAX_LEN_TEXT 1024*1024 //макс размер исходного кода 1MB
#define IN_CODE_ENDL '\0' // символ конца строки
// значение IN::F - запрещенный символ IN::T-разрешенный символ IN::I-игнорировать(не вводить),
#define IN_CODE_TABLE {\
         /*0*/  /*1*/  /*2*/  /*3*/  /*4*/  /*5*/  /*6*/  /*7*/  /*8*/  /*9*/  /*A*/  /*B*/  /*C*/  /*D*/  /*E*/  /*F*/\
	/*0*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F,/*0*/\
	/*1*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*1*/\
	/*2*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*2*/\
	/*3*/IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*3*/\
	/*4*/IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,/*4*/\
	/*5*/IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::T, IN::I, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T,/*5*/\
	/*6*/IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::F,/*6*/\
	/*7*/IN::F, IN::F, IN::T, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F,/*7*/\
	\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	' - ', IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
}
namespace In
{
	struct IN //исходные данные
	{
		enum { T = 1024, F = 2048, I = 4096 }; //Т-допустимый символ F- недопустимый  I- игнорировать
		int size; //размер исходного кода
		int lines; //строки
		int ignor;// количество проигнорированных
		unsigned char* text; //исходный текст
		int code[256]; // таблица проверки
	};
	IN getin(wchar_t infile[], wchar_t outfile[]);//Ввести входной поток 
}