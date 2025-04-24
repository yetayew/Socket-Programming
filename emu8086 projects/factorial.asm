
; You may customize this and other start-up templates;
;9403-472-455-0867 IAR 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
lea si,prompt 
mov ah,2 
mov cx,17  

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
mov ax,[si]
sub ax,30h
inc si
mov bx,[si]
sub bx,30h
mov dx,10
mul dx
add ax,bx

mov ah,0
mov cx,ax
sub cx,1
factorial:
mul cx 
loop factorial

outfact:

 
  
       
finish:
ret

inputs db '0','0'
result db '0','0','0','0','0'
prompt db "Enter the Number :"


