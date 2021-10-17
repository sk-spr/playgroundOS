global long_mode_start
extern  kernel_main
section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


    call kernel_main
    ;print OK
    ;mov byte [0xb8000], "o" ; letter O
    ;mov byte [0xb8001], 0x2f ; white on green

    ;mov byte [0xb8002], "k" ; letter K
    ;mov byte [0xb8003], 0x2e ; white on green

    hlt