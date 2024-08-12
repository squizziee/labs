    .model small
    .code
    org 100h
    ;mov  ax,@data
    ;mov  ds,ax
    
    mov ax,@data
    mov es,ax
    xor ch,ch
    mov cl,ds:[80h]
    mov es:cmd_length,cx      ;get length of cmd    
    cmp max_cmd_size,cl    ;check on limit of cmd
    jb exit      
    mov bh,cl
    dec bh      
    mov si,81h
    lea di,cmd_line
    rep movsb    
    mov ds,ax
    call set_path_and_N
    cmp N,0
    jle input_error       
    call create_temp_file
    call close_temp_file
    mov di,0; N counter
; Outer loop, works fine already.
; Takes chunks of 256 bytes 
; and writes them to buffer
    call open_file
    ;call open_temp_file
read_data:
    ;call open_file
    call move_source_cursor
    mov cx,256
    lea dx,buffer
    mov ah,3Fh
    int 21h
    mov bytes_read,ax
    ;jc close_file
    ;call close_file
    ;call open_temp_file
    call process_chunk
    ;call close_temp_file
    inc chunks_processed
    ; Output to the emulator
    ; screen
    ;mov cx,ax
    cmp bytes_read,256
    jl after_transform
    ;jl exit
    ;mov ah,40h
    ;xchg bx,di
    ;int 21h
    ;xchg di,bx
    ;jc close_file
    jmp read_data

after_transform:
    call close_temp_file
    call close_file
    ;call copy_temp_to_source
    jmp exit

proc set_path_and_N
    mov si,1
    mov di,0
set_path_loop:
    cmp [cmd_line+si],' '
    je read_N
    cmp [cmd_line+si],9
    je read_N
    mov ah,[cmd_line+si]
    mov [file_name+di],ah
    inc si
    inc di
    inc file_name_length
    jmp set_path_loop
read_N:
    inc si
read_N_loop:
    cmp [cmd_line+si],0
    je set_N
    mov ah,0
    mov al,[cmd_line+si]
    push ax
    inc si
    inc N_counter
    jmp read_N_loop
set_N:
    mov bx,1
    mov cx,0
set_N_loop:
    cmp N_counter,0
    je terminate_set_path
    pop ax
    sub ax,'0'
    mul bx
    add cx,ax
    mov ax,10
    mul bx
    mov bx,ax
    dec N_counter
    jmp set_N_loop 
terminate_set_path:
    mov N,cx
    ret
endp

proc process_chunk
    call open_temp_file
    mov si,0
    call move_temp_cursor_to_end
process_chunk_loop:
    cmp si,bytes_read
    je handle_buff_end
    ;je terminate_process_chunk   
    mov ah,[buffer+si]
    cmp ah,' '
    mov divider,' '
    je handle_word_end
    cmp ah,9
    mov divider,9
    je handle_word_end
    cmp ah,0Dh
    mov divider,0Dh
    je handle_word_end
    push si
    mov si,current_word_length
    mov [current_word+si],ah
    pop si
    inc current_word_length
    inc si
    jmp process_chunk_loop
handle_word_end:
    inc di
    inc si
    cmp di,N
    je handle_N_word
    call write_word_to_temp_file
    call clear_current_word
    ;mov [current_word+0],' '
    mov dl,divider
    mov [current_word+0],dl
    mov current_word_length,1
    call write_word_to_temp_file
    call clear_current_word
    mov current_word_length,0
    jmp process_chunk_loop
handle_N_word:
    mov di,0
    call clear_current_word
    jmp process_chunk_loop
handle_buff_end:
    cmp bytes_read,256
    jl handle_word_at_file_end
    ;call close_file
    ret
handle_word_at_file_end:
    inc di
    mov ax,bytes_read
    mov source_last_block_size,ax
    cmp di,N
    je terminate_process_chunk
    call write_word_to_temp_file
    call clear_current_word
    mov current_word_length,0    
    jmp terminate_process_chunk
terminate_process_chunk:
    call close_temp_file
    ret   
endp    
    
proc open_file
    lea dx,file_name
    mov ah,3Dh
    mov al,00h
    int 21h
    jc input_error
    mov source_handler,ax
    jc exit
    ret
endp

proc open_file_for_write
    lea dx,file_name
    mov ah,3Dh
    mov al,1
    int 21h
    mov source_handler,ax
    jc exit
    ret
endp

proc open_temp_file
    lea dx,temp_file_name
    mov ah,3Dh
    mov al,01h
    int 21h
    mov temp_handler,ax
    jc exit
    ret
