
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ax,[y]
sub ax,30h
mov dl,[x]
sub dx,30h
mov cx,dx
result:
mul cx
loop result 
mov [y],ax;moving the result to y
mov dx,[y]

ret

y dw '1'
x db '8';assume the maximum factorial result is 8! for ax


