 
CC = gcc
LD = gcc
ASM = nasm

LD_FLAGS = -Wl,-T,link.ld -m32 -fno-pie -nostdlib -nostdinc -fno-asynchronous-unwind-tables -Wl,--gc-sections -s
CC_FLAGS = -m32 -O2 -fno-pie -fno-builtin -nostdlib -nostdinc -fno-asynchronous-unwind-tables -c -Wall -ffunction-sections -fdata-sections -s
ASM_FLAGS = -f elf32

CC_INCLUDE = -Iinclude

C_FILES = $(shell find . -type f -name '*.c')
ASM_FILES = $(shell find . -type f -name '*.nasm')

C_OBJECTS = $(patsubst %.c, %.o, $(C_FILES))
ASM_OBJECTS = $(patsubst %.nasm, %.o, $(ASM_FILES))


all: BOOT.SYS

BOOT.SYS: $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) -o $@ $(LD_FLAGS) $^ 
	# strip -s $@
	# objcopy -O binary $@ $@

%.o: %.c
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $^ -o $@
	
%.o: %.nasm
	$(ASM) $(ASM_FLAGS) $^ -o $@


clean:
	rm -f BOOT.SYS $(C_OBJECTS) $(ASM_OBJECTS)
	rm -rf bin
