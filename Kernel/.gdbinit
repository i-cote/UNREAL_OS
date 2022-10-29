target remote :1234
add-symbol-file kernel.elf 0x100000

set print pretty on
set disassembly-flavor intel
