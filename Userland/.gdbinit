target remote :1234
add-symbol-file userModule.elf 0x400000

set print pretty on
set disassembly-flavor intel
