This toy project aims at creating a kernel running on the x86_64 architecture for educational purposes.
The goal is to understand what is a kernel, its use in a computer system, the mecanisms through which it achieves its functionalities.
The kernel is tested against qemu and operates in video mode.
This means that the kernel takes care of rendering character glyphs before sending them out to the graphics card.
It also implements its own utf8 engine meaning that it can display latin characters but it does also the print cyrillic alphabet.
The code uses the x64BareBones bootloader in order to have an entry point with a processor that's not in real mode.
