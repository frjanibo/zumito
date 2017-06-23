#include <lib/sprites.h>
#include <lib/motorzxuno.h>
#include <lib/ascii.h>
#include <input.h>
#include <spectrum.h>
#include <stdlib.h>
#include <stdio.h>

#pragma output STACKPTR=65000
int paleta [] ={0,1,7,99,4,116,12,24,13,31,64,132,180,252,221,255};
struct in_UDK k;
unsigned char in_KempcoordX, in_KempcoordY, in_KemprawX, in_KemprawY;

char coor[3];

void main (void)
{
	// Variables globales
	
	int i;

	unsigned char blit[4*8];

	unsigned char y=21;
	unsigned char x=1;
	unsigned char prev_y=y;
    unsigned char prev_x=x;

	int mouse_x = 0;
	int mouse_y = 0;

    //mouse
    unsigned char buttons=0;
    in_MouseKempInit();

    // initialize the struct_in_UDK with keys for use with the keyboard joystick
    k.fire  = in_LookupKey('m');
    k.left  = in_LookupKey('o');
    k.right = in_LookupKey('p');
    k.up    = in_LookupKey('q');
    k.down  = in_LookupKey('a');
	// Inicializamos el modo Radastaniano

	port_out (64571,64);
	port_out (64827,3);

	//port_out (64571,11);
	//port_out( 64827, inp(64827) | 64 );
	
	// Definimos la paleta
	for (i=0;i<16;++i)
	{
		escribe_paleta (i,paleta[i]);
	}

	cls (3);

	// Limite sprites x=60 e y=88
	for (i=0;i<128;i=i+8)
	{
		put_sprite_x8 (sprite_tile3,i,80);
		put_sprite_x8 (sprite_tile1,i,88);
	}
    put_sprite_x8 (sprite_tile2,24,72);
    put_sprite_x8 (sprite_tile3,32,72);
    put_sprite_x8 (sprite_tile4,40,72);

	for(i=0; i<15; i++){
	    plot(i,i,20);
	}

	print ("SPRITE TEST!",20,10);

	put_msprite (spr_caballero,40,30, 16,16);

    get_sprite_x8( blit, x, y);
	while(1)
	{
	        prev_x = x;
	        prev_y = y;

			if( in_KeyPressed(k.up) && y>0) y--;
			if( in_KeyPressed(k.down) && y<88) y++;
			if( in_KeyPressed(k.right) && x<120) x++;
			if( in_KeyPressed(k.left) && x>0) x--;

            wait_int();
            zx_border(1);
            put_sprite_x8( blit,prev_x,prev_y);
            get_sprite_x8( blit, x, y);
            put_sprite_x8 (sprite_tile2,x,y);
            zx_border(7);
	}
}
