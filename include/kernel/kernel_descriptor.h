#ifndef KERNEL_DESCRIPTOR_H
#define KERNEL_DESCRIPTOR_H

#include "cpu/cpu_segment_selector.h"

void init_gdt();
uint8_t kernel_alloc_segment_selector(struct cpu_segment_selector* sel, uint16_t* start_pos);
uint8_t kernel_alloc_program_pack(struct cpu_segment_selector_pack* pack);
void init_kernel_desriptors(struct cpu_segment_selector_pack* pack);

#endif // KERNEL_DESCRIPTOR_H