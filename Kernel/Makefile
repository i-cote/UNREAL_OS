GCC=gcc
LD=ld
AR=ar
ASM=nasm

GCCFLAGS=-g -m64 -fno-exceptions -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc -mno-red-zone -Wall -ffreestanding -nostdlib -fno-common -std=c99
ARFLAGS=rvs
ASMFLAGS=-felf64
LDFLAGS=--warn-common -z max-page-size=0x1000

KERNEL=kernel.bin
KERNELELF=kernel.elf
SOURCES=$(shell find . -type f -name "*.c")
FONTS=$(shell find . -type f -name "*.psfu")
FONTS_ELF=$(FONTS:.psfu=.o)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=kernel_entry/loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(FONTS_ELF)
	$(LD) $(LDFLAGS) -T linker/kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(FONTS_ELF)
	$(LD) $(LDFLAGS) -T linker/kernelELF.ld -o $(KERNELELF) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(FONTS_ELF)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

%.o: %.psfu
	objcopy -O elf64-x86-64 -B i386 -I binary $< $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	find . -type f -name "*.o" | xargs -I _ rm _
	find . -type f -name "*.elf" | xargs -I _ rm _
	find . -type f -name "*.bin" | xargs -I _ rm _

.PHONY: all clean
