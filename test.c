
#include <input.h>
#include <spectrum.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
HEAPSIZE(256)
#include <lib/zumito.h>
#include <lib/sprites.h>
#include <lib/motorzxuno.h>
#include <lib/ascii.h>



#pragma output STACKPTR=65000
int paleta [] ={0,1,7,99,4,116,12,24,13,31,64,132,180,252,221,255};
struct in_UDK k;
unsigned char in_KempcoordX, in_KempcoordY, in_KemprawX, in_KemprawY;

char coor[3];

void main (void)
{
	// Variables globales

	int i,j,prev_x,prev_y,x,y;
	unsigned int extrablit[16];
	unsigned int blit[16];
	struct Sprites *sprites[2];
	Sprite *spr;

    Sprite *sprite;
    heapinit(256);
    sprite = Sprite_new( sprite_tile2, 20, 20 );
    sprites[0] = sprite;
    sprites[1] = Sprite_new( sprite_tile0, 0, 30 );

    // initialize the struct_in_UDK with keys for use with the keyboard joystick
    k.fire  = in_LookupKey('m');
    k.left  = in_LookupKey('o');
    k.right = in_LookupKey('p');
    k.up    = in_LookupKey('q');
    k.down  = in_LookupKey('a');

	// Inicializamos el modo Radastaniano
	port_out (64571,64);
	port_out (64827,3);
	// Definimos la paleta
    for (i=0;i<16;++i) {
        escribe_paleta (i,paleta[i]);
    }

	// turbo
	//port_out (64571,11);
	//port_out( 64827, inp(64827) | 128 );

    iCurrentScreen = 0;
    cls(6);
    print("3.5MHZ MODE",10,0);
    memcpy(RADAS_SCREEN_ADDR_1,RADAS_SCREEN_ADDR_0, RADAS_SCREEN_NUM_BYTES);
    iCurrentScreen = 1;

/*
    for(i=0; i < 1; i++) {
        spr = *(Sprite) sprites[i];
        get_sprite_x8( spr->blit, spr->x, spr->y);
    }
  */
    get_sprite_x8(blit, sprite->x, sprite->y);

	while(1)
	{
	        sprite->prev_y = sprite->y;
	        sprite->prev_x = sprite->x;

			if( in_KeyPressed(k.up) && sprite->y>0) sprite->y--;
			if( in_KeyPressed(k.down) && sprite->y<88) sprite->y++;
			if( in_KeyPressed(k.right) && sprite->x<120) sprite->x++;
			if( in_KeyPressed(k.left) && sprite->x>0) sprite->x--;
			if( in_KeyPressed(k.fire) ) {
			    wait_int();
			}


            memcpy( extrablit, blit, sizeof(extrablit) );

            get_sprite_x8(blit, sprite->x, sprite->y);
            put_sprite_x8(sprite->pixels, sprite->x, sprite->y);
            radasChangeScreens();
            put_sprite_x8( extrablit, sprite->prev_x, sprite->prev_y);
	}
}
