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
	T0 byte 'Yes', 0
	T1 byte 'No', 0
	L1 sdword 1
	L2 sdword 0
	L3 sdword 0
	L4 sdword 0
	L5 sdword 0

.data
	buf byte 255 dup(0)
	buffer00000 sdword ?
	T0T byte 255 dup(0)
	T1T byte 255 dup(0)
	x04000 sdword ?

.code
proc_ch proc, x01000 : dword
	push buffer00000
	push L0
	pop eax
	pop ebx
	cmp eax,ebx
	jne CKECKNOT1
	push offset T0
	call outtxt
jmp OUTCHECK1
CKECKNOT1 :
	push offset T1
	call outtxt
	push buffer00000
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop buffer00000
	push x01000
	pop edx
	push x01000
	call proc_ch
	push eax
	pop x01000
OUTCHECK1 :
	mov eax,L2
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
	call sleep
	call ExitProcess
toend:
	ret
proc_ch endp
main proc
	START :
	push L3
	pop buffer00000
	push L4
	pop x04000
	push x04000
	pop edx
	push x04000
	call proc_ch
	push eax
	pop buffer00000
	mov eax,L5
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