@ECHO OFF
ml /c /coff /Zi "\ASM\ASM.asm"
link /OPT:NOREF /DEBUG "\ASM\Debug\ASM.obj" "\Debug\kernel32.lib" "\Debug\mylib.lib" /SUBSYSTEM:CONSOLE
call \Debug\ASM.exe			