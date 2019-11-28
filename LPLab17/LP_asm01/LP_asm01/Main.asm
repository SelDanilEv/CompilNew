.586P													; система команд
.MODEL FLAT,STDCALL										; модель памяти
includelib kernel32.lib									; компановщику : компоновать с кернел32

ExitProcess PROTO : DWORD								; прототип для завершения процесса виндоус

.STACK 4096												; выделение стека объемом 4 мегабайта

.CONST													; сегмент констант

.DATA													; сегмент данных


array			DWORD	100,11,34,25,163,124,41,7,88,9,44
maxnumb         DWORD   ?								
minnumb         DWORD   ?								


.CODE													; сегмент кода
main PROC												; точка входа
START:													; метка старта
	mov eax,offset array
	push eax
	push lengthof array -1
	call getmin

	push - 1											; код возрата процесса windows
	call ExitProcess									; завершение процесса 

	getmax PROC

		pop		eax
		pop		ebx
		mov		ecx,ebx
		pop		ebx
		mov		esi,ebx
		push	eax

		mov     eax,[esi]
		mov		maxnumb,eax

		FindMax:
		add		esi,4
		mov		edx,[esi]
		cmp		edx,maxnumb
		jg More
		jmp endFindMax

		More:
		mov		maxnumb,edx

		EndFindMax:
		loop FindMax

		ret 
	getmax ENDP

	getmin PROC	

		pop		eax
		pop		ebx
		mov		ecx,ebx
		pop		ebx
		mov		esi,ebx
		push	eax

		mov     eax,[esi]
		mov		maxnumb,eax
		MOV		eax,[esi]
		mov		minnumb,eax

		FindMin:
		add		esi,4
		mov		edx,[esi]
		cmp		edx,minnumb
		jl Less
		jmp endFindMin

		Less:
		mov		minnumb,edx

		EndFindMin:
		loop FindMin

		ret 
	getmin ENDP

main ENDP												; конец процедуры

end main												; конец модуля main