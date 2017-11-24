
#define RADAS_SCREEN_ADDR_0 ( ( unsigned int * ) 0x4000U )
#define RADAS_SCREEN_ADDR_1 ( ( unsigned int * ) 0x6000U )
#define RADAS_SIZE_X 128
#define RADAS_SIZE_Y 96
#define RADAS_BITS_SCREEN_WIDTH 6
#define RADAS_SIZE_X2 ( RADAS_SIZE_X >> 1 )
#define RADAS_SCREEN_NUM_BYTES 6144

unsigned long last_step_time = 0UL;
unsigned int delta_time = 0UL;

// Current drawing screen. Initial value is 1 (the one which is not shown))
unsigned char iCurrentScreen = 1;

// The list of the sprites in screen
struct adt_List* Z_SpritesList;

void Z_InitEngine();
struct adt_List* Z_getSpritesList();

void Z_setPalette( unsigned char* );
void Z_turboOn();
void Z_radastanModeOn();

unsigned long __FASTCALL__ millis();
void Z_setActiveScreen( unsigned char );
void Z_getActiveScreen();
void Z_switchScreen();
unsigned int* Z_getWorkingScreenAddress();
unsigned int* Z_getVisibleScreenAddress();
void Z_copyScreenToShadow();

void put_sprite_x8 (unsigned char* posicion, unsigned char x, unsigned char y);
void put_sprite_x8_even (unsigned char *posicion, unsigned char x, unsigned char y);
void put_sprite_x8m (unsigned char *posicion, unsigned char x, unsigned char y);
void get_sprite_x8 (unsigned char *posicion, unsigned char x, unsigned char y);
void fastcls (int color);


#include "lib/timeout.h"
#include "lib/sprite.h"
#include "lib/room.h"
#include "lib/screen.c"
#include "lib/ascii.h"
#include "lib/z.c"
