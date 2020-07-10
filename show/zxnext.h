#ifndef ZXNEXT_H
#define ZXNEXT_H
/* Register and Port definitions for the ZX Spectrum Next */
/* next registers */
#define R_MACHID 0x00
#define R_COREVER 0x01
#define R_RESET 0x02
#define R_MACHTYP 0x03
#define R_CONFMAP 0x04
#define R_PER1 0x05
#define R_PER2 0x06
#define R_CPUSPD 0x07
#define R_PER3 0x08
#define R_PER4 0x09
#define R_PER5 0x0A
#define R_COREVERSM 0x0E
#define R_COREBOOT 0x10
#define R_VIDTIME 0x11
#define R_L2ACTIVE 0x12
#define R_L2SHADOW 0x13
#define R_GLBLTRANS 0x14
#define R_SPRTCTL 0x15
#define R_L2XOFF 0x16
#define R_L2YOFF 0x17
#define R_L2CLIP 0x18
#define R_SPRTCLIP 0x19
#define R_ULACLIP 0x1A
#define R_TILECLIP 0x1B
#define R_CLIPCTL 0x1C
#define R_LINEMSB 0x1E
#define R_LINELSB 0x1F
#define R_LINEINTCTL 0x22
#define R_LINEINTLSB 0x23
#define R_ULAXOFF 0x26
#define R_ULAYOFF 0x27
#define R_PS2KEYADDMSB 0x28
#define R_PS2KEYADDLSB 0x29
#define R_PS2KEYDATMSB 0x2A
#define R_PS2KEYDATLSB 0x2B
#define R_DACB 0x2C
#define R_DACAD 0x2D
#define R_DACC 0x2E
#define R_TILEXOFFMSB 0x2F
#define R_TILEXOFFLSB 0x30
#define R_TILEYOFF 0x31
#define R_LORESXOFF 0x32
#define R_LORESYOFF 0x33
#define R_SPRTNUM 0x34
#define R_SPRTATTR0 0x35
#define R_SPRTATTR1 0x36
#define R_SPRTATTR2 0x37
#define R_SPRTATTR3 0x38
#define R_SPRTATTR4 0x39
#define R_PALIDX 0x40
#define R_PALVAL8 0x41
#define R_ULAATTRFMT 0x42
#define R_PALCTL 0x43
#define R_PALVAL9 0x44
#define R_FBCOL 0x4A
#define R_SPRTTRANS 0x4B
#define R_TILETRANS 0x4C
#define R_MMU0 0x50
#define R_MMU1 0x51
#define R_MMU2 0x52
#define R_MMU3 0x53
#define R_MMU4 0x54
#define R_MMU5 0x55
#define R_MMU6 0x56
#define R_MMU7 0x57
#define R_CPPRDAT8 0x60
#define R_CPPRADDLSB 0x61
#define R_CPPRCTL 0x62
#define R_CPPRDAT16 0x63
#define R_CPPRVERTOFF 0x64
#define R_ULACTL 0x68
#define R_DISPCTL1 0x69
#define R_LORESCTL 0x6A
#define R_TILECTL 0x6B
#define R_TILEDEFATTR 0x6C
#define R_TILEMAPADD 0x6E
#define R_TILEDEFADD 0x6F
#define R_L2CTL 0x70
#define R_L2XOFFMSB 0x71
#define R_SPRTATTR0I 0x75
#define R_SPRTATTR1I 0x76
#define R_SPRTATTR2I 0x77
#define R_SPRTATTR3I 0x78
#define R_SPRTATTR4I 0x79
#define R_USRREG0 0x7F
#define R_EXPBUSEN 0x80
#define R_EXPBUSCTL 0x81
#define R_INTPORTEN0 0x82
#define R_INTPORTEN1 0x83
#define R_INTPORTEN2 0x84
#define R_INTPORTEN3 0x85
#define R_EXPBUSEN0 0x86
#define R_EXPBUSEN1 0x87
#define R_EXPBUSEN2 0x88
#define R_EXPBUSEN3 0x89
#define R_EXPBUSPROP 0x8A
#define R_ALTROM 0x8C
#define R_128MEMMAP 0x8E
#define R_MEMMAPMOD 0x8F
#define R_PIGPIOOUTEN0 0x90
#define R_PIGPIOOUTEN1 0x91
#define R_PIGPIOOUTEN2 0x92
#define R_PIGPIOOUTEN3 0x93
#define R_PIGPIO0 0x98
#define R_PIGPIO1 0x99
#define R_PIGPIO2 0x9A
#define R_PIGPIO3 0x9B
#define R_PIPEREN 0xA0
#define R_PII2SCTL 0xA2
#define R_PII2SDIV 0xA3
#define R_ESPGPIOOUTEN 0xA8
#define R_ESPGPIO 0xA9
#define R_EXTKEY0 0xB0
#define R_EXTKEY1 0xB1
#define R_RESVD 0xFF

