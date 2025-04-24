 
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

INCLUDE "EMU8086.INC"
                                
MOV DX, OFFSET MAIN
MOV AH, 9 
INT 21H
CALL SCAN_NUM
MOV NUM, CX

MOV BX, 1
MOV AX, 1 
JMP LABEL1

LABEL1:
MUL BX
INC BX
CMP BX,NUM
JA EXIT
JMP LABEL1

EXIT:
LEA SI, MSG
CALL PRINT_STRING
CALL PRINT_NUM  
RET
  
NUM DW ?
MAIN DB "FACTORIAL CALCULATOR. NUM: $"
MSG DB 13,10, "THE RESULT IS: ",0
  
DEFINE_PRINT_NUM
DEFINE_SCAN_NUM
DEFINE_PRINT_NUM_UNS
DEFINE_PRINT_STRING


ret





; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

lea si,prompt 
mov ah,2 
mov cx,28  

Display:
mov dl,[si] 
int 21h 
inc si 
loop  Display

lea si,inputs
mov ah,1
mov cx,2
takeinput:
int 21h
mov [si],al
inc si
loop takeinput

lea si,inputs
mov dl,[si] 
sub bl,30h
inc si
mov bh,[si]
sub bh,30h

mov ax,0 
mov al,bl
mov dh,10
mul dh
add al,bh
mov dh,9
mul dh
mov dh,5
mul dh
add al,32 
mov bl,ah
cmp al,99
jg 3d
jmp 2d
jmp ending 
3d:  
ending:
 

ret
inputs db '0','0'
result db '0','0','0','.','0','0'
prompt db "Enter the temperature in oC: "
 
proc 2d:
    
mov bh,10
mov ah,0
div bh
add al,30h
add ah,30h
lea si,result
inc si
mov [si],al
inc si
mov [si],ah

endp

proc 3d:
    
mov bh,100
mov ah,0
div bh
add al,30h
lea si,result
mov [si],al
mov al,ah
mov bh,10
mov ah,0
div bh
add ah,30h
add al,30h
inc si
mov [si],al
inc si
mov [si],ah

endp



