SECTION .text

EXTERN _init
EXTERN main
EXTERN exit
EXTERN stdio_init

GLOBAL _start
_start:
    push rdi
    push rsi

    call stdio_init

    pop rsi
    pop rdi

    call main
    
    mov rdi, rax
    call exit

    ud2
    hlt