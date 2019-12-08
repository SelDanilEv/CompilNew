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

.stack 4096

.const
	L0 sdword 6
	L1 sdword 6
	T0 byte 'new Year', 0
	L2 sdword 0
	L3 sdword 0
	L4 sdword 15
	L5 sdword 4
	T1 byte 'Happy ', 0
	L6 sdword 0

.data
	buf byte 255 dup(0)
	cycleisneg dword 0
	buffer00000 sdword ?
	T0T byte 255 dup(0)
	x02000 sdword ?
	T1T byte 255 dup(0)

.code
proc_sum proc, x01000 : dword, q01000 : ptr dword
push ecx;
	push L0
	push L1
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	push buffer00000
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop x01000
push ecx;
	push q01000
	push offset T0
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push q01000
	call copytxt
pop ecx;
	push ecx
	push x01000
	call outlit
	pop ecx
	push ecx
	push q01000
	call outtxt
	pop ecx
	mov eax,L2
	ret
proc_sum endp
main proc
	START :
	push L3
	push L4
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
	mov buffer00000,edx
	neg eax
	mov ecx,eax
	mov eax,1
	mov cycleisneg,eax
endcondcycle1 :
MARK1:
push ecx;
	push L5
	push offset T1
	pop edx
	pop edx
push ecx;
	push offset T1
	push offset T1T
	call copytxt
pop ecx;
	push offset T1T
	push L5
	call proc_sum
	push eax
	pop x02000
	mov eax,cycleisneg
	cmp eax,0
	je iter1
	sub buffer00000,1
	jmp enditer1
iter1:
	add buffer00000,1
	enditer1:
loop MARK1
	mov eax,L6
	push 0
	call sleep
	call ExitProcess
main endp
end main