#include <stdint.h>

#include "kernel/kernel_descriptor.h"
#include "cpu/cpu_descriptor.h"
#include "cpu/cpu_segment_selector.h"

void init_gdt(){
	cpu_descriptor* gtd = (cpu_descriptor*)get_GDT();
	for(int i = 0; i < GDT_MAX; ++i){
		gtd[i].r1 = 0;
		gtd[i].r2 = 0;
	}
}

uint8_t kernel_alloc_segment_selector(struct cpu_segment_selector* sel, uint16_t* start_pos){
	cpu_descriptor* gtd = (cpu_descriptor*)get_GDT();
	for(; *start_pos < GDT_MAX; ++(*start_pos)){
		if(gtd[*start_pos].r1 == 0 && gtd[*start_pos].r2 == 0){
			cpu_segment_selector_set_id(sel, *start_pos);
			++(*start_pos);
			return 1;
		}
	}
	return 0;
}

uint8_t kernel_alloc_program_pack(struct cpu_segment_selector_pack* pack){
	cpu_descriptor* gtd = (cpu_descriptor*)get_GDT();
	uint8_t id = 0;
	for(int i = 1; i < GDT_MAX; ++i){
		if(gtd[i].r1 == 0 && gtd[i].r2 == 0){
			cpu_segment_selector_set_id(&pack->sels[id], i);
			++id;
			if(id == 3){
				return 1;
			}
		}
	}
	return 0;
}

void init_kernel_code_desc(cpu_descriptor* d){
	cpu_descriptor_write_base(d, 0);
	cpu_descriptor_write_limit(d, 0xFFFFFFFF);
	cpu_descriptor_write_s_type(d, CPU_DESCRIPTOR_S_DATA);
	cpu_descriptor_write_type(d, CPU_D_TYPE_EXE_READ);
	cpu_descriptor_write_dpl(d, 3);
	cpu_descriptor_write_p_flag(d, CPU_DESCRIPTOR_P_PRESENT);
	cpu_descriptor_write_d_flag(d, CPU_DESCRIPTOR_D_32);
	cpu_descriptor_write_g_flag(d, CPU_DESCRIPTOR_G_4k_4g);
}

void init_kernel_stack_desc(cpu_descriptor* d){
	cpu_descriptor_write_base(d, 0xFFFFFFFF);
	cpu_descriptor_write_limit(d, 0x0);
	cpu_descriptor_write_s_type(d, CPU_DESCRIPTOR_S_DATA);
	cpu_descriptor_write_type(d, CPU_D_TYPE_READ_WRITE_EXPDOWN);
	cpu_descriptor_write_dpl(d, 3);
	cpu_descriptor_write_p_flag(d, CPU_DESCRIPTOR_P_PRESENT);
	cpu_descriptor_write_d_flag(d, CPU_DESCRIPTOR_D_32);
	cpu_descriptor_write_g_flag(d, CPU_DESCRIPTOR_G_4k_4g);
}

void init_kernel_data_desc(cpu_descriptor* d){
	cpu_descriptor_write_base(d, 0);
	cpu_descriptor_write_limit(d, 0xFFFFFFFF);
	cpu_descriptor_write_s_type(d, CPU_DESCRIPTOR_S_DATA);
	cpu_descriptor_write_type(d, CPU_D_TYPE_EXE_READ);
	cpu_descriptor_write_dpl(d, 3);
	cpu_descriptor_write_p_flag(d, CPU_DESCRIPTOR_P_PRESENT);
	cpu_descriptor_write_d_flag(d, CPU_DESCRIPTOR_D_32);
	cpu_descriptor_write_g_flag(d, CPU_DESCRIPTOR_G_4k_4g);
}

void init_kernel_desriptors(struct cpu_segment_selector_pack* pack){
	cpu_descriptor cpu_descriptor_code, cpu_descriptor_stack, cpu_descriptor_data;
	init_kernel_code_desc(&cpu_descriptor_code);
	init_kernel_stack_desc(&cpu_descriptor_stack);
	init_kernel_data_desc(&cpu_descriptor_data);

	load_descriptor(&cpu_descriptor_code, &pack->sels[CPU_SEL_CODE]);
	load_descriptor(&cpu_descriptor_stack, &pack->sels[CPU_SEL_CODE]);
	load_descriptor(&cpu_descriptor_data, &pack->sels[CPU_SEL_DATA]);
}
