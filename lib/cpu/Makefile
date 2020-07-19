INC = $(addprefix ../, $(PRE_INC))
BACK_SLASHING = $(addprefix ../, $(PRE_BACK))
BP = $(addprefix ../, $(PRE_BP))
DEF_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I$(INC)

all: $(BP)/cpu_info.o $(BP)/cpu_info_asm.o $(BP)/cpu_descriptor.o
	ar rcs $(BP)/cpu.a $(BP)/cpu_info_asm.o $(BP)/cpu_info.o $(BP)/cpu_descriptor.o

$(BP)/cpu_info.o: cpu_info.c
	gcc -c cpu_info.c $(DEF_FLAGS)
	mv cpu_info.o $(BP)/cpu_info.o
	
$(BP)/cpu_info_asm.o: cpu_info_asm.asm
	nasm -f elf cpu_info_asm.asm
	mv cpu_info_asm.o $(BP)/cpu_info_asm.o

$(BP)/cpu_descriptor.o: cpu_descriptor.c
	gcc -c cpu_descriptor.c $(DEF_FLAGS)
	mv cpu_descriptor.o $(BP)/cpu_descriptor.o

clear:
	rm -rf *.o *.a *.bin