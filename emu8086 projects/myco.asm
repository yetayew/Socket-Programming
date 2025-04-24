
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

lea si,kem
mov ah,2
mov cx,3

tt:
mov dl,[si]
int 21h
inc si
loop tt

lea si,input
mov ah,1
mov cx,3

hh:
int 21h
mov [si],al
inc si
loop hh

lea si,input 
mov al,[si]
sub al,30h
mov bl,100
mul bl
mov dl,al
inc si
mov al,[si]
sub al,30h
mov bl,10
mul bl
mov dh,al 
inc si
mov al,[si]
sub al,30h
add al,dh
add al,dl

 



ret
kem DB "hhy" 
input DB '0','0'




