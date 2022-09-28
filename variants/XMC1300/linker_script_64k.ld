/**
 * @file XMC1300x0064.ld
 * @date 2021-01-11
 ~
 * @cond
 *********************************************************************************************************************
 * Linker file for the GNU C Compiler v1.10
 * Supported devices: XMC130x-ANY package with 64kB Flash and 16kB RAM
 *
 * Updated January 2021 for any 64kB Flash device
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with
 * Infineon Technologies AG dave@infineon.com).
 *********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-07-07:
 *     - Product splitting
 *     - Copyright notice update
 *
 * 2015-11-24:
 *     - Compatibility with GCC 4.9 2015q2
 *
 * 2016-03-15:
 *     - Add assertion to check that region SRAM_combined does not overflowed no_init section
 *
 * 2016-06-07:
 *     - Add XMC1302-Q040X0200
 *
 * 2018-03-08:
 *     - Change default XMC1xxx stack size
 *     - Move Stack to top of RAM below no_init for more standard and safer location
 *     - Could mean startup_XMC1xxx.S could be shortened
 *
 * 2021-01-11:
 *     - Split script to different flash size files for Boot Kit and Sense2GoL
 *
 * @endcond
 *
 */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Reset_Handler)

MEMORY
{
    FLASH(RX) : ORIGIN = 0x10001000, LENGTH = 0x10000
    SRAM(!RX) : ORIGIN = 0x20000000, LENGTH = 0x4000
}

stack_size = DEFINED(stack_size) ? stack_size : 1024;
no_init_size = 4;

