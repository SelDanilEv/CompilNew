.586
.MODEL flat, stdcall
includelib kernel32.lib
includelib msvcrt.lib
includelib libucrt.lib

system            PROTO C :DWORD           ;вывод cmd - команды

SetConsoleTitleA   PROTO :DWORD      ; установить заголовок окна консоли 
GetStdHandle       PROTO :DWORD      ; получить handle вывода на консоль
WriteConsoleA      PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD ; вывод на консоль

includelib "..\Debug\LP_asm01a.lib"
includelib LP_asm01a.lib

getmin	           PROTO :DWORD, :DWORD
getmax	           PROTO :DWORD, :DWORD


ExitProcess	PROTO   :DWORD

.STACK 4096												; выделение стека объемом 4 мегабайта

.CONST													; сегмент констант
consoletitle   db 'c functions',0
info		   byte 'max-min=',0	
minn		   byte 'min=',0
maxn		   byte 'max=',0	
newline		   byte '\n',0
space		   db ' ',0
equal		   db '=',0
clear		   byte 40 dup(0)
str_pause      db 'pause', 0

.DATA													; сегмент данных
array			DWORD	100,11,34,19,123,150,41,7,88,9,44
result1			byte 40 dup(0)				            ; массив 40 байтов, заполненный нулями
result2			byte 40 dup(0)				            ; массив 40 байтов, заполненный нулями
result3			byte 40 dup(0)				            ; массив 40 байтов, заполненный нулями
min				dword	?
max				dword	?

.CODE													; сегмент кода
	
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
   cmp byte ptr [esi + edi],0         ; сравниваем 2 числа 
   jne count                          ; переход к count, если они не равны
   push 0
   push 0
   push edi
   push pstr
   push eax
   call WriteConsoleA
   ret
   printconsole ENDP

int_to_char proc uses eax ebx ecx edi esi,   ; начало функции 
                      pstr: dword,           ; адрес строки результат
                      intfield: dword        ; преобразуемое число

    mov edi,pstr             ; адрес результата в -> edi
    mov esi,0                ; количество символов в результате 
    cdq                      ; преобразование 2го слова в учетверенное копирование знакового бита регистра eax на все биты регистра edx
    mov ebx,10               ; десятичная система счисления
    idiv ebx                 ; eax = eax/ebx, остаток -> edx
    test eax,80000000h       ; результат отрицательный ?
    jz plus                  ; если результат предыдущей команды 0, т.е.положительный то на plus
    neg eax                  ; eax = -eax
    neg edx                  ; edx = -edx
    mov cl, '-'              ; первый символ результата '-'
    mov [edi],cl             ; первый символ результата '-'
    inc edi                  ; ++edi
plus:
    push dx                  ; остаток -> стек
    inc esi                  ; ++esi
    test eax, eax            ; eax == 0?
    jz fin                   ; если да то на fin
    cdq                      ; знак распространили с eax на edx
    idiv ebx                 ; aex = eax/ebx, остаток -> edx
    jmp plus
fin:
    mov ecx, esi             ; количество ненулевых остатков = количеству символов в результате
write:                       ; цикл записи результата
    pop bx                   ; остаток из стека -> bx
    add bl,'0'               ; сформировали символ в bl
    mov [edi],bl             ; bl-> в результат
    inc edi                  ; edi++
    loop write               ; if (--ecx) > 0 goto write

	pop eax;
	ret 2
	push eax

    ret
int_to_char ENDP


main PROC												; точка входа
START:													; метка старта
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
	;------------------вывод----------
	mov eax,max
	push  eax            ; исходное число
    push offset result2        ; место для результата
    call int_to_char           ; вызов процедуры преобразования

    push offset consoletitle			; заголовок окна консоли
    push offset maxn					; выводимый текст
    call printconsole

	push offset consoletitle			
    push offset result2					
    call printconsole
	
	push offset consoletitle			
    push offset space					
    call printconsole
	;---------------------------------------
	mov eax,min
	push eax                   ; исходное число
    push offset result1        ; место для результата
    call int_to_char           ; вызов процедуры преобразования

    push offset consoletitle			; заголовок окна консоли
    push offset minn					; выводимый текст
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

	push eax                   ; исходное число
    push offset result3        ; место для результата
    call int_to_char           ; вызов процедуры преобразования

    push offset consoletitle			; заголовок окна консоли
    push offset info			; выводимый текст
    call printconsole
	
    push offset consoletitle			; заголовок окна консоли
    push offset result3        ; выводимый текст
    call printconsole
	;-----------------------------
	;push offset str_pause      ; адрес выводимой cmd-команды
	;call system                ; system("pause");
	push - 0											; код возрата процесса windows
	call ExitProcess									; завершение процесса 

main ENDP												; конец процедуры

end main												; конец модуля main