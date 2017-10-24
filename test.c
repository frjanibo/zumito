
#include <input.h>
#include <spectrum.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <lib/zumito.h>
#include <lib/sprites.h>
#include <lib/motorzxuno.h>
#include <lib/ascii.h>

#define HPSIZE 8192*2
#define SPRITES_N 32
#define TILES_N 176
HEAPSIZE(HPSIZE)
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
	Tile *tiles[TILES_N];
	Sprite *spr;
	Sprite *sprite;

	heapinit(HPSIZE);

    for(i=0; i < TILES_N; i++){
	    tiles[i] = Tile_new( sprite_tile2, (i%16)*8, (i/16)*8 );
	}

    sprites[0] = Sprite_new( sprite_tile0, 0, 0);

    for(i=1; i < SPRITES_N; i++){
        sprites[i] = Sprite_new( sprite_tile0, (i%16)*8, 18 );
        sprites[i]->speed_x = rand()%2?-1:1;
        sprites[i]->speed_y = rand()%2?-1:1;
    }
    sprite = sprites[0];
    sprite->frames[0] = sprite_tile0;
    sprite->frames[1] = sprite_tile1;
    sprite->frames[2] = sprite_tile2;
    sprite->frames[3] = sprite_tile3;


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
    // rehabilitar modos timex para shadow screen
    port_out(64571,15);
    port_out(64827,0);

	// turbo
	//port_out (64571,11);
	//port_out( 64827, inp(64827) ^ 128 );

    iCurrentScreen = 0;
    fastcls(6);
    for(i=0; i < TILES_N; i++) {
        put_sprite_x8(tiles[i]->pixels, tiles[i]->x, tiles[i]->y);
    }
    print("3.5MHZ MODE",0,88);
    memcpy(RADAS_SCREEN_ADDR_1,RADAS_SCREEN_ADDR_0, RADAS_SCREEN_NUM_BYTES);
    iCurrentScreen = 1;

    for(i=0; i < SPRITES_N; i++) {
        spr = sprites[i];
        get_sprite_x8( spr->blit, spr->x, spr->y);
        memcpy( spr->shadow_blit, spr->blit, 32 );
    }

	while(1)
	{
        // restauramos la pantalla shadow
        for(i=0; i < SPRITES_N; i++) {
            spr = sprites[i];
            put_sprite_x8( spr->shadow_blit, spr->prev_x, spr->prev_y);
            spr->prev_y = spr->y;
            spr->prev_x = spr->x;

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
            //port_out( 64827, inp(64827) ^ 64 );
            port_out( 64827, inp(64827) ^ 128 );
        }

        for(i=0; i < SPRITES_N; i++) {
            memcpy( sprites[i]->shadow_blit, sprites[i]->blit, 32 );
            get_sprite_x8(sprites[i]->blit, sprites[i]->x, sprites[i]->y);
        }
        for(i=0; i < SPRITES_N; i++) {
            spr = sprites[i];
            put_sprite_x8m(spr->frames[spr->frame], sprites[i]->x, sprites[i]->y);
        }

        sprite->frame++;
        if(sprite->frame==4) sprite->frame=0;

        radasChangeScreens();
        //fastcls(6);
	}
}
