.model small

.data
name_input_file db 50 DUP(0)    
name_output_file db "Lab5\Output.txt", 0 
check_format db '.txt$'

msg_error_file_not_found db "File not found!!!$"  
msg_error_path_not_found db "Path not found!!!$"  

msg_string_con db "String contain word$"
msg_bad_cmd_params db "Bad cmd params$"
msg_start_program db "Program is start....$"
msg_end db "Program successfully compleate.$"

input_file_handle dw ?
outupt_file_handle dw ?

is_contain_word db 0
EOF db 0

bufer_char db ?
bad_word db 50 DUP('$') 

PUTC MACRO char ; macros dlya vivoda odnogo simvola na ekran
    PUSH ax
    mov ah, 0Eh
    mov al, char
    int 10h
    POP ax    
ENDM

PUTS MACRO string ; vivod stroki 
    PUSH ax
    PUSH dx 
    
    mov ah, 9h
    lea dx, string
    int 21h 
    
    PUTC 13
    PUTC 10
    
    POP dx
    POP ax
ENDM   

fseek MACRO pos  ; ustanovka posizii v faile
    PUSH ax
    PUSH dx 
    PUSH cx
    
    mov ah, 42h
    mov al, 1
    mov dx, pos
    mov cx, 0
    int 21h
    
    POP cx
    POP dx
    POP ax    
ENDM

