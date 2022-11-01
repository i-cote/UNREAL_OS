GLOBAL sys_beepInb
GLOBAL sys_beepOutb

SECTION .text:
sys_beepInb:
    push rbp
    mov rbp, rsp
    mov rdx, rdi
    in al, dx
    leave
    ret

sys_beepOutb:
    push rbp
    mov rbp, rsp
    mov rax, rsi
    mov rdx, rdi
    out dx, al
    leave
    ret