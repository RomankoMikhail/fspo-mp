;=============================================================================
; ATA read sectors (CHS mode)
; Max head index is 15, giving 16 possible heads
; Max cylinder index can be a very large number (up to 65535)
; Sector is usually always 1-63, sector 0 reserved, max 255 sectors/track
; If using 63 sectors/track, max disk size = 31.5GB
; If using 255 sectors/track, max disk size = 127.5GB
; See OSDev forum links in bottom of [http://wiki.osdev.org/ATA]
;
; @param EBX The CHS values; 2 bytes, 1 byte (BH), 1 byte (BL) accordingly
; @param CH The number of sectors to read
; @param RDI The address of buffer to put data obtained from disk
;
; @return None
;=============================================================================
[bits 32]

global ata_chs_read
global ata_chs_write

ata_chs_read:   ;pushfh
                push eax
                push ebx
                push ecx
                push edx
                push edi

                mov edx,0x1f6            ;port to send drive & head numbers
                mov al,bh               ;head index in BH
                and al,00001111b        ;head is only 4 bits long
                or  al,10100000b        ;default 1010b in high nibble
                out dx,al

                mov edx,0x1f2           ;Sector count port
                mov al,ch               ;Read CH sectors
                out dx,al

                mov edx,0x1f3           ;Sector number port
                mov al,bl               ;BL is sector index
                out dx,al

                mov edx,0x1f4           ;Cylinder low port
                mov eax,ebx             ;byte 2 in ebx, just above BH
                mov cl,16
                shr eax,cl              ;shift down to AL
                out dx,al

                mov edx,0x1f5            ;Cylinder high port
                mov eax,ebx             ;byte 3 in ebx, just above byte 2
                mov cl,24
                shr eax,cl              ;shift down to AL
                out dx,al

                mov edx,0x1f7           ;Command port
                mov al,20h              ;Read with retry.
                out dx,al

.still_going:   in al,dx
                test al,8               ;the sector buffer requires servicing.
                jz .still_going         ;until the sector buffer is ready.

                mov eax,512/2           ;to read 256 words = 1 sector
                xor bx,bx
                mov bl,ch               ;read CH sectors
                mul bx
                mov ecx,eax             ;RCX is counter for INSW
                mov edx,0x1f0            ;Data port, in and out
                rep insw                ;in to [RDI]

                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
;                popfh
                ret

ata_chs_write:  ;pushfh
                push eax
                push ebx
                push ecx
                push edx
                push edi

                mov edx,0x1f6            ;port to send drive & head numbers
                mov al,bh               ;head index in BH
                and al,00001111b        ;head is only 4 bits long
                or  al,10100000b        ;default 1010b in high nibble
                out dx,al

                mov edx,0x1f2           ;Sector count port
                mov al,ch               ;Read CH sectors
                out dx,al

                mov edx,0x1f3           ;Sector number port
                mov al,bl               ;BL is sector index
                out dx,al

                mov edx,0x1f4           ;Cylinder low port
                mov eax,ebx             ;byte 2 in ebx, just above BH
                mov cl,16
                shr eax,cl              ;shift down to AL
                out dx,al

                mov edx,0x1f5            ;Cylinder high port
                mov eax,ebx             ;byte 3 in ebx, just above byte 2
                mov cl,24
                shr eax,cl              ;shift down to AL
                out dx,al

                mov edx,0x1f7           ;Command port
                mov al,20h              ;Read with retry.
                out dx,al

.still_going:   in al,dx
                test al,8               ;the sector buffer requires servicing.
                jz .still_going         ;until the sector buffer is ready.

                mov eax,512/2           ;to read 256 words = 1 sector
                xor bx,bx
                mov bl,ch               ;read CH sectors
                mul bx
                mov ecx,eax             ;RCX is counter for INSW
                mov edx,0x1f0            ;Data port, in and out
                rep insw                ;in to [RDI]

                pop edi
                pop edx
                pop ecx
                pop ebx
                pop eax
;                popfh
                ret
