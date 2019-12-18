@ECHO OFF
ml /c /coff /Zi "ASM.asm"
link /OPT:NOREF /DEBUG "ASM.obj" "Kernel32.lib" "mylib.lib" /SUBSYSTEM:CONSOLE
call ASM.exe			