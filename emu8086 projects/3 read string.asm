
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

call read 

ret 
read proc
    lea si,input
    mov ah,1
    mov cx,5
    take:
    mov al,[si]
    inc si
    int 21h
    loop take
    ret
read endp
input db ?    


