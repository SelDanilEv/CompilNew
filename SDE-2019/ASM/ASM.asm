.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib
includelib ../Debug/mylib.lib

ExitProcess PROTO : DWORD
outtxt PROTO : DWORD
outlit PROTO : SDWORD
	copytxt PROTO : DWORD,:DWORD
	txtcon PROTO : DWORD,:DWORD

.stack 4096

.const
	L0 dword 5
	L1 dword 5
	T0 byte 'Hello', 0
	L2 dword 0

.data
	buffer00000 dword ?
	z01000 dword ?
	x02000 dword ?
	tema02000 byte 255 dup(0)

.code
proc_sum proc, x01000 : dword
	push x01000
	push x01000
	pop eax
	pop ebx
	mul ebx
	push eax
	pop z01000
	push z01000
	call outlit 
	mov eax,z01000
	ret
proc_sum endp
main proc
	START :
	push L0
	call proc_sum
	push eax
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop x02000
	push offset T0
	push offset tema02000
	call copytxt
	push x02000
	call outlit 
	push offset tema02000
	call outtxt 
	mov eax,L2
	push 0
	call ExitProcess
main endp
end main