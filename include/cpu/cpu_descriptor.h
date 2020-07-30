#ifndef CPU_DESCRIPTOR_H
#define CPU_DESCRIPTOR_H

#include <stdint.h>

#include "cpu/cpu_segment_selector.h"

#define CPU_DESCRIPTOR_S_SYSTEM 0
#define CPU_DESCRIPTOR_S_DATA 1

#define CPU_DESCRIPTOR_P_NOTPRESENT 0
#define CPU_DESCRIPTOR_P_PRESENT 1

#define CPU_DESCRIPTOR_D_16 0
#define CPU_DESCRIPTOR_D_32 1

#define CPU_DESCRIPTOR_G_1b_1m 0    /* inc: 1 byte */
#define CPU_DESCRIPTOR_G_4k_4g 1    /* inc: 4k     */


#define CPU_D_TYPE_READ_ONLY               0
#define CPU_D_TYPE_READ_ONLY_ACC           0b1
#define CPU_D_TYPE_READ_WRITE              0b10
#define CPU_D_TYPE_READ_WRITE_ACC          0b11
#define CPU_D_TYPE_READ_ONLY_EXPDOWN       0b100
#define CPU_D_TYPE_READ_ONLY_EXPDOWN_ACC   0b101
#define CPU_D_TYPE_READ_WRITE_EXPDOWN      0b110
#define CPU_D_TYPE_READ_WRITE_EXPDOWN_ACC  0b111

#define CPU_D_TYPE_EXE_ONLY                0b1000
#define CPU_D_TYPE_EXE_ONLY_ACC            0b1001
#define CPU_D_TYPE_EXE_READ                0b1010
#define CPU_D_TYPE_EXE_READ_ACC            0b1011
#define CPU_D_TYPE_EXE_ONLY_CONF           0b1100
#define CPU_D_TYPE_EXE_ONLY_CONF_ACC       0b1101
#define CPU_D_TYPE_EXE_READ_CONF           0b1110
#define CPU_D_TYPE_EXE_READ_CONF_ACC       0b1111

#define GDT_MAX 8192

typedef struct{
    uint32_t r2;
    uint32_t r1;
} cpu_descriptor;

/*
        Defines the location of byte 0 of the segment within the 4-GByte linear address space. The
    processor puts together the three base address fields to form a single 32-bit value. Segment base
    addresses should be aligned to 16-byte boundaries. Although 16-byte alignment is not required,
    this alignment allows programs to maximize performance by aligning code and data on 16-byte
    boundaries.
*/
void cpu_descriptor_write_base(cpu_descriptor* descr, uint32_t addr);



/*
        Specifies the size of the segment. The processor puts together the two segment limit fields to form
    a 20-bit value. The processor interprets the segment limit in one of two ways, depending on the
    setting of the G (granularity) flag:
        • If the granularity flag is clear, the segment size can range from 1 byte to 1 MByte, in byte increments.
        • If the granularity flag is set, the segment size can range from 4 KBytes to 4 GBytes, in 4-KByte increments.

        The processor uses the segment limit in two different ways, depending on whether the segment is
    an expand-up or an expand-down segment. See Section 3.4.5.1, “Code- and Data-Segment
    Descriptor Types”, for more information about segment types. For expand-up segments, the offset
    in a logical address can range from 0 to the segment limit. Offsets greater than the segment limit
    generate general-protection exceptions (#GP, for all segments other than SS)
    or stack-fault exceptions (#SS for the SS segment).
    For expand-down segments, the segment limit has the reverse
    function; the offset can range from the segment limit plus 1 to FFFFFFFFH or FFFFH, depending on
    the setting of the B flag. Offsets less than or equal to the segment limit generate general-protection
    exceptions or stack-fault exceptions. Decreasing the value in the segment limit field for an expanddown
    segment allocates new memory at the bottom of the segment's address space, rather than at
    the top. IA-32 architecture stacks always grow downwards, making this mechanism convenient for
    expandable stacks
*/
void cpu_descriptor_write_limit(cpu_descriptor* descr, uint32_t limit);


/*
        Specifies whether the segment descriptor is for a system segment (S flag is clear) or a code or data
    segment (S flag is set).
*/
void cpu_descriptor_write_s_type(cpu_descriptor* descr, uint32_t s);


/*
        Indicates the segment or gate type and specifies the kinds of access that can be made to the
    segment and the direction of growth. The interpretation of this field depends on whether the
    descriptor type flag specifies an application (code or data) descriptor or a system descriptor. The
    encoding of the type field is different for code, data, and system descriptors (see Figure 5-1). See
    Section 3.4.5.1, “Code- and Data-Segment Descriptor Types”, for a description of how this field is
    used to specify code and data-segment types.
*/
void cpu_descriptor_write_type(cpu_descriptor* descr, uint32_t type);


/*
        Specifies the privilege level of the segment. The privilege level can range from 0 to 3, with 0 being
    the most privileged level. The DPL is used to control access to the segment. See Section 5.5, “Privilege Levels”,
    for a description of the relationship of the DPL to the CPL of the executing code
    segment and the RPL of a segment selector.
*/
void cpu_descriptor_write_dpl(cpu_descriptor* d, uint32_t dpl);


/*
        Indicates whether the segment is present in memory (set) or not present (clear). If this flag is clear,
    the processor generates a segment-not-present exception (#NP) when a segment selector that
    points to the segment descriptor is loaded into a segment register. Memory management software
    can use this flag to control which segments are actually loaded into physical memory at a given
    time. It offers a control in addition to paging for managing virtual memory.
*/
void cpu_descriptor_write_p_flag(cpu_descriptor* d, uint32_t p);


/*
      Performs different functions depending on whether the segment descriptor is an executable code
    segment, an expand-down data segment, or a stack segment. (This flag should always be set to 1
    for 32-bit code and data segments and to 0 for 16-bit code and data segments.)
*/
void cpu_descriptor_write_d_flag(cpu_descriptor* de, uint32_t d);


/*
        Determines the scaling of the segment limit field. When the granularity flag is clear, the segment
    limit is interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units.
    (This flag does not affect the granularity of the base address; it is always byte granular.) When the
    granularity flag is set, the twelve least significant bits of an offset are not tested when checking the
    offset against the segment limit. For example, when the granularity flag is set, a limit of 0 results in
    valid offsets from 0 to 4095.
*/
void cpu_descriptor_write_g_flag(cpu_descriptor* d, uint32_t g);


void* get_GDT();


void load_descriptor(cpu_descriptor* d, cpu_segment_selector* sel);

#endif //CPU_DESCRIPTOR_H
