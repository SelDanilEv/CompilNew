.586P													; ������� ������
.MODEL FLAT,STDCALL										; ������ ������
includelib kernel32.lib									; ������������ : ����������� � ������32

ExitProcess PROTO : DWORD								; �������� ��� ���������� �������� �������
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD	; �������� ��� ������� ������ ����

.STACK 4096												; ��������� ����� ������� 4 ���������

.CONST													; ������� ��������

.DATA													; ������� ������

HW				DD		?								
array			DWORD	100,11,34,2,123,124,41,7,88,9,44
maxnumb         DWORD   ?								
minnumb         DWORD   ?								
STR1			BYTE	"��������", 0					;���������
STR2			BYTE	"�����3+5= ", 0					;�����
MB_OK			EQU		6	
counter			DD		0								;�������


.CODE													; ������� ����
main PROC												; ����� �����
START:													; ����� ������
	mov eax,offset array
	push eax
	push 10
	call getmin

	push - 1											; ��� ������� �������� windows
	call ExitProcess									; ���������� �������� 

	getmax PROC
		push ebp
		mov ebp,esp


		mov		ecx,[ebp+8]
		mov		esi,[ebp+12]

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

		pop eax
		pop eax
		pop ebx
		pop ebx
		push eax

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


main ENDP												; ����� ���������

end main												; ����� ������ main