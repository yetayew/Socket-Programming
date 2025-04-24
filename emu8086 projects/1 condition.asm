
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h 
mov dx,offset prompt1 ;string print
mov ah,09
int 21h
lea si,x;fetching address of x 
mov ah,1
int 21h
mov [si],al;assume one digit
inc si

mov ah,2
mov dx,0Ah ;new line
int 21h 
mov dl,0Dh
int 21h
mov dx,offset prompt2 ;string print
mov ah,09
int 21h 
lea si,y;fetching address of y 
mov ah,1
int 21h
mov [si],al;assume one digit
inc si

mov al,[y]
mov bl,[x]
cmp al,bl
jl else
add bl,1
mov [x],bl
jmp finish
else:
sub al,1
mov [y],al 
 
finish:
lea si,x
mov ah,2
mov dx,0Ah ;new line
int 21h
mov dl,0Dh
int 21h
mov dl,78h
int 21h
mov dl,00h
int 21h
mov dl,3Dh
int 21h
mov dl,00h
int 21h
mov dl,[x]
int 21h

lea si,y
mov ah,2 
mov dl,0Ah
int 21h
mov dl,0Dh
int 21h
mov dl,79h
int 21h
mov dl,00h
int 21h
mov dl,3Dh
int 21h
mov dl,00h
int 21h
mov dl,[y]
int 21h


ret
y db ? 
x db ?
prompt1 db "Enter the number for x :","$"
prompt2 db "Enter the number for y :","$"



