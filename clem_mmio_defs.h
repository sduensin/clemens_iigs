//  support read or write operations
#define CLEM_MMIO_PAGE_WRITE_OK     0x00000001
//  use a mask of the requested bank and the 17th address bit of the read/write
//  bank
#define CLEM_MMIO_PAGE_MAINAUX      0x10000000
//  use the original bank register
#define CLEM_MMIO_PAGE_DIRECT       0x40000000
//  redirects to Mega2 I/O registers
#define CLEM_MMIO_PAGE_IOADDR       0x80000000

//  These flags refer to bank 0 memory switches for address bit 17
//  0 = Main Bank, 1 = Aux Bank ZP, Stack and Language Card
#define CLEM_MMIO_MMAP_ALTZPLC      0x00000001
//  0 = Main Bank RAM Read Enabled, 1 = Aux Bank RAM Read Enabled
#define CLEM_MMIO_MMAP_RAMRD        0x00000002
//  0 = Main Bank RAM Write Enabled, 1 = Aux Bank RAM Write Enabled
#define CLEM_MMIO_MMAP_RAMWRT       0x00000004

//  Bits 4-7 These flags refer to the language card banks
#define CLEM_MMIO_MMAP_LC           0x000000f0
//  0 = Read LC ROM, 1 = Read LC RAM
#define CLEM_MMIO_MMAP_RDLCRAM      0x00000010
//  0 = Write protect LC RAM, 1 = Write enable LC RAM
#define CLEM_MMIO_MMAP_WRLCRAM      0x00000020
//  0 = LC Bank 1, 1 = LC Bank 2
#define CLEM_MMIO_MMAP_LCBANK2      0x00000040
//  0 = Internal ROM, 1 = Peripheral ROM
#define CLEM_MMIO_MMAP_CXROM        0x00000100
//  0 = Internal Slot 3 ROM, 1 = Peripheral Slot 3 ROM
#define CLEM_MMIO_MMAP_C3ROM        0x00000200

// Bits 16-23 These flags refer to shadow register controls
#define CLEM_MMIO_MMAP_NSHADOW      0x00ff0000
#define CLEM_MMIO_MMAP_NSHADOW_TXT1 0x00010000
#define CLEM_MMIO_MMAP_NSHADOW_TXT2 0x00020000
#define CLEM_MMIO_MMAP_NSHADOW_HGR1 0x00040000
#define CLEM_MMIO_MMAP_NSHADOW_HGR2 0x00080000
#define CLEM_MMIO_MMAP_NSHADOW_SHGR 0x00100000
#define CLEM_MMIO_MMAP_NSHADOW_AUX  0x00200000

//  0 = Bank 00: I/O enabled + LC enabled,  1 = I/O disabled + LC disabled
#define CLEM_MMIO_MMAP_NIOLC        0x01000000

/** Flags for _clem_mmio_read */
#define CLEM_MMIO_READ_NO_OP        0x01

/**
 * IO Registers
 */
/** Write to enable peripheral ROM for C100 - CFFF */
#define CLEM_MMIO_REG_SLOTCXROM     0x06
/** Write to enable internal ROM for C100 - CFFF */
#define CLEM_MMIO_REG_INTCXROM      0x07
/** Write to enable main bank Page 0, Page 1 and LC */
#define CLEM_MMIO_REG_STDZP         0x08
/** Write to enable aux bank Page 0, Page 1 and LC */
#define CLEM_MMIO_REG_ALTZP         0x09
/** Write to enable peripheral ROM for C300 */
#define CLEM_MMIO_REG_SLOTC3ROM     0x0A
/** Write to enable internal ROM for C300 */
#define CLEM_MMIO_REG_INTC3ROM      0x0B
/** Read and test bit 7, 0 = LC bank 1, 1 = bank 2 */
#define CLEM_MMIO_REG_LC_BANK_TEST  0x11
/** Read and test bit 7, 0 = ROM, 1 = RAM */
#define CLEM_MMIO_REG_ROM_RAM_TEST  0x12
/** Get ROM source for the CXXX pages */
#define CLEM_MMIO_REG_READCXROM     0x15
/** Read bit 7 to detect bank 0 = main, 1 = aux bank */
#define CLEM_MMIO_REG_RDALTZP       0x16
/** Get ROM source for the C300 page */
#define CLEM_MMIO_REG_READC3ROM     0x17
/**
 * Primarily defines how memory is accessed by the video controller, with
 * the bank latch bit (0), which is always set to 1 AFAIK
 */
#define CLEM_MMIO_REG_NEWVIDEO      0x29
/**
 * Defines what areas of the FPI banks are disabled, and how I/O language
 * card space is treated on FPI bank 0 and 1.
 */
#define CLEM_MMIO_REG_SHADOW        0x35
/**
 * Defines fast/slow processor speed, system-wide shadowing behavior and other
 * items... (disk input?)
 */
#define CLEM_MMIO_REG_SPEED         0x36
/**
 * Amalgom of the C08x registers
 */
#define CLEM_MMIO_REG_STATEREG      0x68

/** R1 - LC Bank 2, Read RAM, Write Protect */
#define CLEM_MMIO_REG_LC2_RDRAM_WP  0x80
/** R2 - LC Bank 2, Read ROM, Write Enable */
#define CLEM_MMIO_REG_LC2_ROM_WE    0x81
/** R1 - LC Bank 2, Read ROM, Write Protect */
#define CLEM_MMIO_REG_LC2_ROM_WP    0x82
/** R2 - LC Bank 2, Read and Write Enable */
#define CLEM_MMIO_REG_LC2_RAM_WE    0x83
/** R1 - LC Bank 1, Read RAM, Write Protect */
#define CLEM_MMIO_REG_LC1_RAM_WP    0x88
/** R2 - LC Bank 1, Read ROM, Write Enable */
#define CLEM_MMIO_REG_LC1_ROM_WE    0x89
/** R1 - LC Bank 2, Read ROM, Write Protect */
#define CLEM_MMIO_REG_LC1_ROM_WP    0x8A
/** R2 - LC Bank 2, Read and Write Enable */
#define CLEM_MMIO_REG_LC1_RAM_WE    0x8B
