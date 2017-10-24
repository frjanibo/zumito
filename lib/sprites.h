// sprites.h

extern unsigned char sprite_tile0 [];

#asm
	._sprite_tile0
	DEFB	0x00, 0x00, 0, 0
	DEFB	0x00, 0x99, 0x99, 0
	DEFB	0x00, 0x98, 0x89, 0
	DEFB	0x00, 0x90, 0x09, 0
	DEFB	0x00, 0x90, 0x09, 0
	DEFB	0x00, 0x98, 0x89, 0
	DEFB	0x00, 0x99, 0x99, 0
	DEFB	0,0,0,0

#endasm

extern unsigned char sprite_tile1 [];

#asm
	._sprite_tile1
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68

#endasm

extern unsigned char sprite_tile2 [];

#asm
	._sprite_tile2
	DEFB	58, 187, 187, 170
	DEFB	171, 187, 187, 186
	DEFB	187, 164, 75, 68
	DEFB	164, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68

#endasm

extern unsigned char sprite_tile3 [];

#asm
	._sprite_tile3
	DEFB	170, 170, 170, 170
	DEFB	171, 186, 171, 186
	DEFB	75, 180, 68, 180
	DEFB	75, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68

#endasm

extern unsigned char sprite_tile4 [];

#asm
	._sprite_tile4
	DEFB	170, 187, 187, 163
	DEFB	171, 187, 187, 186
	DEFB	68, 187, 74, 187
	DEFB	68, 75, 68, 171
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68
	DEFB	68, 68, 68, 68

#endasm

extern unsigned char sprite_zulu [];

#asm
	._sprite_zulu
	DEFB	243, 63, 243, 63, 243, 51

#endasm

extern unsigned char sprite_test [];

#asm
	._sprite_test
	DEFB	@11110010,255,255,255,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,187,187,187,255
	DEFB	255,255,255,255,255

#endasm

static unsigned char spr_caballero[] = {
    0x88,
    0x88,
    0x88,
    0x88,
    0x88,
    0x88,
    0x88,
    0x88,
    0x82,
    0x22,
    0x2d,
    0xed,
    0x22,
    0x22,
    0x22,
    0x28,
    0x82,
    0x22,
    0x2e,
    0x3e,
    0x24,
    0x22,
    0x22,
    0x28,
    0x82,
    0x22,
    0x25,
    0x3e,
    0x24,
    0x22,
    0xa2,
    0x28,
    0x82,
    0x22,
    0x25,
    0xa5,
    0x24,
    0xaa,
    0xaa,
    0x28,
    0x82,
    0x22,
    0xee,
    0xee,
    0xda,
    0xaa,
    0xa2,
    0x28,
    0x82,
    0x2e,
    0x5e,
    0xde,
    0xaa,
    0xa4,
    0xa2,
    0x28,
    0x82,
    0x2e,
    0xad,
    0x5a,
    0xaa,
    0x2a,
    0xa2,
    0x28,
    0x82,
    0x2b,
    0x3d,
    0xba,
    0xaa,
    0xba,
    0xa2,
    0x28,
    0x82,
    0x4a,
    0x5e,
    0xab,
    0xbb,
    0xa2,
    0x22,
    0x28,
    0x84,
    0x4a,
    0xae,
    0xaa,
    0xaa,
    0xa2,
    0x22,
    0x28,
    0x84,
    0x2a,
    0xa5,
    0x4a,
    0xaa,
    0xa2,
    0x22,
    0x28,
    0x82,
    0x22,
    0xaa,
    0xaa,
    0x4a,
    0x22,
    0x22,
    0x28,
    0x82,
    0x22,
    0xa2,
    0xaa,
    0x2a,
    0x22,
    0x22,
    0x28,
    0x82,
    0x22,
    0xa2,
    0xaa,
    0x2a,
    0x22,
    0x22,
    0x28,
    0x88,
    0x84,
    0x48,
    0x44,
    0x84,
    0x48,
    0x88,
    0x88
};
