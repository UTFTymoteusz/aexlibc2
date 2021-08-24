SECTION .text

EXTERN init
EXTERN main
EXTERN exit

GLOBAL _start
_start:
    push rdi
    push rsi

    call init

    pop rsi
    pop rdi

    call main
    
    mov rdi, rax
    call exit

    ud2
    hlt