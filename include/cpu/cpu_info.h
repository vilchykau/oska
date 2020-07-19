#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <stdint.h>
#include <stdbool.h>

struct cpu_cpuid_mask{
    uint32_t edx;
    uint32_t ecx;
};

bool cpu_cpuid_is_enable();
//void cpu_cpuid_get_mask(cpu_cpuid_mask* m);

#endif