global gdt_set

gdtr DW 0 ; For limit storage
     DD 0 ; For base storage

gdt_set:
   mov   eax, [esp + 4]
   mov   [gdtr + 2], eax
   mov   ax, [esp + 8]
   mov   [gdtr], ax
   lgdt  [gdtr]
   ret
