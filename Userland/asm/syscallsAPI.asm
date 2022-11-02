GLOBAL sys_read_asm:
GLOBAL sys_write_asm:
GLOBAL sys_print_asm:
GLOBAL sys_ticker_asm:
GLOBAL sys_memcpy_asm: 
GLOBAL sys_inb_asm;
GLOBAL sys_out_asm;

SECTION .text

sys_read_asm: ; int sys_read(int fd, char *buf, int count)
    push rbp
    mov rbp, rsp

    mov r8,rcx  ;Passing arguments from C to syscall parameters
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,0
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_write_asm: ; int sys_write(int fd, char *buf, int count)
    push rbp
    mov rbp, rsp

    mov r8,rcx ;Passing arguments from C to syscall parameters
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,1
    int 80h

    mov rsp,rbp
    pop rbp
    ret
    
sys_print_asm: ; int sys_print(int fd, int length, int coor)
    push rbp
    mov rbp, rsp

    mov r8,rcx ;Passing arguments from C to syscall parameters
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,4
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_ticker_asm: ; int sys_ticker(int fd, int length)
    push rbp
    mov rbp, rsp

    mov rdx,rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, 5
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_memcpy_asm: ; int sys_memcpy(char *buf, int count)
    push rbp
    mov rbp, rsp

    mov rdx, rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, 6
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_out_asm: ; int sys_out(int port, int value)
    push rbp
    mov rbp, rsp

    mov rdx, rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, 3

    mov rsp, rbp
    pop rbp
    ret

sys_inb_asm: ; int sys_inb(int port)
    push rbp
    mov rbp, rsp

    mov rsi, rdi ;Passing arguments from C to syscall parameters
    mov rdi, 2
    int 80h

    mov rsp,rbp
    pop rbp
    ret
