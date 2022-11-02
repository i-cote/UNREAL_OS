GLOBAL cpuVendor:
GLOBAL getStatusRegA:
GLOBAL getSeconds:
GLOBAL getMinutes:
GLOBAL getHours:

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
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


getSeconds: ;Obtains the seconds from the RTC
	push rbp
	mov rbp, rsp

	mov al, 00h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getMinutes: ;Obtains the minutes from the RTC
	push rbp
	mov rbp, rsp

	mov al, 02h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getHours: ;Obtains the hours from the RTC
	push rbp
	mov rbp, rsp

	mov al, 04h
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret
