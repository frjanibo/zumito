#include <malloc.h>


#define RADAS_SCREEN_ADDR_0 ( ( unsigned int * ) 0x4000U )
#define RADAS_SCREEN_ADDR_1 ( ( unsigned int * ) 0x6000U )
#define RADAS_SIZE_X 128
#define RADAS_SIZE_Y 96
#define RADAS_BITS_SCREEN_WIDTH 6
#define RADAS_SIZE_X2 ( RADAS_SIZE_X >> 1 )
#define RADAS_SCREEN_NUM_BYTES 6144

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int prev_x;
    unsigned int prev_y;
    unsigned int *pixels;
    unsigned int blit[16];
} Sprite;

Sprite *Sprite_new( unsigned char *pixels, unsigned char x, unsigned char y ){
  Sprite *s = malloc( sizeof(Sprite) );
  s->pixels = pixels;
  s->x = x;
  s->prev_x = x;
  s->y = y;
  s->prev_y = y;
  return s;
}