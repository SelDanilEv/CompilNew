.586P													; система команд
.MODEL FLAT,STDCALL										; модель памяти
includelib kernel32.lib									; компановщику : компоновать с кернел32

ExitProcess PROTO : DWORD								; прототип для завершения процесса виндоус

.STACK 4096												; выделение стека объемом 4 мегабайта

.CONST													; сегмент констант

.DATA													; сегмент данных


maxnumb         DWORD   ?								
minnumb         DWORD   ?								


.CODE													; сегмент кода

	getmax PROC  first:dword,count:dword
	
		mov		esi,first
		mov		ecx,count

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

		mov eax,maxnumb
		ret 
	getmax ENDP

	getmin PROC		first:dword,count:dword
		mov		esi,first
		mov		ecx,count

		mov     eax,[esi]
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

		mov eax,minnumb
		ret 
	getmin ENDP

end