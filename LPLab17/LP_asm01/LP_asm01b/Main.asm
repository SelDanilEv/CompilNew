.586
.MODEL flat, stdcall
includelib kernel32.lib
includelib msvcrt.lib
includelib libucrt.lib

system            PROTO C :DWORD           ;����� cmd - �������

SetConsoleTitleA   PROTO :DWORD      ; ���������� ��������� ���� ������� 
GetStdHandle       PROTO :DWORD      ; �������� handle ������ �� �������
WriteConsoleA      PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD ; ����� �� �������

includelib "..\Debug\LP_asm01a.lib"
includelib LP_asm01a.lib

getmin	           PROTO :DWORD, :DWORD
getmax	           PROTO :DWORD, :DWORD


ExitProcess	PROTO   :DWORD

.STACK 4096												; ��������� ����� ������� 4 ���������

.CONST													; ������� ��������
consoletitle   db 'c functions',0
info		   byte 'max-min=',0	
minn		   byte 'min=',0
maxn		   byte 'max=',0	
newline		   byte '\n',0
space		   db ' ',0
equal		   db '=',0
clear		   byte 40 dup(0)
str_pause      db 'pause', 0

.DATA													; ������� ������
array			DWORD	100,11,34,19,123,150,41,7,88,9,44
result1			byte 40 dup(0)				            ; ������ 40 ������, ����������� ������
result2			byte 40 dup(0)				            ; ������ 40 ������, ����������� ������
result3			byte 40 dup(0)				            ; ������ 40 ������, ����������� ������
min				dword	?
max				dword	?

.CODE													; ������� ����
	
	printconsole PROC uses eax ebx ecx esi edi,
                      pstr: dword, ptitle: dword
   push ptitle
   call SetConsoleTitleA
   push -11
   call GetStdHandle
   mov esi, pstr
   mov edi, -1
count:
   inc edi
   cmp byte ptr [esi + edi],0         ; ���������� 2 ����� 
   jne count                          ; ������� � count, ���� ��� �� �����
   push 0
   push 0
   push edi
   push pstr
   push eax
   call WriteConsoleA
   ret
   printconsole ENDP

int_to_char proc uses eax ebx ecx edi esi,   ; ������ ������� 
                      pstr: dword,           ; ����� ������ ���������
                      intfield: dword        ; ������������� �����

    mov edi,pstr             ; ����� ���������� � -> edi
    mov esi,0                ; ���������� �������� � ���������� 
    cdq                      ; �������������� 2�� ����� � ������������ ����������� ��������� ���� �������� eax �� ��� ���� �������� edx
    mov ebx,10               ; ���������� ������� ���������
    idiv ebx                 ; eax = eax/ebx, ������� -> edx
    test eax,80000000h       ; ��������� ������������� ?
    jz plus                  ; ���� ��������� ���������� ������� 0, �.�.������������� �� �� plus
    neg eax                  ; eax = -eax
    neg edx                  ; edx = -edx
    mov cl, '-'              ; ������ ������ ���������� '-'
    mov [edi],cl             ; ������ ������ ���������� '-'
    inc edi                  ; ++edi
plus:
    push dx                  ; ������� -> ����
    inc esi                  ; ++esi
    test eax, eax            ; eax == 0?
    jz fin                   ; ���� �� �� �� fin
    cdq                      ; ���� �������������� � eax �� edx
    idiv ebx                 ; aex = eax/ebx, ������� -> edx
    jmp plus
fin:
    mov ecx, esi             ; ���������� ��������� �������� = ���������� �������� � ����������
write:                       ; ���� ������ ����������
    pop bx                   ; ������� �� ����� -> bx
    add bl,'0'               ; ������������ ������ � bl
    mov [edi],bl             ; bl-> � ���������
    inc edi                  ; edi++
    loop write               ; if (--ecx) > 0 goto write

	pop eax;
	ret 2
	push eax

    ret
int_to_char ENDP


main PROC												; ����� �����
START:													; ����� ������
	mov eax,offset array
	push lengthof array -1
	push eax
	call getmin
	mov min,eax
	mov eax,offset array
	push lengthof array-1
	push eax
	call getmax
	mov max,eax
	;------------------�����----------
	mov eax,max
	push  eax            ; �������� �����
    push offset result2        ; ����� ��� ����������
    call int_to_char           ; ����� ��������� ��������������

    push offset consoletitle			; ��������� ���� �������
    push offset maxn					; ��������� �����
    call printconsole

	push offset consoletitle			
    push offset result2					
    call printconsole
	
	push offset consoletitle			
    push offset space					
    call printconsole
	;---------------------------------------
	mov eax,min
	push eax                   ; �������� �����
    push offset result1        ; ����� ��� ����������
    call int_to_char           ; ����� ��������� ��������������

    push offset consoletitle			; ��������� ���� �������
    push offset minn					; ��������� �����
    call printconsole

	push offset consoletitle			
    push offset result1					
    call printconsole
	
	push offset consoletitle			
    push offset space					
    call printconsole
	;---------------------------------------
	mov eax,max
	sub eax,min

	push eax                   ; �������� �����
    push offset result3        ; ����� ��� ����������
    call int_to_char           ; ����� ��������� ��������������

    push offset consoletitle			; ��������� ���� �������
    push offset info			; ��������� �����
    call printconsole
	
    push offset consoletitle			; ��������� ���� �������
    push offset result3        ; ��������� �����
    call printconsole
	;-----------------------------
	;push offset str_pause      ; ����� ��������� cmd-�������
	;call system                ; system("pause");
	push - 0											; ��� ������� �������� windows
	call ExitProcess									; ���������� �������� 

main ENDP												; ����� ���������

end main												; ����� ������ main