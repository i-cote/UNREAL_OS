target remote :1234
add-symbol-file 0000-sampleCodeModule.elf 0x400000

set print pretty on
set disassembly-flavor intel
