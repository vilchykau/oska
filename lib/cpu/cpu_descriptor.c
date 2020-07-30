#include "cpu/cpu_descriptor.h"

void cpu_descriptor_write_base(cpu_descriptor* d, uint32_t addr){
    d->r2 &= 0xFFFF;
    d->r2 |= (addr & 0xFFFF) << 16;

    d->r1 &= 0xFFFF00;
    d->r1 |= (addr & 0xFF000000) | ((addr >> 16) & 0xFF);
}

void cpu_descriptor_write_limit(cpu_descriptor* d, uint32_t limit){
    d->r2 &= 0xFFFF0000;
    d->r2 |= (limit & 0xFFFF);

    d->r1 &= 0xFFF0FFFF;
    d->r1 |= (limit & 0x000F0000);
}

void cpu_descriptor_write_s_type(cpu_descriptor* d, uint32_t ss){
    d->r1 &= ~((uint32_t)1 << 12);
    d->r1 |= (ss & 0x1) << 12;
}

void cpu_descriptor_write_type(cpu_descriptor* d, uint32_t type){
    d->r1 &= 0xFFFFF0FF;
    d->r1 |= (type & 0xF) << 8;
}

void cpu_descriptor_write_dpl(cpu_descriptor* d, uint32_t dpl){
    d->r1 &= ~((uint32_t)0b11 << 13);
    d->r1 |= (dpl & 0b11) << 13;
}

void cpu_descriptor_write_p_flag(cpu_descriptor* d, uint32_t p){
    d->r1 &= ~((uint32_t)1 << 15);
    d->r1 |= (p & 0x1) << 15;
}

void cpu_descriptor_write_d_flag(cpu_descriptor* de, uint32_t d){
    de->r1 &= ~((uint32_t)1 << 22);
    de->r1 |= (d & 0x1) << 22;
}

void cpu_descriptor_write_g_flag(cpu_descriptor* d, uint32_t g){
    d->r1 &= ~((uint32_t)1 << 23);
    d->r1 |= (g & 0x1) << 23;
}

void load_descriptor(cpu_descriptor* d, cpu_segment_selector* sel){
    cpu_descriptor* gtd = get_GDT();
    gtd[cpu_segment_selector_get_id(sel)] = *d;
}


void cpu_cgd_init(cpu_call_gate_descriptor* desc){
    desc->r2 = 0;
    desc->r2 |= (uint32_t)0b1100 << 8;
}

void cpu_cgd_set_segment_selector(cpu_call_gate_descriptor* desc,
    cpu_segment_selector* sel){
    desc->r1 &= 0xFFFF;
    desc->r1 |= sel->value << 16;
}
/*
void cpu_cgd_set_segment_selector(cpu_call_gate_descriptor* desc,
    cpu_segment_selector sel){
    cpu_cgd_set_segment_selector(desc, &sel);
}*/

void cpu_cgd_set_offset(cpu_call_gate_descriptor* desc, uint32_t offset){
    desc->r1 &= 0xFFFF0000;
    desc->r1 |= offset & 0xFFFF;

    desc->r2 &= 0xFFFF;
    desc->r2 |= offset & 0xFFFF0000;
}

void cpu_cgd_set_dpl(cpu_call_gate_descriptor* desc, uint32_t dpl){
    desc->r2 &= ~((uint32_t)0b11 << 13);
    desc->r2 |= (dpl & 0b11) << 13;
}

void cpu_cgd_set_p(cpu_call_gate_descriptor* desc, uint32_t p){
    desc->r2 &= ~((uint32_t)0b1 << 15);
    desc->r2 |= (p & 1) << 15;
}

void cpu_cgd_set_param_cout(cpu_call_gate_descriptor* desc, uint32_t param_count){
    desc->r2 &= ~((uint32_t)0b11111);
    desc->r2 |= param_count & 0b11111;
}
