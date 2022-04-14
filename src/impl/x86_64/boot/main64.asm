global long_mode_start

section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov dword [0xb8000], 0x2f452f52         ; /R/Z
    mov dword [0xb8004], 0x2f5a2f59         ; /Y/E
    mov dword [0xb8008], 0x2f52             ; /R
    mov DWORD [0xb8010], 0x2f4d             ; /M
    mov dword [0xb8014], 0x2f4d2f4f         ; /M/O
    hlt