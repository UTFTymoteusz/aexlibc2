[BITS 64]

global syscall
syscall:
    push rbp
    mov rbp, rsp

    push r11
    push r12
    push r14
    push r15

    mov r12, rdi ; id

    mov rdi, rsi ; a
    mov rsi, rdx ; b
    mov r14, rcx ; c
    ; r8 d
    ; r9 e

    syscall

    pop r15
    pop r14
    pop r12
    pop r11

    pop rbp
    ret