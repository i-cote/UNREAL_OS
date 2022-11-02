;Archivo con toadas las funciones auxiliares de asm para los comandos de la terminal

GLOBAL  invalidOpcodeTester:
SECTION .text:

invalidOpcodeTester:
    mov cr6, rax
    ret
