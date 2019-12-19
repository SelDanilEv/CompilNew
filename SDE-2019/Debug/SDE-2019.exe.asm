.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib
includelib E:/Compil/SDE-2019/Debug/mylib.lib

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
	mesoverflow byte 'Overflow',0
	L0 sdword 2
	L1 sdword 0
	T0 byte '@', 0
	T1 byte '*', 0
	L2 sdword 0
	L3 sdword 0
	T2 byte '@', 0
	T3 byte '*', 0
	L4 sdword 0
	L5 sdword 0
	L6 sdword 0
	L7 sdword 9
	L8 sdword 0
	T4 byte ' ', 0
	T5 byte 'Sum', 0
	L9 sdword 0

.data
	buf byte 255 dup(0)
	buffer00000 sdword ?
	out00000 byte 255 dup(0)
	x00000 sdword ?
	sum00000 sdword ?
	cycleisneg1 dword 0
	cyclestartvalue1 dword 0
	T0T byte 255 dup(0)
	T1T byte 255 dup(0)
	T2T byte 255 dup(0)
	T3T byte 255 dup(0)
	cycleisneg2 dword 0
	cyclestartvalue2 dword 0
	cycleisneg3 dword 0
	cyclestartvalue3 dword 0
	T4T byte 255 dup(0)
	T5T byte 255 dup(0)

.code

proc_addn proc
	push offset out00000
	pop edx
	push offset out00000
	call textlenght
	push eax
	pop x00000
	mov eax,x00000
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
	call sleep
	call ExitProcess
overflow:
	push offset mesoverflow
	call outtxt
	call sleep
	call ExitProcess
toend:
	ret
proc_addn endp
proc_show proc, u02000 : dword
	push u02000
	push L0
	pop ebx
	pop eax
	cmp ebx,0
	je divbyzero
	mov edx,0
	idiv ebx
	push edx
	pop x00000
	push x00000
	push L1
	pop eax
	pop ebx
	cmp eax,ebx
	jne CKECKNOT1
	push offset T0
	push offset out00000
	call copytxt
jmp OUTCHECK1
CKECKNOT1 :
	push offset T1
	push offset out00000
	call copytxt
OUTCHECK1 :
	push L2
	push u02000
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative1
	mov buffer00000,ebx
	mov cyclestartvalue1,eax
	add eax,1
	mov ecx,eax
	mov eax,0
	mov cycleisneg1,eax
	jmp endcondcycle1
negative1 :
	mov buffer00000,ebx
	mov cyclestartvalue1,edx
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
	push ecx
	mov eax,cycleisneg1
	cmp eax,0
	je iter1
	mov eax,cyclestartvalue1
	pop ecx
	add eax,ecx
	push ecx
	mov buffer00000,eax
	jmp enditer1
iter1:
	mov eax,cyclestartvalue1
	pop ecx
	sub eax,ecx
	push ecx
	mov buffer00000,eax
	enditer1:
	push x00000
	push L3
	pop eax
	pop ebx
	cmp eax,ebx
	jne CKECKNOT2
	push offset out00000
	push offset T2
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push offset out00000
	call copytxt
jmp OUTCHECK2
CKECKNOT2 :
	push offset out00000
	push offset T3
	pop eax
	pop ebx
	push offset buf
	push ebx
	push eax
	call txtcon
	push eax
	push offset out00000
	call copytxt
OUTCHECK2 :
jmp MARK1
MARKOUT1:
	call proc_addn
	push eax
	pop x00000
	push sum00000
	push x00000
	pop eax
	pop ebx
	add eax, ebx
	push eax
	jo overflow
	pop sum00000
	push offset out00000
	call outtxt
	push x00000
	call outlit
	mov eax,L4
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
	call sleep
	call ExitProcess
overflow:
	push offset mesoverflow
	call outtxt
	call sleep
	call ExitProcess
toend:
	ret
proc_show endp

main proc
	START :
	push L5
	push L6
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative2
	mov buffer00000,ebx
	mov cyclestartvalue2,eax
	add eax,1
	mov ecx,eax
	mov eax,0
	mov cycleisneg2,eax
	jmp endcondcycle2
negative2 :
	mov buffer00000,ebx
	mov cyclestartvalue2,edx
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
	push ecx
	mov eax,cycleisneg2
	cmp eax,0
	je iter2
	mov eax,cyclestartvalue2
	pop ecx
	add eax,ecx
	push ecx
	mov buffer00000,eax
	jmp enditer2
iter2:
	mov eax,cyclestartvalue2
	pop ecx
	sub eax,ecx
	push ecx
	mov buffer00000,eax
	enditer2:
	push buffer00000
	pop edx
	push buffer00000
	call proc_show
	push eax
	pop x00000
jmp MARK2
MARKOUT2:
	push L7
	push L8
	pop eax
	pop ebx
	mov edx,eax
	sub eax,ebx
	cmp eax,0
	jl negative3
	mov buffer00000,ebx
	mov cyclestartvalue3,eax
	add eax,1
	mov ecx,eax
	mov eax,0
	mov cycleisneg3,eax
	jmp endcondcycle3
negative3 :
	mov buffer00000,ebx
	mov cyclestartvalue3,edx
	neg eax
	mov ecx,eax
	add ecx,1
	mov eax,1
	mov cycleisneg3,eax
endcondcycle3 :
	push ecx
MARK3:pop ecx
	cmp ecx,0
je MARKOUT3
	sub ecx,1
	push ecx
	mov eax,cycleisneg3
	cmp eax,0
	je iter3
	mov eax,cyclestartvalue3
	pop ecx
	add eax,ecx
	push ecx
	mov buffer00000,eax
	jmp enditer3
iter3:
	mov eax,cyclestartvalue3
	pop ecx
	sub eax,ecx
	push ecx
	mov buffer00000,eax
	enditer3:
	push buffer00000
	pop edx
	push buffer00000
	call proc_show
	push eax
	pop x00000
jmp MARK3
MARKOUT3:
	push offset T4
	call outtxt
	push offset T5
	call outtxt
	push sum00000
	call outlit
	mov eax,L9
	push 0
jmp toend
divbyzero:
	push offset mesdivbyzero
	call outtxt
jmp toend
overflow:
	push offset mesoverflow
	call outtxt
toend:
	call sleep
	call ExitProcess
main endp
end main
