    .text
    .globl main

    .section .rodata
_fmt_int:   .string "%ld\n"
_fmt_float: .string "%g\n"
_fmt_str:   .string "%s\n"
_fmt_read:  .string "%ld"

    .text

fatorial:
    pushq   %rbp
    movq    %rsp, %rbp


main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp

    movq    $5, %rdi
    call    fatorial
    movq    %rax, -16(%rbp)
    movq    -16(%rbp), %rax
    movq    %rax, -8(%rbp)
    movq    -8(%rbp), %rsi
    leaq    _fmt_int(%rip), %rdi
    xorq    %rax, %rax
    call    printf


    .bss
