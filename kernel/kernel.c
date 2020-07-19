#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cpu/cpu_descriptor.h"
#include "basic_terminal/basic_terminal.h"
 
extern void register_inter_init();
extern void _i0();
extern void call_int(uint32_t);

 
void kernel_main(void) 
{
	terminal_initialize();
	terminal_writestring("Hello Woffrld!\n");

	struct cpu_descriptor d;
	cpu_descriptor_write_dpl(&d, 0b11);
	terminal_writestring("  ");
	termial_write_hex(d.r1);
	terminal_writestring("  ");
	termial_write_hex(d.r2);
}
