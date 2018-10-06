# fspo-mp

# Tools
## Windows
Any usefull tools for Windows can be found [on my Google Drive folder](https://drive.google.com/drive/folders/1OuOFH21THfU4dd29RGbahGftpbpv0kTR?usp=sharing)
Here list of tools:
 - Bochs VM (provides good interface for bootloader, gdt and idt debugging);
 - Code::Blocks (in particular MinGW compiler suite);
 - HxD Hex editor;
 - ImDisk Toolkit (for disk image mounting and editing);
 - Nasm;
 - git client
 - Visual Studio Code (IMHO best tool for code writing).

## Linux
### Debian based (Ubuntu, KDE Neon and etc.)
If you using Debian based system you want to install:
```
apt install nasm bochs build-essential gcc-multilib g++-multilib git
```
Optionaly you may need descent hex editor (wxHexEditor, Bless or Okteta)
### Other linux distros
You need to install following:
 - bochs vm;
 - gcc and g++ with 32 bit target support;
 - make;
 - nasm;
 - git;
 - any hex editor;
 - any code editor.
# Notes
## Bootloader
 - bootloader is designed to be used on ***FAT16*** filesystems. You need to copy last 450 bytes into your disk image with offset 0x3E.
 - bootloader loads BOOT.SYS file on address 0x9000
 - bootloader sets 32 protected mode
 - bootloader sets 1024x768x24 bit vesa mode, address is stored on 0x8000 (and somewhere between 0x500 - 0x7BFF)
## Bochs
 - to use the GUI debugger specify in bochs configuration file ```options="gui_debug"``` near ```display_library:```
 ```
 display_library: x, options="gui_debug"
 ```
 or
 ```
 display_library: win32, options="gui_debug"
 ```
