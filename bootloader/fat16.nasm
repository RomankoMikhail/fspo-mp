; Целевой адрес загрузки
%define targetAddr      0x9000
%define targetVideoTbl  0x500
%include "fatdef.nasm"

        org     0x7C00

entry:  jmp     short boot
        nop

; Резервируем место для заголовка FAT16
        times   0x3B db 0x90

; Код загрузки первоначального файла 'ядра'
; Подготавливаем основную систему и сохраняем номер диска, с которого мы загрузились (BIOS передает его через dl).
boot:   ;jmp     0x0000:0x7C43
        xor     eax, eax
        mov     esi, eax
        mov     edi, eax
        mov     ds, ax
        mov     es, ax
        mov     bp, 0x7C00
        mov     [bsDriveNumber], dl

; Подготавливаемся к загрузке файла
        mov     ax, [bsSecsPerFat]
        shl     ax, 1
        add     ax, [bsResSectors]
        mov     [rstart], ax

        mov     bx, [bsRootDirEnts]
        shr     bx, 4
        add     bx, ax
        mov     [dstart], bx

.next_sector:
        mov     bx, targetAddr
        mov     si, bx
        mov     di, bx
        call    readsector

.next_entry:
        mov     cx, 11
        mov     si, mFile
        repe    cmpsb
        jz      .done
        add     di, byte 0x20
        and     di, byte -0x20
        cmp     di, [bsBytesPerSec]
        jnz     .next_entry
        dec     dx
        jnz     .next_sector

        ;mov     si, mErr
        ;call    printmsg
        jmp     $

.done:
        ;mov     si, mLoad
        ;call    printmsg
        add     di, 15
        mov     ax, [di]
        
        mov     bx, targetAddr
.loadfile:
        call    readcluster
        cmp     ax, 0xFFF8
        jg      .loadfile

; Инициализация VESA и GDT
        xor     eax, eax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax
        mov     sp, 0xfffc

        call    initVesa
        ;call    do_e820
        cli

        lgdt    [gd_table]

        mov     eax, cr0
        or      eax, 1
        mov     cr0, eax
        mov     ax, DATA_D      ; BUG #1
        mov     ds, ax          ; BUG #1
        mov     es, ax          ; BUG?
        mov     ss, ax          ; BUG?
        jmp     CODE_D:targetAddr
        jmp     $
        

; Функции для чтения с диска и вывода на экран.
%include "syscalls.nasm"

dstart  dw      0x0000
rstart  dw      0x0000
tclust  dw      0x0000

; Сообщение при загрузке необходимого файла
;mLoad   db  "LOADING... ", 0

; Сообщение при остуствии файла (отсутствие 0 в конце строки позволит вывести на экран имя необходимого файла)
;mErr    db  "NO "
mFile   db  "BOOT    SYS"

gdt_begin:
null_desc:
	dd      0
	dd      0
code_desc:
	dw      0xffff
	dw      0
	db      0
	db      0b10011010
	db      0b11001111
	db      0
data_desc:
	dw      0xffff
	dw      0
	db      0
	db      0b10010010
	db      0b11001111
	db      0
gdt_end:

gd_table:
	dw      gdt_end - gdt_begin
	dd      gdt_begin

CODE_D  equ     code_desc - gdt_begin
DATA_D  equ     data_desc - gdt_begin

; Дополняем файл до 512 байт
        times 510-$+$$ db 0

; Сигнатура загрузчика
sign    dw      0xAA55
