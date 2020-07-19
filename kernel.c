#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cpu/cpu_info.h"
#include "cpu/cpu_segment_selector.h"
#include "basic_terminal/basic_terminal.h"
 
extern void register_inter_init();
extern void _i0();
extern void call_int(uint32_t);

 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	register_inter_init();

	terminal_initialize();
	

	//register_inter_init();
	terminal_writestring("Hello World!\n");
	terminal_writestring("Zzzzz....  .\n");

}
