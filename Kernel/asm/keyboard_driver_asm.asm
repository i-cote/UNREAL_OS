GLOBAL fetchScanCodeByte
GLOBAL setScanCodeSetToOne

section .text

setScanCodeSetToOne: ;Sets scan code to 1
	nop
	ret

fetchScanCodeByte: ;Returns scan code byte
	mov rax, 0
	in al, 60h
	ret
