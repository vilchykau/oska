INC = $(addprefix ../, $(PRE_INC))
BACK_SLASHING = $(addprefix ../, $(PRE_BACK))
BP = $(addprefix ../, $(PRE_BP))
DEF_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -I$(INC)

all: $(BP)/basic_terminal.o
	ar rcs $(BP)/basic_terminal.a $(BP)/basic_terminal.o
	mv basic_terminal.a $(BP)/basic_terminal.a

$(BP)/basic_terminal.o: basic_terminal.c
	gcc -c basic_terminal.c $(DEF_FLAGS)
	mv basic_terminal.o $(BP)/basic_terminal.o

clear:
	rm -rf *.o *.a *.bin