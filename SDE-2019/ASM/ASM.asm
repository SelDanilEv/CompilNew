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
	T0 byte ' ', 0
	L0 sdword 0
	T1 byte '*', 0
	L1 sdword 0
	L2 sdword 1
	L3 sdword 10
	T2 byte ' ', 0
	L4 sdword 10
	L5 sdword 1
	L6 sdword 0

.data
	buf byte 255 dup(0)
	buffer00000 sdword ?
	out00000 byte 255 dup(0)
	x00000 sdword ?
	cycleisneg1 dword 0
	T0T byte 255 dup(0)
	T1T byte 255 dup(0)
	cycleisneg2 dword 0
	cycleisneg3 dword 0
	T2T byte 255 dup(0)

.code
proc_show proc, u01000 : dword
	push offset T0
	push offset out00000
	call copytxt
	push L0
	push u01000
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative1
	mov buffer00000,ebx
	mov ecx,eax
	mov eax,0
	mov cycleisneg1,eax
	jmp endcondcycle1
negative1 :
	mov buffer00000,ebx
	neg eax
	mov ecx,eax
	add ecx,1
	mov eax,1
	mov cycleisneg1,eax
endcondcycle1 :
MARK1:
	push ecx
	push offset out00000
	push offset T1
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push offset out00000
	call copytxt
	mov eax,cycleisneg1
	cmp eax,0
	je iter1
	sub buffer00000,1
	jmp enditer1
iter1:
	add buffer00000,1
	enditer1:
	pop ecx
loop MARK1
	push offset out00000
	call outtxt
	mov eax,L1
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
	call sleep
	call ExitProcess
toend:
	ret
proc_show endp
main proc
	START :
	push L2
	push L3
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative2
	mov buffer00000,ebx
	mov ecx,eax
	mov eax,0
	mov cycleisneg2,eax
	jmp endcondcycle2
negative2 :
	mov buffer00000,ebx
	neg eax
	mov ecx,eax
	add ecx,1
	mov eax,1
	mov cycleisneg2,eax
endcondcycle2 :
MARK2:
	push ecx
	push buffer00000
	pop x00000
	push x00000
	pop edx
	push x00000
	call proc_show
	push eax
	pop x00000
	mov eax,cycleisneg2
	cmp eax,0
	je iter2
	sub buffer00000,1
	jmp enditer2
iter2:
	add buffer00000,1
	enditer2:
	pop ecx
loop MARK2
	push offset T2
	push offset out00000
	call copytxt
	push L4
	push L5
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative3
	mov buffer00000,ebx
	mov ecx,eax
	mov eax,0
	mov cycleisneg3,eax
	jmp endcondcycle3
negative3 :
	mov buffer00000,ebx
	neg eax
	mov ecx,eax
	add ecx,1
	mov eax,1
	mov cycleisneg3,eax
endcondcycle3 :
MARK3:
	push ecx
	push buffer00000
	pop x00000
	push x00000
	pop edx
	push x00000
	call proc_show
	push eax
	pop x00000
	mov eax,cycleisneg3
	cmp eax,0
	je iter3
	sub buffer00000,1
	jmp enditer3
iter3:
	add buffer00000,1
	enditer3:
	pop ecx
loop MARK3
	mov eax,L6
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