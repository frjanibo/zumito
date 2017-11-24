
#define ENEMY_VERMIN 0x10
#define ENEMY_KNIGHT 0x20
#define ENEMY_BEE 0x30
#define ENEMY_TANK 0x40
#define ENEMY_WEB 0x50
#define ENEMY_EGG 0x60
unsigned char enemy_rewards[] = {10,20,10,80,0,0};

#include <input.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <adt.h>

#include "game/graphics.h"
#include "game/logo.h"
#include "game/tileset_rocks.h"

#include "lib/z.h"


#include "game/animations.h"
#include "game/player.h"
#include "game/enemies.h"
#include "game/title.h"
#include "game/waves.h"
#include "game/hud.h"
#include "game/game_screen.h"

#define HPSIZE 1024 * 6
HEAPSIZE(HPSIZE)
#pragma output STACKPTR=65535

Room *room;
Screen* screens[2];

void main (void)
{
        // Variables globales
        heapinit(HPSIZE);
        Z_InitEngine();

        screens[0] = Screen_new(0, introScreenUpdate );
        screens[0]->onExit = introScreenExit;
        screens[1] = Screen_new(1, gameScreenUpdate );
        screens[1]->onEnter = gameScreenEnter;
        screens[1]->onExit = gameScreenExit;

        Z_turboOn();
        Z_radastanModeOn();
        Z_setPalette( paleta );
        Z_setPaletteOffset( PAL_TILESET_Rocks, 10 );
        outp(254, 1); // border

        room = Room_new( 1, 16, 11);
        room->cells = room_rocks;
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

        while(1)
        {
                CURRENT_SCREEN = NEXT_SCREEN;
                if(screens[CURRENT_SCREEN]->onEnter) screens[CURRENT_SCREEN]->onEnter();
                screens[CURRENT_SCREEN]->loop();
                if(screens[CURRENT_SCREEN]->onExit) screens[CURRENT_SCREEN]->onExit();
        }
}



void *u_malloc(int size) {
        return malloc(size);        // let malloc take care of things; carry flag set properly by the malloc() call
}

void u_free(void *addr) {
        free(addr);                 // free() deallocates memory allocated by malloc() and ignores addr==0
}
