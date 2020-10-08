SECTION .text

EXTERN _init
EXTERN main

GLOBAL _start
_start:
    ; call _init
    call main

    mov rdi, rax
    mov r12, 1
    syscall

    ud2
    hlt