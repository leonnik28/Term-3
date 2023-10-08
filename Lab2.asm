.model simple

.stack 64h

.data
    message db 200,201 dup ('$')
    slovo db 200,201 dup ('$')
    firstRule db "Enter string whith 'trash words' that we need to delete:$"
    secondRule db "'trash words' have been deleted. New string: $"
    thirdRule db "Enter 'trash word':$"
.code
start: 

    mov ax, @data
    mov ds, ax
     
    xor si,si
    xor di,di
    
    mov ah,9h
    lea dx,firstRule
    int 21h
    
    mov ah,2h 
    mov dx,0ah 
    int 21h
    
    mov ah,2h 
    mov dx,0dh 
    int 21h
    
    mov ah,0ah
    lea dx,message
    int 21h
    
    mov ah,2h 
    mov dx,0ah 
    int 21h
    
    mov ah,2h 
    mov dx,0dh 
    int 21h
    
    mov ah,9h
    lea dx,thirdRule
    int 21h
    
    mov ah,2h 
    mov dx,0ah 
    int 21h
    
    mov ah,2h 
    mov dx,0dh 
    int 21h
    
    mov ah,0ah
    lea dx,slovo
    int 21h   
    
    mov si,offset message
    mov di,offset slovo+2    
;___________________________{    
    add si,2
    mov dx,si
Nool_first_Mark:
    add si,1
    cmp [si],'$'
    je noolhelpjump
    jmp Nool_first_Mark
    noolhelpjump:
Nool_second_Mark:        
    cmp si,dx
    je noolhelpjumptwo
    mov bl,[si-1]  
    mov [si],bl
    sub si,1 
    jmp Nool_second_Mark
    noolhelpjumptwo:
    mov [si],' '
;___________________________}     
    jmp First_Mark  
 
Under_First_Mark:
    mov si,dx
    mov di,offset slovo+2
     
First_Mark: 

    cmp [si],'$'
    je End
    xor cx,cx
    xor bx,bx 
    mov cl,[si]
    mov bl,[di]
    cmp cl,bl
    je Cycle_jump_first
    mov di,offset slovo+2
    add si,1
    jmp First_Mark    
Cycle_jump_first:
    add di,1
    add si,1
            
    xor bx,bx
    ;xor cx,cx 
    ;mov cx,'$'           
    mov bl,[di]           
    cmp bl,0dh
    je Second_Mark
    jmp First_Mark
    
Second_Mark:
    
    sub si,1
    cmp [si],' '
    je Cycle_jump_second
    jmp Second_Mark
Cycle_jump_second:
    add si,1
    mov dx,si
    ;sub si,1
    
Third_Mark:

    cmp [si],'$'
    je Cycle_jump_third
    mov bx,[si+1]  
    mov [si],bx
    add si,1
    jmp Third_Mark
Cycle_jump_third:
    mov si,dx
    cmp [si],' '
    je help_jump
    cmp [si],'$'
    je End
    jmp Third_Mark

help_jump:
    cmp [si],'$'
    je Under_First_Mark
    mov bx,[si+1]  
    mov [si],bx
    add si,1
    jmp help_jump
    
End:

    mov ah,2h 
    mov dx,0ah 
    int 21h
    
    mov ah,2h 
    mov dx,0dh 
    int 21h
    
    mov ah,9h
    lea dx,secondRule
    int 21h
 
    mov ah,2h 
    mov dx,0ah 
    int 21h
    
    mov ah,2h 
    mov dx,0dh 
    int 21h 
    
    mov ah,9h
    lea dx,message+3
    int 21h 
    
    int 20h     
end start
