GLOBAL_INC_DIR = include
GLOBAL_LOB_PATH = lib
BP = build

subdirs = lib build

all: make_subs $(BP)/kernel

re:
	make clear
	make all

clear:
	(cd build;make clear)

make_subs:
	@for i in $(subdirs); do\
	(cd $$i;make all PRE_INC=$(GLOBAL_INC_DIR) PRE_BP=$(BP)); done

clear_subs:
	@for i in $(subdirs); do\
	(cd $$i;make clear); done

iso: all
	@@./make_iso.sh

$(BP)/kernel: $(BP)/kernel.o $(BP)/boot.o $(BP)/register_inter_init.o
	gcc -T linker.ld -o $(BP)/kernel.bin -ffreestanding -O2 -nostdlib $(BP)/boot.o $(BP)/kernel.o $(BP)/basic_terminal.a $(BP)/cpu.a $(BP)/register_inter_init.o -lgcc -m32

$(BP)/kernel.o: kernel.c
	gcc -c -Iinclude kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
	mv kernel.o $(BP)/kernel.o

$(BP)/register_inter_init.o: register_inter_init.asm
	nasm -f elf register_inter_init.asm
	mv register_inter_init.o $(BP)/register_inter_init.o

$(BP)/boot.o: boot.s
	as boot.s -o boot.o --32
	mv boot.o $(BP)/boot.o




