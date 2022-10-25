GLOBAL sys_read_asm:
GLOBAL sys_write_asm:
GLOBAL sys_print_asm:

SECTION .text

sys_read_asm:
    push rbp
    mov rbp, rsp

    mov r8,rcx
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

    mov r8,rcx
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,1
    int 80h

    mov rsp,rbp
    pop rbp
    ret
    
sys_print_asm:
    push rbp
    mov rbp, rsp

    mov r8,rcx
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,4
    int 80h

    mov rsp,rbp
    pop rbp
    ret

