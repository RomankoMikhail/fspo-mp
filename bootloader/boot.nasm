initVesa:
        xor     ax, ax
        mov     cx, 256
        mov     di, 0x500
        rep     stosb
        mov     ax, 0x4f01
        mov     cx, 0x112 ; 1024*768*24bit
        mov     di, targetVideoTbl
        int     0x10

        mov     ax, 0x4f02
        mov     bx, 0x4112
        int     0x10
        ;	mov     eax, [targetVideoTbl + 0x28]
        ;	mov     dword[0x8000], eax
        ret