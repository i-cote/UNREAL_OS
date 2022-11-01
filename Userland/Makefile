GCC=gcc
GPP=g++
LD=ld
AR=ar
ASM=nasm

GCCFLAGS=-g -m64 -fno-exceptions -std=c99 -Wall -ffreestanding -nostdlib -fno-common -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc
ARFLAGS=rvs
ASMFLAGS=-felf64

MODULE=userModule.bin
SOURCES=$(shell find . -type f -name "[^_]*.c")
SOURCES_ASM=$(shell find . -type f -name "*.asm")
OBJECTS_ASM=$(SOURCES_ASM:%.asm=%.o)

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) -I./include -T linker/userModule.ld userland_entry/_loader.c $(OBJECTS_ASM) $(SOURCES) -o $(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T linker/userModuleELF.ld userland_entry/_loader.c $(OBJECTS_ASM) $(SOURCES) -o userModule.elf

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	find . -type f -name "*.o" | xargs -I _ rm _
	find . -type f -name "*.elf" | xargs -I _ rm _
	find . -type f -name "*.bin" | xargs -I _ rm _

.PHONY: all clean print
