;Archivo con toadas las funciones auxiliares de asm para los comandos de la terminal


GLOBAL getRAX:
GLOBAL getRBX:
GLOBAL getRCX:
GLOBAL getRDX:
GLOBAL getRBP:
GLOBAL getRSP:
GLOBAL getRSI:
GLOBAL getRDI:
GLOBAL getR8:
GLOBAL getR9:
GLOBAL getR10:
GLOBAL getR11:
GLOBAL getR12:
GLOBAL getR13:
GLOBAL getR14:
GLOBAL getR15:
GLOBAL  invalidOpcodeTester:
GLOBAL getStatusRegA:
GLOBAL getSeconds:
GLOBAL getMinutes:
GLOBAL getHours:


SECTION .text:

getRAX:
    mov rax, rax
    ret
getRBX:
    mov rax, rbx
    ret
getRCX:
    mov rax, rcx
    ret
getRDX:
    mov rax, rdx
    ret
getRBP:
    mov rax, rbp
    ret
getRSP:
    mov rax, rsp
    ret
getRSI:
    mov rax, rsi
    ret
getRDI:
    mov rax, rdi
    ret
getR8:
    mov rax, r8
    ret
getR9:
    mov rax, r9
    ret
getR10:
    mov rax, r10
    ret
getR11:
    mov rax, r11
    ret
getR12:
    mov rax, r12
    ret
getR13:
    mov rax, r13
    ret
getR14:
    mov rax, r14
    ret
getR15:
    mov rax, r15
    ret
invalidOpcodeTester:
    mov cr6, rax
    ret



getStatusRegA:
	push rbp
	mov rbp, rsp

	mov al, 0Ah
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret


getSeconds:
	push rbp
	mov rbp, rsp

	mov al, 00h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getMinutes:
	push rbp
	mov rbp, rsp

	mov al, 02h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getHours:
	push rbp
	mov rbp, rsp

	mov al, 04h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret
