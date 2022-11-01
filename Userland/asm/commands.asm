;Archivo con toadas las funciones auxiliares de asm para los comandos de la terminal

GLOBAL  invalidOpcodeTester:
GLOBAL getStatusRegA:
GLOBAL getSeconds:
GLOBAL getMinutes:
GLOBAL getHours:


SECTION .text:

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