endp

proc open_temp_file_for_read
    lea dx,temp_file_name
    mov ah,3Dh
    mov al,0
    int 21h
    mov temp_handler,ax
    jc exit
    ret
endp

proc delete_temp_file
    mov ah,41h
    lea dx,temp_file_name
    int 21h
    ret
endp
 
proc create_temp_file
    lea dx,temp_file_name
    mov cx,0
    mov ah,3Ch
    int 21h
    mov temp_handler,ax
    ret    
endp
 
proc write_word_to_temp_file
    mov bx,temp_handler
    mov ah,40h
    mov cx,current_word_length
    lea dx,current_word
    int 21h
    ret    
endp 
 
proc clear_current_word
    push si
    mov si,0
clear_current_word_loop:
    cmp si,current_word_length
    je terminate_clear_current_word
    mov ah,0
    mov [current_word+si],0
    inc si
    jmp clear_current_word_loop
terminate_clear_current_word:
    mov current_word_length,0
    pop si
    ret    
endp

proc close_file
    mov ah,3Eh
    mov bx,source_handler
    int 21h
    ret
endp
  
proc close_temp_file
    mov ah,3Eh
    mov bx,temp_handler
    int 21h
    ret
endp  
  
proc move_temp_cursor_to_end
    mov ah,42h
    mov al,2
    mov bx,temp_handler
    mov cx,0
    mov dx,0
    int 21h
    ret        
endp

proc move_temp_cursor
    mov ax,255
    mul chunks_processed
    mov cx,ax
    xchg cx,dx
    mov ah,42h
    mov al,0
    mov bx,temp_handler
    int 21h
    ret          
endp

proc move_source_cursor
    mov ax,255
    mul chunks_processed
    mov cx,ax
    xchg cx,dx
    mov ah,42h
    mov al,0
    mov bx,source_handler
    int 21h
    ret        
endp
 
proc move_source_cursor_to_end_margin
    mov ax,255
    dec chunks_processed
    mul chunks_processed
    inc chunks_processed
    add ax,source_last_block_size
    mov cx,ax
    xchg cx,dx
    mov ah,42h
    mov al,0
    mov bx,source_handler
    int 21h
    ret        
endp 
 
proc move_source_cursor_to_end
    mov ah,42h
    mov al,2
    mov bx,temp_handler
    mov cx,0
    mov dx,0
    int 21h
    ret             
endp
    
proc copy_temp_to_source
    mov chunks_processed,0
    mov bytes_read,0
    ;call open_file
copy_loop:
    call open_temp_file_for_read
    call move_temp_cursor
    ;call move_source_cursor
    mov cx,256
    mov bx,temp_handler
    lea dx,buffer
    mov ah,3Fh
    int 21h   
    mov bytes_read,ax
    call close_temp_file
      
      
    call open_file_for_write
    call move_source_cursor
    mov bx,source_handler
    mov ah,40h
    mov cx,bytes_read
    lea dx,buffer
    int 21h   
    call close_file
    
    inc chunks_processed
    cmp bytes_read,256
    jl after_copy
    jmp copy_loop
after_copy:
    mov ax,source_last_block_size
    sub ax,bytes_read
    mov end_margin,ax
    call clear_buff
    call open_file_for_write
    ;call move_source_cursor
    call move_source_cursor_to_end_margin
    mov bx,source_handler
    mov ah,40h
    mov cx,end_margin
    lea dx,buffer
    int 21h   
    call close_file
    ret
endp

proc clear_buff
    mov di,0
clear_buff_loop:
    cmp di,255
    je terminate_clear_buff
    mov [buffer+di],0
    inc di
    jmp clear_buff_loop
terminate_clear_buff:
    ret        
endp

input_error:
    mov ah,09h
    lea dx,error_msg
    int 21h
    jmp exit
exit:
    hlt
    .data   
    buffer db 256 dup(0)
    divider db 0
    current_word db 50 dup(0)
    current_word_length dw 0
    ;file_name db 'c:\test_short.txt',0
    file_name db 100 dup(0)
    file_name_length dw 0
    temp_file_name db 'c:\tmp.txt',0
    some_file_name db 'c:\dumbass.txt',0
    temp_handler dw 0
    source_handler dw 0
    N dw 1
    N_counter dw 0
    bytes_read dw 0
    source_last_block_size dw 0
    end_margin dw 0
    chunks_processed dw 0
    cmd_length dw 0
    cmd_line db 127 dup(0), '$'
    max_cmd_size db 127
    error_msg db 'Wrong input$'