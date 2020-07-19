section .text

extern divide_by_zero

resqf:
;    call divide_by_zero
    iret

global register_inter_init
register_inter_init:
    push ebx
    mov eax, 44

    mov ebx, resqf
    mov [eax], ebx

    pop ebx

    ret

global call_int
call_int:
    int 44
    ret

end    
