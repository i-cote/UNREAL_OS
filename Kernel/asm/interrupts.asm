GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL _irq01Handler
GLOBAL _irq00Handler
GLOBAL _irq60Handler
GLOBAL _exception0Handler
GLOBAL _exception6Handler

EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn
%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro

_irq00Handler:
	irqHandlerMaster 0 

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

_irq60Handler:
	pushState
	mov rbp, rsp

	mov r8,rcx
	mov rcx,rdx
	mov rdx,rsi
	mov rsi,rdi
	mov rdi, 60h
	call irqDispatcher

	mov rsp,rbp
	popState
	iretq

_exception0Handler:
	exceptionHandler 0

_exception6Handler:
	exceptionHandler 6

SECTION .bss
	aux resq 1
