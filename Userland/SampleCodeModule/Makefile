include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
MODULEELF=0000-sampleCodeModule.elf
SOURCES=$(wildcard [^_]*.c)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -T sampleCodeModuleELF.ld _loader.c $(SOURCES) -o ../$(MODULEELF)

clean:
	rm -rf *.o

.PHONY: all clean print
