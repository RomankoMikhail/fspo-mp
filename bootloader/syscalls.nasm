%include "fatdef.nasm"

;------------------------------------------------------------------------------
; Read a sector from disk, using LBA
; input:   EAX - 32-bit DOS sector number
;      ES:BX - destination buffer
; output:   ES:BX points one byte after the last byte read
;      EAX - next sector
readsector:
    push dx
    push si
    push di

.read_it:
    push eax   ; Save the sector number
    mov di, sp   ; remember parameter block end

    push byte 0   ; other half of the 32 bits at [C]
    push byte 0   ; [C] sector number high 32bit
    push eax   ; [8] sector number low 32bit
    push es    ; [6] buffer segment
    push bx    ; [4] buffer offset
    push byte 1   ; [2] 1 sector (word)
    push byte 16   ; [0] size of parameter block (word)

    mov si, sp
    mov dl, [bsDriveNumber]
    mov ah, 42h   ; EXTENDED READ
    int 0x13   ; http://hdebruijn.soo.dto.tudelft.nl/newpage/interupt/out-0700.htm#0651

    mov sp, di   ; remove parameter block from stack
    pop eax      ; Restore the sector number

    jnc .read_ok    ; jump if no error

    push ax
    xor ah, ah   ; else, reset and retry
    int 0x13
    pop ax
    jmp .read_it

.read_ok:
    inc eax       ; next sector
    add bx, 512      ; Add bytes per sector
    jnc .no_incr_es      ; if overflow...

.incr_es:
    mov dx, es
    add dh, 0x10      ; ...add 1000h to ES
    mov es, dx

.no_incr_es:
    pop di
    pop si
    pop dx
    ret
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Read a cluster from disk, using LBA
; input:   AX - 16-bit cluster number
;      ES:BX - destination buffer
; output:   ES:BX points one byte after the last byte read
;      AX - next cluster
readcluster:
    push cx
    mov [tclust], ax      ; save our cluster value
;cluster X starting sector
; starting sector = (bsSecsPerClust * (cluster# - 2)) + datastart
    xor cx, cx
    sub ax, 2
    mov cl, byte [bsSecsPerClust]
    imul cx      ; EAX now holds starting sector
    add ax, word [dstart]   ; add the datastart offset

    xor cx, cx
    mov cl, byte [bsSecsPerClust]
.readcluster_nextsector:
    call readsector
    dec cx
    cmp cx, 0
    jne .readcluster_nextsector

; Great! We read a cluster.. now find out where the next cluster is
    push bx   ; save our memory pointer
    mov bx, 0x7E00   ; load a sector from the root cluster here
    push bx
    mov ax, [bsResSectors]
    call readsector
    pop bx   ; bx points to 0x7e00 again
    mov ax, [tclust] ; ax holds the cluster # we just read
    shl ax, 1   ; multipy by 2
    add bx, ax
    mov ax, [bx]
    
    pop bx   ; restore our memory pointer
    pop cx
    
    ret

printmsg:
    push bp
.clp:
    mov ah, 0x0e
    mov al, [si]
    inc si
    cmp al, 0
    je .cot
    int 0x10
    jmp .clp
.cot:
    pop bp
    ret