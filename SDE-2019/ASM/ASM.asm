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
	L0 sdword 5
	L1 sdword 5
	L2 sdword 5
	L3 sdword 0

.data
	buf byte 255 dup(0)
	cycleisneg dword 0
	buffer00000 sdword ?
	x01000 sdword ?

.code

main proc
	START :
push ecx;
	push L0
	push L1
	push L2
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop ebx
	cmp ebx,0
	je divbyzero
	mov edx,0
	idiv ebx
	push eax
	pop x01000
	push ecx
	push x01000
	call outlit
	pop ecx
	mov eax,L3
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