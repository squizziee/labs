.model small
.stack 100h
.data
    cmd_length db ?                                      
    cmd_text db 129 dup(0)  
    folder_path db 129 dup(0)     
    dta_block db 2ch dup(0)                 
    buffer db 52 dup(0)   
    exe_path db 142 dup(0)
    
    error_bad_args db "Wrong number of CMD parameters", 0Ah, 0Dh, '$' 
    error_bad_init db "Bad Init", 0Ah, 0Dh, '$'    
    error_run_prog db "Error inside running program", 0Ah, 0Dh, '$' 
    error_folder db "Wrong folder path", 0Ah, 0Dh, '$' 
    empty_line db 0Ah, 0Dh,"Program running: ", 0Ah, 0Dh,'$'
    delim db 0Ah, 0Dh, '$'
    
    epb_struct  dw 0                       
                dw offset commandline, 0          
                dw 005Ch, 0, 006Ch, 0       
    commandline db 125                           
                db " /?"                             
    commandline_text db 122 dup(?)                   
    epb_length dw $ - epb_struct          
    suffix db "*.exe", 0                  
    data_size = $ - cmd_length            
    
.code                            
is_empty macro str, is_0
    push si
    lea si, str
    call strlen
    pop si
    
    cmp ax, 0
    je is_0
endm

puts macro str
    push ax
    push dx
    lea dx, str
    mov ah, 9
    int 21h
    pop dx
    pop ax    
endm

print_error_code macro
    add al, '0'
    mov dl, al
    mov ah, 06h
    int 21h
endm
 
start:
    mov ah, 4Ah                           
    mov bx, ((code_size/16)+1)+((data_size/16)+1)+32 
    int 21h    
    jnc init                              
    puts error_run_prog                      
    print_error_code                           
    mov ax, 1                             
    jmp end_start                           
init:
    mov ax, @data                         
    mov es, ax                            
    xor ch, ch                            
    mov cl, ds:[80h]                     
    mov cmd_length, cl                    
    mov si, 81h                           
    lea di, cmd_text                      
    rep movsb                               
    mov ds, ax                            
    call parse_cmd                            
    test ax, ax                           
    jne end_start                           
    mov ah, 3Bh                           
    lea dx, folder_path
    int 21h  
    jc bad_folder_path                       
    call find_first_file                                            
    push dx
    push ax   
    lea dx, empty_line
    mov ah, 09h
    int 21h   
    pop dx
    pop ax
    call run_exe                          
    test ax, ax                           
    jne end_start                             
run_file:
    call find_next_file                   
    test ax, ax                          
    jne end_start                        
    push dx
    push ax    
    lea dx, empty_line
    mov ah, 09h
    int 21h   
    pop dx
    pop ax
    call run_exe                          
    test ax, ax                           
    jne end_start                            
    jmp run_file                              
bad_folder_path:
    puts error_folder                           
end_start:
    mov ax, 4C00h                         
    int 21h 
  
parse_cmd proc
    push bx
    push cx
    push dx    
    mov cl, cmd_length                    
    xor ch, ch                             
    lea si, cmd_text                      
    lea di, buffer                            
    call to_asciiz                           
    lea di, folder_path                  
    call to_asciiz                           
    is_empty folder_path, bad_cmd_args    
    lea di, buffer                        
    call to_asciiz                      
    is_empty buffer, good_cmd_args           
bad_cmd_args:
    puts error_bad_args                     
    mov ax, 1                             
    jmp end_parse_cmd    
good_cmd_args:
    xor ax, ax                                
end_parse_cmd:
    pop dx
    pop cx
    pop bx
    ret
endp

to_asciiz proc
    push ax
    push cx
    push di
    parse_to_asciiz:
        mov al, ds:[si]
        cmp al, ' '
        je is_delimeter
        cmp al, 0Dh
        je is_delimeter
        cmp al, 09h
        je is_delimeter
        cmp al, 0Ah
        je is_delimeter
        cmp al, 00h
        je is_delimeter
        cmp al, '$'
        je is_delimeter        
        mov es:[di], al
        inc di                 
        inc si                 
    loop parse_to_asciiz
    
is_delimeter:
    mov al, 00h
    mov es:[di], al
    inc si
    pop di
    pop cx
    pop ax 
    ret
endp

strlen proc
    push bx
    push si    
    xor ax, ax
start_strlen:
    mov bl, ds:[si]
    cmp bl, 00h
    je end_strlen
    inc si
    inc ax
    jmp start_strlen
end_strlen:
    pop si
    pop bx
    ret
endp

run_exe proc
    push bx
    push dx
    mov ax, 4B00h
    lea bx, epb_struct
    lea dx, dta_block + 1Eh
    int 21h    
    jnc good_run_exe    
    puts error_run_prog
    print_error_code   
    mov ax, 1
    jmp exit_run_exe    
good_run_exe:
    xor ax, ax    
exit_run_exe:
    pop dx
    pop bx
    ret     
endp

set_dta proc
    mov ah, 1Ah
    lea dx, dta_block
    int 21h
    ret
endp
    
find_first_file proc
    call set_dta
    mov ah, 4Eh
    xor cx, cx
    lea dx, suffix
    int 21h    
    jnc good_find
    mov ax, 1
    jmp end_find
good_find:
    xor ax, ax
end_find:
    ret 
find_first_file endp

find_next_file proc
    call set_dta
    mov ah, 4Fh
    int 21h
    jnc good_next
    mov ax, 1
    jmp end_next
    
good_next:
    xor ax, ax
end_next:
    ret
endp    
    code_size = $ - start    
end start