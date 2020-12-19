[BITS 64]

extern _set_errno ; a very temporary fix because i cant be bothered to figure out how to directly get the tls offsets lol

global syscall
syscall:
    push rbp
    mov rbp, rsp

    push rbx
    push r11
    push r12
    push r13
    push r14
    push r15

    mov r12, rdi ; id

    mov rdi, rsi ; a
    mov rsi, rdx ; b
    mov r14, rcx ; c
    ; r8 d
    ; r9 e

    syscall

    push rax
    push rdx

    mov edi, r12d
    call _set_errno

    pop rdx
    pop rax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop rbx

    pop rbp
    ret