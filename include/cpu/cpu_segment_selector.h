struct cpu_segment_selector{
    short int value;
};

#define CPU_SEG_SEL_GETID(SEL) (SEL.value >> 3)
#define CPU_SEG_SEL_SETID(SEL, ID) (SEL.value = (SEL.value & 0x7) | (ID << 3))

#define TD_GDT 0
#define TD_LDT 1
#define CPU_SEG_SEL_GET_TD(SEL) ((SEL.value >> 2) & 1)
#define CPU_SEG_SEL_SET_TD(SEL, TD) (SEL.value = (SEL.value & 0xFFFB) | (TD << 2))

#define CPU_SEG_SEL_GET_PL(SEL) (SEL.value & 3)
#define CPU_SEG_SEL_SET_PL(SEL, PL) (SEL.value = (SEL.value & 0xFFFC) | PL)