SECTIONS
{
    /* TEXT section */

    .text :
    {
      sText = .;
      KEEP(*(.reset));
      *(.text .text.* .gnu.linkonce.t.*);

      /* C++ Support */
      KEEP(*(.init))
      KEEP(*(.fini))

      /* .ctors */
      *crtbegin.o(.ctors)
      *crtbegin?.o(.ctors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
      *(SORT(.ctors.*))
      *(.ctors)

      /* .dtors */
      *crtbegin.o(.dtors)
      *crtbegin?.o(.dtors)
      *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
      *(SORT(.dtors.*))
      *(.dtors)

      *(.rodata .rodata.*)
      *(.gnu.linkonce.r*)
      . = ALIGN(4);
    } > FLASH

    .eh_frame_hdr : ALIGN (4)
    {
      KEEP (*(.eh_frame_hdr))
    } > FLASH

    .eh_frame : ALIGN (4)
    {
      KEEP (*(.eh_frame))
    } > FLASH

    /* Exception handling, exidx needs a dedicated section */
    .ARM.extab : ALIGN(4)
    {
      *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    . = ALIGN(4);
    __exidx_start = .;
    .ARM.exidx : ALIGN(4)
    {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;
    . = ALIGN(4);

    /* End of RO-DATA and start of LOAD region for the veneers */
    eROData = . ;

    /* DSRAM layout (Lowest to highest)*/
    /* Veneer <-> DATA <-> ram_code <-> BSS <-> HEAP <-> memory gap <-> Stack <-> no_init */

    .VENEER_Code ABSOLUTE(0x2000000C): AT(eROData)
    {
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        VeneerStart = .;
        KEEP(*(.XmcVeneerCode));
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        VeneerEnd = .;
    } > SRAM

    VeneerSize = ABSOLUTE(VeneerEnd) - ABSOLUTE(VeneerStart);

     /* Standard DATA and user defined DATA/BSS/CONST sections */
    DataLoadAddr = eROData + VeneerSize;
    .data : AT(DataLoadAddr)
    {
      . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
      __data_start = .;
      *(vtable)
      * (.data);
      * (.data*);
      *(*.data);
      *(.gnu.linkonce.d*)

      . = ALIGN(4);
      /* preinit data */
      PROVIDE_HIDDEN (__preinit_array_start = .);
      KEEP(*(.preinit_array))
      PROVIDE_HIDDEN (__preinit_array_end = .);

      . = ALIGN(4);
      /* init data */
      PROVIDE_HIDDEN (__init_array_start = .);
      KEEP(*(SORT(.init_array.*)))
      KEEP(*(.init_array))
      PROVIDE_HIDDEN (__init_array_end = .);


      . = ALIGN(4);
      /* finit data */
      PROVIDE_HIDDEN (__fini_array_start = .);
      KEEP(*(SORT(.fini_array.*)))
      KEEP(*(.fini_array))
      PROVIDE_HIDDEN (__fini_array_end = .);

      . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
      __data_end = .;
    } > SRAM
    __data_size = __data_end - __data_start;

    .ram_code : AT(DataLoadAddr + __data_size)
    {
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        __ram_code_start = .;
        /* functions with __attribute__ ((section (".ram_code")))*/
        *(.ram_code)
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        __ram_code_end = .;
    } > SRAM
    __ram_code_load = LOADADDR (.ram_code);
    __ram_code_size = __ram_code_end - __ram_code_start;

    /* BSS section */
    .bss (NOLOAD) :
    {
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        __bss_start = .;
        * (.bss);
        * (.bss*);
        * (COMMON);
        *(.gnu.linkonce.b*)
        . = ALIGN(4); /* section size must be multiple of 4. See startup_XMC_xxxx.S file */
        __bss_end = .;
        Heap_Bank1_Start = .;
    } > SRAM
    __bss_size = __bss_end - __bss_start;

    _stack_begin = ORIGIN(SRAM) + LENGTH(SRAM) - stack_size - (2 * no_init_size);

    /* Dummy section for stack  */
    Stack _stack_begin (NOLOAD) :
    {
        . = ORIGIN(SRAM) + LENGTH(SRAM) - stack_size - (2 * no_init_size);
        Heap_Bank1_End = .;
        end = Heap_Bank1_End;
        __stack_start = .;
         . = . + stack_size;
        __stack_end = .;
        __initial_sp = .;
    } > SRAM

    /* Heap - Bank1*/

    Heap_Bank1_Size  = Heap_Bank1_End - Heap_Bank1_Start;

    ASSERT(Heap_Bank1_Start <= Heap_Bank1_End, "bss section SRAM overflowed stack section")

    /* .no_init section contains SystemCoreClock. See system_XMC_xxxx.c file */
    .no_init ORIGIN(SRAM) + LENGTH(SRAM) - no_init_size (NOLOAD) :
    {
        * (.no_init);
    } > SRAM


    /DISCARD/ :
    {
        *(.comment)
    }

    .stab              0 (NOLOAD) : { *(.stab) }
    .stabstr           0 (NOLOAD) : { *(.stabstr) }

    /* DWARF 1 */
    .debug             0 : { *(.debug) }
    .line              0 : { *(.line) }

    /* GNU DWARF 1 extensions */
    .debug_srcinfo     0 : { *(.debug_srcinfo) }
    .debug_sfnames     0 : { *(.debug_sfnames) }

    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges     0 : { *(.debug_aranges) }
    .debug_pubnames    0 : { *(.debug_pubnames) }
    .debug_pubtypes    0 : { *(.debug_pubtypes) }

    /* DWARF 2 */
    .debug_info        0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev      0 : { *(.debug_abbrev) }
    .debug_line        0 : { *(.debug_line) }
    .debug_frame       0 : { *(.debug_frame) }
    .debug_str         0 : { *(.debug_str) }
    .debug_loc         0 : { *(.debug_loc) }
    .debug_macinfo     0 : { *(.debug_macinfo) }

    /* DWARF 2.1 */
    .debug_ranges      0 : { *(.debug_ranges) }

    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames   0 : { *(.debug_weaknames) }
    .debug_funcnames   0 : { *(.debug_funcnames) }
    .debug_typenames   0 : { *(.debug_typenames) }
    .debug_varnames    0 : { *(.debug_varnames) }

    /* Build attributes */
    .build_attributes  0 : { *(.ARM.attributes) }
}
