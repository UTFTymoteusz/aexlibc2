SECTION .text

EXTERN _init
EXTERN main

GLOBAL _start
_start:
    ; call _init
    call main

    mov rsi, rax
    mov rdi, 1
    syscall