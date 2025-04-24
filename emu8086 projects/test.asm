
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

lea si,inputs
mov cx,5
mov ah,1
take:
mov al,[si]
int 21h
inc si
loop take

lea si,inputs
mov cx,5
mov ah,2 
display:
mov dl,[si]
int 21h
inc si
loop display

ret
inputs db ?



