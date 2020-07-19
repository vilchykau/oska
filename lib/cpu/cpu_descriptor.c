#include "cpu/cpu_descriptor.h"

void cpu_descriptor_write_base(struct cpu_descriptor* d, uint32_t addr){
    d->r2 &= 0xFFFF;
    d->r2 |= (addr & 0xFFFF) << 16;

    d->r1 &= 0xFFFF00;
    d->r1 |= (addr & 0xFF000000) | ((addr >> 16) & 0xFF);
}

void cpu_descriptor_write_limit(struct cpu_descriptor* d, uint32_t limit){
    d->r2 &= 0xFFFF0000;
    d->r2 |= (limit & 0xFFFF);

    d->r1 &= 0xFFF0FFFF;
    d->r1 |= (limit & 0x000F0000);
}

void cpu_descriptor_write_s_type(struct cpu_descriptor* d, uint32_t s){
    d->r1 &= ~((uint32_t)1 << 12);
    d->r1 |= (s & 0x1) << 12;
}

void cpu_descriptor_write_type(struct cpu_descriptor* d, uint32_t type){
    d->r1 &= 0xFFFFF0FF;
    d->r1 |= (type & 0xF) << 8;
}

void cpu_descriptor_write_dpl(struct cpu_descriptor* d, uint32_t dpl){
    d->r1 &= ~((uint32_t)0b11 << 13);
    d->r1 |= (dpl & 0b11) << 13;
}

void cpu_descriptor_write_p_flag(struct cpu_descriptor* d, uint32_t p){
    d->r1 &= ~((uint32_t)1 << 15);
    d->r1 |= (s & 0x1) << 15;
}
