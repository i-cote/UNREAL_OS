GLOBAL sys_read_asm
GLOBAL sys_write_asm
GLOBAL sys_print_asm
GLOBAL sys_ticker_asm
GLOBAL sys_memcpy_asm
GLOBAL sys_inb_asm
GLOBAL sys_out_asm
GLOBAL sys_accessRTC_asm

READ equ 0
WRITE equ 1
BEEP_INB equ 2
BEEP_OUTB equ 3
PRINT equ 4
MEMCPY equ 6
TICKER equ 5
RTC equ 7

SECTION .text

sys_read_asm: ; int sys_read(int fd, char *buf, int count)
    push rbp
    mov rbp, rsp

    mov r8,rcx  ;Passing arguments from C to syscall parameters
    mov rcx,rdx
    mov rdx,rsi
    mov rsi,rdi
    mov rdi,READ
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
    mov rdi,WRITE
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
    mov rdi,PRINT
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_ticker_asm: ; int sys_ticker(int fd, int length)
    push rbp
    mov rbp, rsp

    mov rdx,rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, TICKER
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_memcpy_asm: ; int sys_memcpy(char *buf, int count)
    push rbp
    mov rbp, rsp

    mov rdx, rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, MEMCPY
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_out_asm: ; int sys_out(int port, int value)
    push rbp
    mov rbp, rsp

    mov rdx, rsi ;Passing arguments from C to syscall parameters
    mov rsi, rdi
    mov rdi, BEEP_OUTB

    mov rsp, rbp
    pop rbp
    ret

sys_inb_asm: ; int sys_inb(int port)
    push rbp
    mov rbp, rsp

    mov rsi, rdi ;Passing arguments from C to syscall parameters
    mov rdi, BEEP_INB
    int 80h

    mov rsp,rbp
    pop rbp
    ret

sys_accessRTC_asm: ; int sys_accessRTC(int fd)
    push rbp
    mov rbp, rsp

    mov rsi, rdi ;Passing arguments from C to syscall parameters
    mov rdi, RTC
    int 80h

    mov rsp,rbp
    pop rbp
    ret
