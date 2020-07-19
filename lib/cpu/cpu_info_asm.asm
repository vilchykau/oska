section .text

struc cpu_cpuid_mask
     .ecx resd 1
     .edx resd 1
endstruc


global cpu_cpuid_is_enable
cpu_cpuid_is_enable:
    pushfd                               ;Save EFLAGS
    pushfd                               ;Store EFLAGS
    xor dword [esp],0x00200000           ;Invert the ID bit in stored EFLAGS
    popfd                                ;Load stored EFLAGS (with ID bit inverted)
    pushfd                               ;Store EFLAGS again (ID bit may or may not be inverted)
    pop eax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
    xor eax,[esp]                        ;eax = whichever bits were changed
    popfd                                ;Restore original EFLAGS
    and eax,0x00200000                   ;eax = zero if ID bit can't be changed, else non-zero
    ret

global cpu_cpuid_get_mask
cpu_cpuid_get_mask:
    mov eax, 0x0
    cpuid

    push esi
    mov esi, [esp+8]

    mov [esi + cpu_cpuid_mask.ecx], ecx
    mov [esi + cpu_cpuid_mask.edx], edx

    pop esi
    ret

end
