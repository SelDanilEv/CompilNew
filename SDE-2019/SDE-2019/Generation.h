#pragma once
#define BEFORE_DATA ".586\n.model flat, stdcall\nincludelib SDElib.lib\nincludelib kernel32.lib\n"
#define TEXTMAXSIZE 255
#define ASM_FILE_PATH "../ASM/ASM.asm"

namespace Generation
{
	struct OneSegment {
		std::string Name;
		std::string Code;
	};
	std::string WriteSegment(OneSegment segment);

	void Generate(LexA::Tables);
}