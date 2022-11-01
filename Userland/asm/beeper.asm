GLOBAL inb
GLOBAL outb

SECTION .text:
inb:
    push rbp
    mov rbp, rsp
    mov rdx, rdi
    in al, dx
    leave
    ret

outb:
    push rbp
    mov rbp, rsp
    mov rax, rsi
    mov rdx, rdi
    out dx, al
    leave
    ret