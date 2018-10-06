# Tools definition
CC = gcc
LD = gcc
ASM = nasm

# Flags definition
LD_FLAGS = -Wl,-T,memory.lds -m32 -nostdlib -fno-asynchronous-unwind-tables -Wl,--gc-sections -s
CC_FLAGS = -m32 -O2 -nostdlib -fno-asynchronous-unwind-tables -c -Wall -ffunction-sections -fdata-sections -s
ASM_FLAGS = -f elf32

# Include dirs definitions
CC_INCLUDE = -Ikernel/include

# Source files definitions
C_FILES = $(shell find kernel/ -type f -name '*.c')
ASM_FILES = $(shell find kernel/ -type f -name '*.asm')

# Object files definitions
C_OBJECTS = $(patsubst %.c, %.oc, $(C_FILES))
ASM_OBJECTS = $(patsubst %.asm, %.oa, $(ASM_FILES))

# Rules
all: kernel.o

kernel.o: $(C_OBJECTS) $(ASM_OBJECTS)
	 $(LD) -o $@ $^ $(LD_FLAGS)
	 cp $@ $@.bak
	 strip -s $@
	 objcopy -O binary $@ $@
	 
%.oc: %.c
	$(CC) $(CC_FLAGS) $(CC_INCLUDE) $^ -o $@
	
%.oa: %.asm
	$(ASM) $(ASM_FLAGS) $^ -o $@
	
clean:
	rm -f kernel.o $(C_OBJECTS) $(ASM_OBJECTS)
	rm -rf bin