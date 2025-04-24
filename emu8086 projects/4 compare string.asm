
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

lea si,password;fetching address of password variable
mov ah,1
mov cx,5
takeinput:
int 21h
mov [si],al
inc si
loop takeinput;we are taking inputs from the user (length of 5)  
 
mov dl,0Ah
mov ah,2
int 21h
mov dl,0Dh
int 21h
 
lea di,initial
lea si,password                       
mov dl,[si]
mov al,[di]
cmp al,dl;we are comparing the first character 
jne deny
int 21h 
inc si
inc di
mov dl,[si]
mov al,[di]
cmp al,dl;we are comparing the second character
jne deny
int 21h
inc si
inc di
mov dl,[si]
mov al,[di]
cmp al,dl ;we are comparing the third character
jne deny
int 21h 
inc si
inc di
mov dl,[si]
mov al,[di]
cmp al,dl;we are comparing the fourth character
jne deny
int 21h
inc si
inc di
mov dl,[si]
mov al,[di]
cmp al,dl;we are comparing the fifth character
jne deny
int 21h  
 
mov ah,2
mov dx,0Ah ;new line
int 21h 
mov dx,offset access ;string print
mov ah,09
int 21h 
jmp finish
deny: 
mov ah,2
mov dx,0Ah
int 21h
mov dx,offset denied;string print
mov ah,09
int 21h




finish:
ret 
access db "access granted","$"
denied db "access denied","$"
initial db "abcde";assume the initial saved password
password db ?