.code
MAIN:
    mov ax, @data
    mov es, ax
    
    call parce_cmd_line
    
    lea si, name_output_file
    PUSH si
    call proc_create_file
    
    PUTS msg_start_program
    
    lea dx, name_input_file
    PUSH dx
    PUSH 00h 
    call proc_open_file
    mov [input_file_handle], ax 
    
    lea dx, name_output_file
    PUSH dx
    PUSH 01h
    call proc_open_file
    mov [outupt_file_handle], ax
    
    call proc_check_file_bad_word
     
    PUSH [input_file_handle]
    call proc_close_file 
    
    PUSH [outupt_file_handle]
    call proc_close_file
    
    PUTS msg_end
    end_program:
    mov ah, 4Ch
    int 21h
   
    parce_cmd_line PROC NEAR
        xor cx, cx 
        mov cl, DS:[80h] ; chtenie dlini komandnoi stroki
        lea di, name_input_file
        mov si, 82h 
        dec cl

        first_param:  ; izvlechenie imeni faila pereborom simvolov
        MOVSB  ; iz SI v DI
        dec cl
        cmp [si], ' '
        je check_first_param
        jmp first_param

        check_first_param:  ; proverka rasshireniia
            PUSH cx
            mov cx, 4  ; schetchik dlya proverki .txt
            lea bx, check_format
            add bx, 3
        check_char_first_param: ; sravnenie bx s di(simvolom imeni)
            dec di
            mov al, [bx]
            cmp [di], al
            jne bad_params
            dec bx
        loop check_char_first_param
        POP cx

        inc si
        dec cl
        lea di, bad_word
        second_param:
            REP MOVSB   ;kopirovanie bad_word v bufer
            jmp end_proc_parce_cmd_line

        bad_params:
            PUTS msg_bad_cmd_params
            jmp end_program
        
        end_proc_parce_cmd_line:
        mov ax, @data
        mov ds,ax    
        ret    
    parce_cmd_line ENDP

    proc_create_file PROC NEAR    ; sozdanie novogo faila
        PUSH bx
        PUSH bp
        mov bp, sp
        param_proc_create_file_name equ bp + 6   ; opredelit simvolnoe imya, kotoroe budet sootvetstvovat adryesu v stekye
        
        mov ah, 3Ch   ;  sozdaniya fayla v registre AH
        mov cx, 0     ; Ustanovka atributov fayla (0)
        mov dx, [param_proc_create_file_name]
        int 21h

        PUSH ax   ; Sokhranenie identifikatora fayla
        call proc_close_file
        
        POP bp
        POP bx
        ret 2  ;ochistka steka na 2 bayta 
    proc_create_file ENDP
    
    proc_open_file PROC NEAR
        PUSH bp
        mov bp, sp
        proc_open_file_name equ bp + 6
        proc_open_file_accses equ bp + 4
        
        mov ah, 3Dh  ; otkritie faila
        mov al, [proc_open_file_accses]
        mov dx, [proc_open_file_name]
        xor cx, cx
        int 21h
        
        jc error_open_file
        jmp end_proc_open_file 

        error_open_file:
            cmp ax, 02h ; Sravnenie vozvrashchennogo koda oshibki s 02h (fayl ne nayden)
            je file_not_found 
            cmp ax, 03h        ; Sravnenie vozvrashchennogo koda oshibki s 03h (put' ne nayden)
            je path_not_found
            jmp end_proc_open_file

        file_not_found:
            PUTS msg_error_file_not_found
            jmp end_proc_open_file
        ; ???? ? ????? ?? ??????
        path_not_found:
            PUTS msg_error_path_not_found
            jmp end_proc_open_file
        
        end_proc_open_file:
            POP bp
            ret 4    
    proc_open_file ENDP  

    proc_close_file PROC NEAR
        PUSH ax
        PUSH dx
        PUSH bp
        mov bp, sp
        proc_close_file_fileID equ bp + 8
        
        mov ah, 3Eh  ;zakritie faila
        mov bx, [proc_close_file_fileID]
        int 21h       
        
        POP bp
        POP dx
        POP ax
        ret 2    
    proc_close_file ENDP

    proc_check_string_file PROC NEAR
        PUSH bp
        mov bp, sp

        mov bx, [input_file_handle]
        lea si, bad_word
        mov cx, 0 
        check_next_char:
            PUSH bx
            call fgetc
            inc cx
            cmp al, ' '  
            je check_next_char
            cmp al, 0Dh ; Sravnenie s kodom vozvrata karetki
            je end_proc_check_string
            cmp al, 00h  ; Sravnenie s nulevym simvolom (konets stroki)
            je end_proc_check_string
            compare_words:
                cmp al, [si]
                jne con_check_next_char        
                inc si
                PUSH bx
                call fgetc 
                inc cx
                cmp [si], '$'
                je check_is_word
                jmp compare_words              
        con_check_next_char:
        lea si, bad_word
        skip_not_bad_word:
            PUSH bx
            call fgetc
            inc cx
            cmp al, ' '
            je check_next_char
            cmp al, 0Dh
            je end_proc_check_string
            cmp al, 00h
            je end_proc_check_string      
            jmp skip_not_bad_word

        check_is_word:
            cmp al, ' '
            je word_is_found
            cmp al, 0Dh
            je word_is_found
            cmp al, 00h
            je word_is_found
            jmp check_next_char 
        
        word_is_found:
            PUTS msg_string_con 
            mov is_contain_word, 1 ; Ustanovka flaga nalichiya slova
            jmp end_proc_check_string
            
        end_proc_check_string:
        POP bp
        ret        
    proc_check_string_file ENDP
    
    fputs PROC NEAR
        PUSH bp
        mov bp, sp
        input_next_char:
            PUSH [input_file_handle]
            call fgetc
            mov [input_file_handle], bx
            cmp al, 00h
            je end_of_file
            PUSH [outupt_file_handle]
            call fputc
            mov [outupt_file_handle], bx 
            cmp al, 0Ah
            je end_fputs
        jmp input_next_char
        
        end_of_file:
        mov EOF, 1
        jmp end_fputs
        
        end_fputs:
        POP bp
        ret
    fputs ENDP
    
    proc_check_file_bad_word PROC NEAR
        PUSH bp
        mov bp, sp
        check_next_string: 
            call proc_check_string_file
            cmp [is_contain_word], 1
            je skip_string 
            neg cx
            fseek cx
            call fputs
            cmp [EOF], 1 ;proverka na konec faila
            jne check_next_string
            jmp end_proc_check_file_bad_word

        skip_string:
            PUSH bx
            call fgetc
            cmp al, 0Ah
            je con_check_next_string
            cmp al, 00h
            je end_proc_check_file_bad_word
        jmp skip_string
        con_check_next_string:
            mov is_contain_word, 0
            mov [input_file_handle], bx
            jmp check_next_string
             
        end_proc_check_file_bad_word:
        POP bp
        ret     
    proc_check_file_bad_word ENDP    
    
    fgetc PROC NEAR 
        PUSH cx
        PUSH bp
        mov bp, sp
        fgets_fileID equ bp + 6 ; Id 
        mov ah, 3Fh
        mov bx, [fgets_fileID]
        mov cx, 01h 
        lea dx, bufer_char
        int 21h
        mov al, [bufer_char] 
        jmp end_fgetc
        
    end_fgetc:       
        POP bp 
        POP cx
        ret 2    
    fgetc ENDP 

    fputc PROC NEAR
        PUSH ax
        PUSH cx
        PUSH dx
        PUSH bp
        mov bp, sp
        fputc_fileID equ bp + 10  ;
        
        mov ah, 40h
        mov bx, [fputc_fileID]
        mov cx, 1
        lea dx, bufer_char
        int 21h
        
        POP bp
        POP dx
        POP cx
        POP ax
        ret 2
    fputc ENDP
    
end MAIN
