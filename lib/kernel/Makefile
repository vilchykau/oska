INC = $(addprefix ../, $(PRE_INC))
BACK_SLASHING = $(addprefix ../, $(PRE_BACK))
BP = $(addprefix ../, $(PRE_BP))
DEF_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I$(INC)

all: $(BP)/kernel_descriptor.o 
	ar rcs $(BP)/kernel_lib.a $(BP)/kernel_descriptor.o $(BP)/cpu_descriptor.o

$(BP)/kernel_descriptor.o: kernel_descriptor.c
	gcc -c kernel_descriptor.c $(DEF_FLAGS)
	mv kernel_descriptor.o $(BP)/kernel_descriptor.o

clear:
	rm -rf *.o *.a *.bin