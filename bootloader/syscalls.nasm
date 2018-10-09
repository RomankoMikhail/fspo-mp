%include "fatdef.nasm"



;printmsg:
;        mov     ah, 0x0e
;        mov     al, [si]
;        inc     si
;        cmp     al, 0
;        je      .cot
;        int     0x10
;        jmp     printmsg
;.cot:
;        ret
