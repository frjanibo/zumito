
#include <input.h>
#include <spectrum.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
HEAPSIZE(1024*8)
#include <lib/zumito.h>
#include <lib/sprites.h>
#include <lib/motorzxuno.h>
#include <lib/ascii.h>

#define SPRITES_N 32

#pragma output STACKPTR=65000
int paleta [] ={0,1,7,99,4,116,12,24,13,31,64,132,180,252,221,255};
struct in_UDK k;
unsigned char in_KempcoordX, in_KempcoordY, in_KemprawX, in_KemprawY;

char coor[3];

void main (void)
{
	// Variables globales

	int i,j,prev_x,prev_y,x,y;
	unsigned int background[RADAS_SCREEN_NUM_BYTES];
	Sprite *sprites[SPRITES_N];
	Sprite *spr;
	Sprite *sprite;
	heapinit(60000);

    sprites[0] = Sprite_new( sprite_tile2, 0, 0);
    for(i=1; i < SPRITES_N; i++){
        sprites[i] = Sprite_new( sprite_tile2, rand()%120, rand()%88);
        sprites[i]->speed_x = rand()%2?-1:1;
        sprites[i]->speed_y = rand()%2?-1:1;
    }
    sprite = sprites[0];

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

    for(i=0; i < SPRITES_N; i++) {
        spr = sprites[i];
        get_sprite_x8( spr->blit, spr->x, spr->y);
        memcpy( spr->shadow_blit, spr->blit, 32 );
    }

	while(1)
	{
        for(i=0; i < SPRITES_N; i++) {

            put_sprite_x8( sprites[i]->shadow_blit, sprites[i]->prev_x, sprites[i]->prev_y);
            sprites[i]->prev_y = sprites[i]->y;
            sprites[i]->prev_x = sprites[i]->x;

            spr = sprites[i];
            spr->x += spr->speed_x;
            if(spr->x==0 || spr->x==120) spr->speed_x *= -1;
            spr->y += spr->speed_y;
            if(spr->y==0 || spr->y==88) spr->speed_y *= -1;
        }

        if( in_KeyPressed(k.up) && sprite->y>0) sprite->y--;
        if( in_KeyPressed(k.down) && sprite->y<88) sprite->y++;
        if( in_KeyPressed(k.right) && sprite->x<120) sprite->x++;
        if( in_KeyPressed(k.left) && sprite->x>0) sprite->x--;
        if( in_KeyPressed(k.fire) ) {
            wait_int();wait_int();wait_int();wait_int();
            port_out (64571,11);
            port_out( 64827, inp(64827) ^ 128 );
        }

        for(i=0; i < SPRITES_N; i++) {
            spr = sprites[i];
            memcpy( spr->shadow_blit, spr->blit, 32 );
            get_sprite_x8(spr->blit, spr->x, spr->y);
        }

        for(i=0; i < SPRITES_N; i++) {
            put_sprite_x8(sprites[i]->pixels, sprites[i]->x, sprites[i]->y);
        }
        radasChangeScreens();
	}
}
