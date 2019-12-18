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
	L0 sdword 10
	L1 sdword 5
	T0 byte 'func buffer', 0
	L2 sdword 0
	L3 sdword 0
	L4 sdword 10
	T1 byte 'start buffer', 0
	L5 sdword 0

.data
	buf byte 255 dup(0)
	buffer00000 sdword ?
	x00000 sdword ?
	cycleisneg1 dword 0
	T0T byte 255 dup(0)
	cycleisneg2 dword 0
	T1T byte 255 dup(0)

.code

proc_prnt proc
	push L0
	push L1
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
	push ecx
MARK1:pop ecx
	cmp ecx,0
je MARKOUT1
	sub ecx,1
	mov buffer00000,ecx
	push ecx
	push offset T0
	call outtxt
	push buffer00000
	call outlit
	mov eax,cycleisneg1
	cmp eax,0
	je iter1
	sub buffer00000,1
	jmp enditer1
iter1:
	add buffer00000,1
	enditer1:
jmp MARK1
MARKOUT1:
	mov eax,L2
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
	call sleep
	call ExitProcess
toend:
	ret
proc_prnt endp

main proc
	START :
	push L3
	push L4
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
	push ecx
MARK2:pop ecx
	cmp ecx,0
je MARKOUT2
	sub ecx,1
	mov buffer00000,ecx
	push ecx
	push offset T1
	call outtxt
	push buffer00000
	call outlit
	call proc_prnt
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
jmp MARK2
MARKOUT2:
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

