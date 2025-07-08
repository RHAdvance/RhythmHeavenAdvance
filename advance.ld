OUTPUT_ARCH(arm)
ENTRY(__romPos)

SECTIONS {    
    . = 0;
    _start = . ;
    __romPos = 0x08000000;
    
    . = 0x03000000;
    .bss . : SUBALIGN(4) {
        "build/src/*.o"(.bss);
        "build/asm/*.o"(.bss);
    }
    
    . = 0x08000000;
    .cartrom . : AT(__romPos) SUBALIGN(4) {
        build/asm/rom_header.s.o(.text*);
        build/asm/boot.s.o(.text*);
        "build/src/*.o"(.text*);
        "build/asm/*.o"(.text*);
        *libgcc.a:*.o(.text*);
        *libc.a:*.o(.text*);

        "build/src/*.o"(.*);
        "build/asm/*.o"(.*);
        "build/data/*.o"(.*);
        "build/games/*.o"(.*);
        "build/graphics/*.o"(.*);
        "build/bin/*.o"(.*);
        "build/audio/*.o"(.*);
    }

    _end = . ;
     /DISCARD/ : {*(*);}
}