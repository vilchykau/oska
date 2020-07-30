#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/kernel_descriptor.h"
#include "basic_terminal/basic_terminal.h"
#include "cpu/cpu_segment_selector.h"

void kernel_main(void)
{
	init_gdt();

	struct cpu_segment_selector_pack system_pack;
	kernel_alloc_program_pack(&system_pack);


	terminal_initialize();
	terminal_writestring("Hello Woffrld!\n");


}