/* next ports */
__sfr __at 0x0b pZ80DMA;
__sfr __at 0x0f pDACB;
__sfr __at 0x1f pDACA;
__sfr __at 0x1f pKempJoy1;
__sfr __at 0x1f pMFDis;
__sfr __at 0x1f pMF128_12Dis;
__sfr __at 0x37 pKempJoy2;
__sfr __at 0x3f pDACA2;
__sfr __at 0x3f pMF128_2Dis;
__sfr __at 0x3f pMFPlus3En;
__sfr __at 0x4f pDACC;
//pSprtPal = $53
__sfr __at 0x57 pSprtAttr;
__sfr __at 0x5b pSprtPat;
__sfr __at 0x5f pDACD;
__sfr __at 0x6b pZXNDMA;
__sfr __at 0x9f pMFEn;
__sfr __at 0x9f pMF128_12En;
__sfr __at 0xb3 pDACBC;
__sfr __at 0xbf pMF128_2En;
__sfr __at 0xbf pMFPlus3Dis;
__sfr __at 0xdf pDACAD;
__sfr __at 0xe3 pDivMMCCtl;
__sfr __at 0xe7 pSPICS;
__sfr __at 0xeb pSPIDat;
__sfr __at 0xf1 pDACA1;
__sfr __at 0xf3 pDACB1;
__sfr __at 0xf9 pDACC1;
__sfr __at 0xfb pDACAD2;
__sfr __at 0xfe pULA;
__sfr __at 0xff pTimex;
__sfr __banked __at 0x103b pI2CSCL;
__sfr __banked __at 0x113b pI2CSDA;
__sfr __banked __at 0x123b pL2;
__sfr __banked __at 0x133b pUARTTX;
__sfr __banked __at 0x143b pUARTRX;
__sfr __banked __at 0x153b pUARTCtl;
__sfr __banked __at 0x1ffd pPlus3Mem;
__sfr __banked __at 0x183b pCTCCh0;
__sfr __banked __at 0x193b pCTCCh1;
__sfr __banked __at 0x1a3b pCTCCh2;
__sfr __banked __at 0x1b3b pCTCCh3;
__sfr __banked __at 0x1c3b pCTCCh4;
__sfr __banked __at 0x1d3b pCTCCh5;
__sfr __banked __at 0x1e3b pCTCCh6;
__sfr __banked __at 0x1f3b pCTCCh7;
__sfr __banked __at 0x243b pNextReg;
__sfr __banked __at 0x253b pNextDat;
__sfr __banked __at 0x303b pSprtSlt;
__sfr __banked __at 0x7ffd p128Mem;
__sfr __banked __at 0xbf3b pULAPlusReg;
__sfr __banked __at 0xbffd pAYDat;
__sfr __banked __at 0xdffd p128Mem2;
__sfr __banked __at 0xeff7 pPent1MMem;
__sfr __banked __at 0xfadf pKempMouBut;
__sfr __banked __at 0xfbdf pKempMouX;
__sfr __banked __at 0xff3b pULAPlusDat;
__sfr __banked __at 0xffdf pKempMouY;
__sfr __banked __at 0xfffd pAYReg;

#define GETNEXTREG(R) (pNextReg=(R), pNextDat)
#define SETNEXTREG(R, V) (pNextReg=(R), pNextDat=(V))
#endif
