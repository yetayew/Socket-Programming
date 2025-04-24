
; You may customize this and other start-up templates;
;9403-472-455-0867 IAR 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h
lea si,prompt 
mov ah,2 
mov cx,30  

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
mov al,[si]
sub al,30h
inc si
mov ah,[si]
sub ah,30h
mov dl,ah 
mov ah,0
mov bl,10
mul bl
add al,dl 

mov bl,9
mul bl 
mov bl,5
div bl 
add al,32

mov ch,ah
mov ah,0 
mov bl,100
cmp bl,al
jge div100
mov bl,10
div bl
add al,30h
add ah,30h
lea si,result
inc si
mov [si],al
inc si
mov [si],ah
inc si
mov al,ch
mov bl,10
mul bl
mov bl,5
div bl 
add al,30h
mov [si],al
jmp ending
div100:
mov bl,100
div bl
add al,30h
lea si,result
mov [si],al
mov al,ah
mov ah,0
mov bl,10
div bl
add al,30h
add ah,30h
inc si 
mov [si],al
inc si
mov [si],ah
inc si
mov al,ch
mov bl,10
mul bl
mov bl,5
div bl
add al,30h
mov [si],al


ending: 
mov dl,0Ah
mov ah,2
int 21h
mov dl,0Dh
int 21h
mov dl,0Ah
int 21h
mov dl,0Dh
int 21h
mov dl,09h
int 21h
int 21h
         
lea si,inputs         
mov dl,[si]
int 21h 
inc si
mov dl,[si]
int 21h 
mov dl,00h
int 21h 
mov dl,60h
int 21h
mov dl,43h
int 21h
mov dl,00h
int 21h
mov dl,3Dh
int 21h
mov dl,00h
int 21h

lea si,result
mov al,[si]
mov ah,0
mov bl,30h
cmp bl,al
jge 3digit_display

mov dl,[si]
cmp dl,30h
mov ah,2  
jle next
int 21h
next:
inc si
mov dl,[si]
int 21h
inc si
mov dl,[si]
int 21h
mov dl,2Eh
int 21h
inc si 
mov dl,[si]
int 21h
inc si
mov dl,[si]
int 21h
mov dl,00h
int 21h
mov dl,60h
int 21h
mov dl,46h
int 21h 
jmp finish
3digit_display:
mov dl,[si]
mov ah,2
int 21h
inc si
mov dl,[si]
int 21h 
inc si
mov dl,[si]
int 21h
mov dl,2Eh;printing dot 
int 21h
inc si
mov dl,[si]
int 21h
inc si
mov dl,[si]
int 21h 
mov dl,00h
int 21h
mov dl,60h
int 21h
mov dl,46h
int 21h      
       
finish:
ret

inputs db '0','0'
result db '0','0','0','0','0'
prompt db "Enter temperature value in oC:"


