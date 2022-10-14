GLOBAL fetchScanCodeByte
GLOBAL setScanCodeSetToOne

section .text

;TODO implement this function
setScanCodeSetToOne:
	nop
	ret

fetchScanCodeByte:
	mov rax, 0
	in al, 60h
	ret
