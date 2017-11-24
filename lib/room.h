#define TILE_F_SOLID 0x01

#include "game/rooms.h"

typedef struct {
    unsigned char id;
    unsigned char flags;
    unsigned char *pixels;
} Tile;

typedef struct {
    unsigned char id;
    unsigned char width;
    unsigned char height;
    unsigned char *cells;
    Tile *tileset;
} Room;


Room* Room_new( unsigned char id, unsigned char width, unsigned char height){
  Room* r = malloc( sizeof(Room) );
  r->id = id;
  r->width = width;
  r->height = height;
  r->tileset = malloc( sizeof(Tile) *16 );

  return r;
}

Room_setTile( Room* r, unsigned char in, uchar flags, uchar* pixels ){
  r->tileset[in]= Tile_new( in, flags, pixels);
}

unsigned char Room_getcell( Room room, unsigned char col, unsigned char row) {
  unsigned char cell = room->cells[ (row*room->width>>1) + (col>>1) ];
  if( (col&1) == 0) cell = cell >> 4;
  return cell & 0x0F;
}

Tile* Room_getTileAt( Room room, unsigned char col, unsigned char row) {
  unsigned char cell = Room_getcell(room,col,row);
  return room->tileset[cell];
}

uchar Room_canMoveRight(Room room, uchar x, uchar y) {
  return !Tile_isSolid(Room_getTileAt(room, (x+8)>>3, y>>3 )) && !Tile_isSolid(Room_getTileAt(room, (x+8)>>3, (y+7)>>3 ));
}
uchar Room_canMoveLeft(Room room, uchar x, uchar y) {
  return !Tile_isSolid(Room_getTileAt(room, (x-1)>>3, y>>3 )) && !Tile_isSolid(Room_getTileAt(room, (x-1)>>3, (y+7)>>3));
}
uchar Room_canMove(Room r, uchar x, uchar y, uchar direction) {
  switch(direction) {
    case DIRECTION_RIGHT:
      return !Tile_isSolid(Room_getTileAt(r, (x+8)>>3, y>>3 )) && !Tile_isSolid(Room_getTileAt(r, (x+8)>>3, (y+7)>>3 ));
    case DIRECTION_LEFT:
      return !Tile_isSolid(Room_getTileAt(r, (x-1)>>3, y>>3 )) && !Tile_isSolid(Room_getTileAt(r, (x-1)>>3, (y+7)>>3));
    case DIRECTION_UP:
      return !Tile_isSolid(Room_getTileAt(r, x>>3, (y-1)>>3 )) && !Tile_isSolid(Room_getTileAt(r, (x+7)>>3, (y-1)>>3 ));
    case DIRECTION_DOWN:
      return !Tile_isSolid(Room_getTileAt(r, x>>3, (y+8)>>3 )) && !Tile_isSolid(Room_getTileAt(r, (x+7)>>3, (y+8)>>3 ));
  }
  return 0;
}

Tile* Tile_new( unsigned char id, uchar flags, unsigned char *pixels ){
  Tile* t = malloc( sizeof(Tile) );
  t->pixels = pixels;
  t->id = id;
  t->flags = flags;
  return t;
}

uchar Tile_isSolid( Tile* t ){
  return t->flags & TILE_F_SOLID;
}
