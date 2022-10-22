GLOBAL sys_read_asm:
GLOBAL sys_write_asm:

SECTION .text

sys_read_asm:
    push rbp
    mov rbp, rsp

    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,0
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_write_asm:
    push rbp
    mov rbp, rsp

    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,1
    int 80h

    mov rsp,rbp
    pop rbp
    ret
    
