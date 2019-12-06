.586
.model flat, stdcall
includelib SDElib.lib
includelib kernel32.lib

ExitProcess PROTO : DWORD

.stack
4096
.const
	L0 dword 100
	L1 dword 200
	L2 dword 5
	L3 dword 6
	T0 byte 'tt', 0
	L4 dword 0

.data
	buffer00000 dword 0
	z01000 dword 0
	x02000 dword 0

.code
proc_sum proc, x01000 : dword, y01000 : byte
	mov ebx,L1
	mov eax,L0
	add eax,ebx
	mov ebx,x01000
	mov eax,eax
	sub eax,ebx
	mov z01000, eax;
proc_sum endp