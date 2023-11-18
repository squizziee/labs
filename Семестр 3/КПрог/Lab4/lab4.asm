    .model tiny
    .code
    org 100h
start:
    call read_length
    mov length,bx
    cmp length,200
    ja error
    mov ah,9
    lea dx,new_line
    int 21h
    mov di,0
read_string:
    cmp di,length
    je after_read_string
    mov ah,08h
    int 21h
    mov [buff+di],al
    mov ah,02h
    mov dl,[buff+di]
    int 21h
    inc di
    jmp read_string
after_read_string:
    mov ah,9
    lea dx,new_line
    int 21h
    ;dec length 
    mov cx,0      ; current left bound 
    jmp outer_loop
inner_loop:
    cmp si,length
    je inner_iteration_over
    cmp [buff+si],0Dh
    je after_change_min   
    mov bh,[buff+si]    
    mov bl,[buff+di]
    cmp bh,bl
    jl change_min
after_change_min:
    inc si
    jmp inner_loop                  
outer_loop:
    mov di,cx      ; min element index    
    mov si,cx      ; i
    jmp inner_loop
inner_iteration_over:
    cmp di,length
    je set_index_registers
    mov si,cx
    mov al,[buff+si]
    mov bl,[buff+di]
    mov [buff+si],bl
    mov [buff+di],al
    inc cx         ; j
    mov di,cx
    mov si,cx
    jmp outer_loop   
change_min:
    mov di,si
    jmp after_change_min
output:
    lea dx,new_line 
    mov ah,9
    int 21h
    ;lea dx,buff
    ;mov ah,9
    ;int 21h 
    mov si,0
output_by_symbol:
    cmp si,length
    je final
    mov ah,02h
    mov dl,[buff+si]
    int 21h
    inc si 
    jmp output_by_symbol
set_index_registers:
    mov si,0
    mov di,0
    ;inc length
    jmp output_by_symbol
error:
    mov ah,9
    lea dx,new_line
    int 21h
    mov ah,9
    lea dx,error_msg
    int 21h 
    jmp final
final:
    hlt
read_length:
  mov  ax,@data
  mov  ds,ax       
  mov  ah,9
  mov  dx,offset msg
  int  21h
  mov  ah,0Ah
  mov  dx,offset string
  int  21h
  call string2number                
proc string2number
  mov  si,offset string + 1
  mov  cl,[si]                                         
  mov  ch,0
  add  si,cx
  mov  bx,0
  mov  bp,1
repeat:                           
  mov  al,[si] 
  sub  al,48
  cmp al,0
  jl error
  cmp al,9
  ja error 
  mov  ah,0 
  mul  bp 
  add  bx,ax 
  mov  ax,bp
  mov  bp,10
  mul  bp 
  mov  bp,ax   
  dec  si 
  loop repeat
  ret 
endp    
    .data   
    buff db 200 dup('$')
    new_line db 0Ah,0Dh,'$'
    length dw ?
    error_msg db 'Wrong input$'
    msg   db 'Enter length of a string: $'
    string db 4 ;MAX NUMBER OF CHARACTERS ALLOWED (3).
       db ? ;NUMBER OF CHARACTERS ENTERED BY USER.
       db 5 dup (?) ;CHARACTERS ENTERED BY USER. 