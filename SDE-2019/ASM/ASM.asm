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
	L0 sdword 0
	L1 sdword 5
	L2 sdword 10
	L3 sdword 1
	T0 byte 'Happy ', 0
	T1 byte 'New ', 0
	T2 byte 'Year', 0
	L4 sdword 0

.data
	buf byte 255 dup(0)
	cycleisneg dword 0
	buffer00000 sdword ?
	out01000 sdword ?
	x02000 sdword ?
	hello02000 byte 255 dup(0)
	T0T byte 255 dup(0)
	T1T byte 255 dup(0)
	T2T byte 255 dup(0)

.code
proc_sum proc, x01000 : dword, y01000 : dword
push ecx;
	push x01000
	push y01000
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop out01000
	mov eax,out01000
	ret
proc_sum endp
main proc
	START :
push ecx;
	push L0
	pop x02000
	push L1
	push L2
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative1
	mov buffer00000,ebx
	mov ecx,eax
	mov eax,0
	mov cycleisneg,eax
	jmp endcondcycle1
negative1 :
	mov buffer00000,ebx
	neg eax
	mov ecx,eax
	add ecx,1
	mov eax,1
	mov cycleisneg,eax
endcondcycle1 :
MARK1:
push ecx;
	push x02000
	push L3
	pop edx
	pop edx
	push L3
	push x02000
	call proc_sum
	push eax
	pop x02000
	push ecx
	push x02000
	call outlit
	pop ecx
	mov eax,cycleisneg
	cmp eax,0
	je iter1
	sub buffer00000,1
	jmp enditer1
iter1:
	add buffer00000,1
	enditer1:
loop MARK1
push ecx;
	push offset T0
	push offset T1
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push offset T2
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push offset hello02000
	call copytxt
pop ecx;
	push ecx
	push offset hello02000
	call outtxt
	pop ecx
	mov eax,L4
	push 0
	call sleep
	call ExitProcess
main endp
end main