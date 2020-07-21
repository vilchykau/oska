INC = $(addprefix ../, $(PRE_INC))
BP = $(addprefix ../, $(PRE_BP))
BACK_SLASHING = $(addprefix ../, $(PRE_BACK))

subdirs = cpu basic_terminal kernel

all: make_subs

clear:
	rm -rf *.o *.a *.bin


make_subs:
	@for i in $(subdirs); do\
	(cd $$i;make all PRE_INC=$(INC) PRE_BP=$(BP) BACK_SLASHING=$(BACK_SLASHING)); done

clear_subs:
	@for i in $(subdirs); do\
	(cd $$i;make clear); done