#include "cpu/cpu_segment_selector.h"

#include <stdint.h>

uint32_t cpu_segment_selector_get_id(cpu_segment_selector* sel){
    return (sel->value >> 3);
}

void cpu_segment_selector_set_id(cpu_segment_selector* sel, uint16_t id){
    sel->value &= 0x7;
    sel->value |= (id << 3);
}
