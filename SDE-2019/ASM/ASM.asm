.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib
includelib ../Debug/mylib.lib

ExitProcess PROTO : DWORD
outtxt PROTO : DWORD
outlit PROTO : SDWORD
copytxt PROTO : DWORD,:DWORD
txtcon PROTO : DWORD,:DWORD,:DWORD
cleartxt PROTO : DWORD
sleep PROTO
textlenght PROTO : DWORD

.stack 4096

.const
	mesdivbyzero byte 'Divide by zero',0
	L0 sdword -2
	L1 sdword -5
	T0 byte 'true', 0
	T1 byte 'false', 0
	L2 sdword 0

.data
	buf byte 255 dup(0)
	buffer00000 sdword ?
	T0T byte 255 dup(0)
	T1T byte 255 dup(0)

.code


main proc
	START :
	push L0
	push L1
	pop eax
	pop ebx
	cmp eax,ebx
	jng CKECKNOT1
	push offset T0
	call outtxt
jmp OUTCHECK1
CKECKNOT1 :
	push offset T1
	call outtxt
OUTCHECK1 :
	mov eax,L2
	push 0
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
toend:
	call sleep
	call ExitProcess
main endp
end main

