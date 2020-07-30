#ifndef CPU_SEGMENT_SELECTOR_H
#define CPU_SEGMENT_SELECTOR_H

#include <stdint.h>

typedef struct{
    uint16_t value;
} cpu_segment_selector;

#define CPU_SEL_CODE  0
#define CPU_SEL_DATA  1
#define CPU_SEL_STACK 2

typedef struct{
    cpu_segment_selector sels[3];
} cpu_segment_selector_pack;

uint32_t cpu_segment_selector_get_id(cpu_segment_selector* sel);
void cpu_segment_selector_set_id(cpu_segment_selector* sel, uint16_t id);

#define CPU_SEG_SEL_GETID(SEL) (SEL.value >> 3)
#define CPU_SEG_SEL_SETID(SEL, ID) (SEL.value = (SEL.value & 0x7) | (ID << 3))

#define TD_GDT 0
#define TD_LDT 1
#define CPU_SEG_SEL_GET_TD(SEL) ((SEL.value >> 2) & 1)
#define CPU_SEG_SEL_SET_TD(SEL, TD) (SEL.value = (SEL.value & 0xFFFB) | (TD << 2))

#define CPU_SEG_SEL_GET_PL(SEL) (SEL.value & 3)
#define CPU_SEG_SEL_SET_PL(SEL, PL) (SEL.value = (SEL.value & 0xFFFC) | PL)

#endif
