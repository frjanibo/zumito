#define ENEMY_VERMIN 0x80
#define ENEMY_KNIGHT 0x90
#define ENEMY_BEE 0xA0
#define ENEMY_TANK 0xB0
#define ENEMY_WEB 0x70
#define ENEMY_EGG 0x10
#define ENEMY_MORTAL_FLAG 0x80

#define ITEM_STAR 0x08
#define ITEM_POWERUP 0x09
#define ITEM_SPEEDUP 0x0A
#define ITEM_FLAG 0x08

unsigned char enemy_rewards[16] = {0,10,20,10,80,0,0};

long heap;
/*
#define HPSIZE 1024 * 6
HEAPSIZE(HPSIZE)
*/

#pragma output STACKPTR=65535


#include <input.h>
#include <stdlib.h>
#include <malloc.h>
#include <adt.h>

#include "game/graphics.h"
#include "game/logo.h"
#include "game/tileset_rocks.h"
//#include "game/tileset_spaceship.h"

#include "lib/z.h"

#include "game/animations.h"
#include "game/player.h"
#include "game/items.c"
#include "game/enemies.h"
#include "game/title.h"
#include "game/waves.h"
#include "game/hud.h"
#include "game/game_screen.h"

#include "game/player.c"


Room *room;
Screen* screens[2];


void load_tilesetRocks(Room* room){
	Room_setTile(room, 0, 0x00, TILESET_Rocks_0x0 );
        Room_setTile(room, 1, TILE_F_SOLID, TILESET_Rocks_0x1 );
        Room_setTile(room, 2, TILE_F_SOLID, TILESET_Rocks_0x2 );
        Room_setTile(room, 3, TILE_F_SOLID, TILESET_Rocks_0x3 );
        Room_setTile(room, 4, TILE_F_SOLID, TILESET_Rocks_0x4 );
        Room_setTile(room, 5, TILE_F_SOLID, TILESET_Rocks_0x5 );
        Room_setTile(room, 6, TILE_F_SOLID, TILESET_Rocks_0x6 );
        Room_setTile(room, 7, TILE_F_SOLID, TILESET_Rocks_0x7 );
        Room_setTile(room, 8, TILE_F_SOLID, TILESET_Rocks_1x0 );
        Room_setTile(room, 9, TILE_F_SOLID, TILESET_Rocks_1x1 );
        Room_setTile(room, 0xA, TILE_F_SOLID, TILESET_Rocks_1x2 );
        Room_setTile(room, 0xB, TILE_F_SOLID, TILESET_Rocks_1x3 );
        Room_setTile(room, 0xC, TILE_F_SOLID, TILESET_Rocks_1x4 );
        Room_setTile(room, 0xD, TILE_F_SOLID, TILESET_Rocks_1x5 );
        Room_setTile(room, 0xE, 0, TILESET_Rocks_1x6 );
        Room_setTile(room, 0xF, TILE_F_SOLID, TILESET_Rocks_1x7 );
}
/*
void load_tilesetSpaceship(Room* room){
	Room_setTile(room, 0, 0x00, TILESET_Spaceship_0x0 );
        Room_setTile(room, 1, TILE_F_SOLID, TILESET_Spaceship_0x1 );
        Room_setTile(room, 2, TILE_F_SOLID, TILESET_Spaceship_0x2 );
        Room_setTile(room, 3, TILE_F_SOLID, TILESET_Spaceship_0x3 );
        Room_setTile(room, 4, TILE_F_SOLID, TILESET_Spaceship_0x4 );
        Room_setTile(room, 5, TILE_F_SOLID, TILESET_Spaceship_0x5 );
        Room_setTile(room, 6, TILE_F_SOLID, TILESET_Spaceship_0x6 );
        Room_setTile(room, 7, TILE_F_SOLID, TILESET_Spaceship_0x7 );
        Room_setTile(room, 8, TILE_F_SOLID, TILESET_Spaceship_1x0 );
        Room_setTile(room, 9, TILE_F_SOLID, TILESET_Spaceship_1x1 );
        Room_setTile(room, 0xA, TILE_F_SOLID, TILESET_Spaceship_1x2 );
        Room_setTile(room, 0xB, TILE_F_SOLID, TILESET_Spaceship_1x3 );
        Room_setTile(room, 0xC, TILE_F_SOLID, TILESET_Spaceship_1x4 );
        Room_setTile(room, 0xD, TILE_F_SOLID, TILESET_Spaceship_1x5 );
        Room_setTile(room, 0xE, 0, TILESET_Spaceship_1x6 );
        Room_setTile(room, 0xF, TILE_F_SOLID, TILESET_Spaceship_1x7 );
}
*/
void main (void)
{
        // Variables globales
        //heapinit(HPSIZE);
        mallinit();
        sbrk(57671, 1024*4);
        Z_InitEngine();

        screens[0] = Screen_new(0, introScreenUpdate );
        screens[0]->onExit = introScreenExit;
        screens[1] = Screen_new(1, gameScreenUpdate );
        screens[1]->onEnter = gameScreenEnter;
        screens[1]->onExit = gameScreenExit;

        Z_turboOn();
        Z_radastanModeOn();
        Z_setPalette( paleta );   
        outp(254, 1); // border

        room = Room_new( 1, 16, 11);
        room->cells = room_rocks;
        //load_tilesetSpaceship(room);
        load_tilesetRocks(room);
        //Z_setPaletteOffset( PAL_TILESET_Spaceship, 10 );        
        Z_setPaletteOffset( PAL_TILESET_Rocks, 9 );

        while(1)
        {
            CURRENT_SCREEN = NEXT_SCREEN;
                
            if(screens[CURRENT_SCREEN]->onEnter != NULL) {
				screens[CURRENT_SCREEN]->onEnter();
            }

            screens[CURRENT_SCREEN]->loop();

            if(screens[CURRENT_SCREEN]->onExit != NULL) {
				screens[CURRENT_SCREEN]->onExit();
			}
                
                
        }

}


void *u_malloc(int size) {
        return malloc(size);        // let malloc take care of things; carry flag set properly by the malloc() call
}

void u_free(void *addr) {
        free(addr);                 // free() deallocates memory allocated by malloc() and ignores addr==0
}


