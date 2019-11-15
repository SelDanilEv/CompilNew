.586P													; ������� ������
.MODEL FLAT,STDCALL										; ������ ������
includelib kernel32.lib									; ������������ : ����������� � ������32

ExitProcess PROTO : DWORD								; �������� ��� ���������� �������� �������

.STACK 4096												; ��������� ����� ������� 4 ���������

.CONST													; ������� ��������

.DATA													; ������� ������


maxnumb         DWORD   ?								
minnumb         DWORD   ?								


.CODE													; ������� ����

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