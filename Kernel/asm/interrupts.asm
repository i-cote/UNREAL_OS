GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt

GLOBAL picMasterMask
GLOBAL picSlaveMask

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL timerRoutine
GLOBAL keyboardRoutine
GLOBAL systemCallsRoutine
GLOBAL getRegisters
GLOBAL registerBuffer

EXTERN irqDispatcher
EXTERN timer_handler
EXTERN exceptionDispatcher
EXTERN fetchKeyboardEvent
EXTERN syscallHandler

EXTERN sys_read
EXTERN sys_write
EXTERN sys_memcpy
EXTERN sys_print
EXTERN sys_ticker 

WRITE equ 1
READ equ 0
PRINT equ 4
MEMCPY equ 6
TICKER equ 5

SECTION .text

_cli:
	cli
	ret


_sti:
	sti
	ret

_hlt:
	sti
	hlt
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out 0A1h, al
    pop rbp
    retn
	
%macro pushState 0
	push rax
	pushStateSys
%endmacro 	

%macro pushStateSys 0
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

%macro popStateSys 0
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
%endmacro

%macro popState 0
	popStateSys
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
	;pisa la direccion de retorno del iretq y se dirige al puentero de
	;shell que fue previamente incializado 
	push rax
	mov rax, 0x00400000
	mov [rsp + 8], rax
	pop rax
	iretq
%endmacro

%macro endInterrupt 0
	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al
%endmacro

timerRoutine:
    pushState

	call timer_handler

	; signal pic EOI (End of Interrupt)
	endInterrupt

	popState
	iretq

keyboardRoutine:
    pushState

	call fetchKeyboardEvent

	; signal pic EOI (End of Interrupt)
	endInterrupt

	popState
	iretq

systemCallsRoutine:
	pushStateSys
	mov rbp, rsp

	mov rbx, rdi				;getting the id for syscall
	
	mov rdi, rsi				;rearranging the args for the syscall
	mov rsi, rdx
	mov rdx, rcx			
	mov rcx, r8
	mov r8, r9

	cmp rbx, WRITE
	je .write_handler
	cmp rbx, READ
	je .read_handler
	cmp rbx, PRINT
	je .print_handler
	cmp rbx, TICKER
	je .ticker_handler
	cmp rbx, MEMCPY
	je .memcpy_handler

.end_sys:
	mov rsp,rbp
	popStateSys
	iretq

.write_handler:
	call sys_write
	jmp .end_sys

.read_handler:
	call sys_read
	jmp .end_sys

.print_handler:
	call sys_print
	jmp .end_sys

.ticker_handler:
	call sys_ticker
	jmp .end_sys

.memcpy_handler:
	call sys_memcpy
	jmp .end_sys

_exception0Handler:
	exceptionHandler 0

_exception6Handler:
	exceptionHandler 6

getRegisters:
	mov QWORD[registerBuffer], rax
	mov QWORD[registerBuffer + 8], rbx
	mov QWORD[registerBuffer + 16], rcx
	mov QWORD[registerBuffer + 24], rdx
	mov QWORD[registerBuffer + 32], rbp
	mov QWORD[registerBuffer + 40], rsp
	mov QWORD[registerBuffer + 48], rsi
	mov QWORD[registerBuffer + 56], rdi
	mov QWORD[registerBuffer + 64], r8
	mov QWORD[registerBuffer + 72], r9
	mov QWORD[registerBuffer + 80], r10
	mov QWORD[registerBuffer + 88], r11
	mov QWORD[registerBuffer + 96], r12
	mov QWORD[registerBuffer + 104], r13
	mov QWORD[registerBuffer + 112], r14
	mov QWORD[registerBuffer + 120], r15
	
	mov rax, registerBuffer
	ret


SECTION .bss
	aux resq 1
	registerBuffer resb 128
