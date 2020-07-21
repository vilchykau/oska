section .text

global get_GDT
get_GDT:
    sub esp, 3
    lgdt [esp]
    add esp, 1
    mov eax, [esp]
    add esp, 2
    ret

end