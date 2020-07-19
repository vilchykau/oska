GLOBAL_INC_DIR = include
GLOBAL_LOB_PATH = lib
BP = build

subdirs = lib build kernel

all: make_subs

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






