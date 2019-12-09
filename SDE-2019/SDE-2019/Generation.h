#pragma once
#define BEFORE_DATA ".586\n.model flat, stdcall\n\nincludelib kernel32.lib\nincludelib libucrt.lib\nincludelib ../Debug/mylib.lib\n"
#define TEXTMAXSIZE 255
#define ASM_FILE_PATH "../ASM/ASM.asm"
#define ASMCYCLE "MARK"
#define ASMCHECK "OUTCHECK"

namespace Generation
{
	struct OneSegment {
		std::string Name;
		std::string Code;
	};
	std::string WriteSegment(OneSegment segment);

	void Generate(LexA::Tables);
	void GenerateOutput();
	void GenerateReturn();
	void GenerateExpression();
	void GenerateFunction(int);
}