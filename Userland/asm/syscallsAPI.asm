GLOBAL sys_read_asm:
GLOBAL sys_write_asm:
GLOBAL sys_print_asm:
GLOBAL sys_ticker_asm:
GLOBAL sys_memcpy_asm: 
GLOBAL sys_inb_asm;
GLOBAL sys_out_asm;

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

sys_ticker_asm:
    push rbp
    mov rbp, rsp

    mov rdx,rsi
    mov rsi, rdi
    mov rdi, 5
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_memcpy_asm:
    push rbp
    mov rbp, rsp

    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 6
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_out_asm:
    push rbp
    mov rbp, rsp

    mov rdx, rsi
    mov rsi, rdi
    mov rdi, 3

    mov rsp, rbp
    pop rbp
    ret

sys_inb_asm:
    push rbp
    mov rbp, rsp

    mov rsi, rdi
    mov rdi, 2
    int 80h

    mov rsp,rbp
    pop rbp
    ret
