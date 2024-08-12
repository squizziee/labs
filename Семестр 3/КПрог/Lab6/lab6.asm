    .model tiny
    .code
    org 100h
    mov  ax,@data
    mov  ds,ax
    call create_temp_file
    mov di,0; N counter
; Outer loop, works fine already.
; Takes chunks of 256 bytes 
; and writes them to buffer
    call open_file
    call open_temp_file
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
    
proc open_file
    lea dx,file_name
    mov ah,3Dh
    mov al,00h
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

proc process_chunk
    ;call open_temp_file
    mov si,0
    call move_temp_cursor_to_end
process_chunk_loop:
    cmp si,bytes_read
    je handle_buff_end   
    mov ah,[buffer+si]
    cmp ah,' '
    je handle_word_end
    cmp ah,0Dh
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
    mov [current_word+0],' '
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
    cmp di,N
    je terminate_process_chunk
    call write_word_to_temp_file
    call clear_current_word
    mov current_word_length,0
    jmp terminate_process_chunk
terminate_process_chunk:
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

proc move_source_cursor_to_end
    mov ah,42h
    mov al,2
    mov bx,temp_handler
    mov cx,0
    mov dx,0
    int 21h
    ret             
endp
after_transform:
    call close_file
    call close_temp_file
    mov ah,3ch
    mov cx,0
    lea dx,temp_file_name
    int 21h
    mov source_handler,ax
    jmp exit
    call open_file
    call copy_temp_to_source
    call close_file
    jmp exit    
proc copy_temp_to_source
    mov chunks_processed,0
copy_loop:
    call open_temp_file
    call move_temp_cursor
    call move_source_cursor_to_end
    mov cx,256
    lea dx,buffer
    mov ah,3Fh
    int 21h   
    push ax
    call close_file
    call open_file
    
    pop ax
    mov cx,ax
    mov bx,source_handler
    mov ah,40h
    lea dx,buffer
    int 21h
    
    call close_file
    inc chunks_processed
    cmp ax,256
    jl after_copy
    jmp copy_loop
after_copy:
    ret
endp    
exit:
    hlt
    
    buffer db 256 dup(0)
    current_word db 50 dup(0)
    current_word_length dw 0
    file_name db 'c:\test_short.txt',0
    temp_file_name db 'c:\tmp.txt',0
    some_file_name db 'c:\dumbass.txt',0
    temp_handler dw 0
    source_handler dw 0
    N dw 5
    bytes_read dw 0
    chunks_processed dw 0