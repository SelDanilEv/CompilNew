.586
.model flat, stdcall
includelib kernel32.lib
includelib SDElib.lib
includelib libucrt.lib

ExitProcess PROTO : DWORD

EXTERN outlit :proc
EXTERN outtxt :proc

.stack 4096

.const
	L0 dword 0
	L1 dword 5
	L2 dword 0

.data
	buffer00000 dword 0
	z01000 dword 0
	x02000 dword 0

.code
proc_sum proc, x01000 : dword
	mov ebx,x01000
	mov eax,L0
	sub eax,ebx
	mov z01000, eax;
	ret
proc_sum endp
main proc
	START : 
	mov x02000, eax;
	push(10)
	call outlit
	push - 1
	call ExitProcess
main endp
end main