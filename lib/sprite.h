#include <malloc.h>

#define DIRECTION_UP    0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3

#define SPRITE_DESTROY_F 0
#define SPRITE_VISIBLE_F 1
#define SPRITE_STATIC_F 2

typedef struct {
	unsigned char size;
	unsigned char** data;
} Animation;

typedef struct {
    unsigned char id;
    unsigned char x;
    unsigned char y;
    unsigned char prev_x;
    unsigned char prev_y;
    unsigned char speed;

    unsigned char clock;
    unsigned char anim_clock;
    unsigned char direction;
    unsigned char blit_a[32];
    unsigned char blit_b[32];

	Animation* anim;
    unsigned char frame;

    unsigned char life;
    unsigned char flags;

    unsigned char a,b,c; // general use

    void (*customUpdateMethod)();
    void (*onAnimationEnds)();
} Sprite;

Sprite* Sprite_new( unsigned char x, unsigned char y ){
  Sprite* s = malloc( sizeof(Sprite) );
  s->id=0;
  s->x = x;
  s->prev_x = x;
  s->y = y;
  s->prev_y = y;
  s->speed = 0;
  s->clock=0;
  s->life = 1;

  s->frame = 0;
  s->anim = NULL;
  s->anim_clock = 0;
  s->direction = DIRECTION_RIGHT;
  s->customUpdateMethod = NULL;
  s->onAnimationEnds = NULL;
  s->flags=0;
  s->a=0; s->b=0; s->c=0;

  sprite_set_flag(s,SPRITE_VISIBLE_F,1);
  
  return s;
}

void sprite_set_flag(Sprite* s, uchar flag, uchar value) {
	s->flags ^= (-value ^ s->flags) & (1U << flag);
}
unsigned char sprite_get_flag(Sprite* s, uchar flag) {
	return (s->flags >> flag) & 1U;
}

unsigned char Sprite_Collision_Rect( Sprite* a, Sprite* b) {
  if( (a->x+8 > b->x) && ( a->x < b->x+8) ) {
    // collides in X
    if( (a->y+8 > b->y) && ( a->y < b->y+8) ) {
      // collides in Y
      return 1;
    }
  }
  return 0;
}
unsigned char Sprite_Collision_Circle( Sprite* a, Sprite* b) {
	unsigned char delta_x = a->x - b->x;
	unsigned char delta_y = a->y - b->y;
	if(delta_x*delta_x + delta_y*delta_y < 4) {
		return 1;
	} else {
		return 0;
	}
}
unsigned char sprites_count(){
  return adt_ListCount( Z_getSpritesList() );
}
Sprite* Sprite_CollisionList( Sprite* a, struct adt_List* group, unsigned char type ) {
  struct adt_ListNode *position = group->current;
  uchar state = group->state;

  Sprite *collides = NULL;
  Sprite *s = adt_ListFirst( group );

  while(s!=NULL) {
      if( s->id==type && Sprite_Collision_Rect(a,s) ) {
        collides = s;
        break;
      }
      s = adt_ListNext(group);
  }

  group->current = position;
  group->state = state;
  return collides;
}
Sprite* Sprite_CollisionList_AND( Sprite* a, struct adt_List* group, unsigned char type ) {
  struct adt_ListNode *position = group->current;
  uchar state = group->state;

  Sprite *collides = NULL;
  Sprite *s = adt_ListFirst( group );

  while(s!=NULL) {
      if( (s->id&type)!=0 && Sprite_Collision_Rect(a,s) ) {
        collides = s;
        break;
      }
      s = adt_ListNext(group);
  }

  group->current = position;
  group->state = state;
  return collides;
}
void Sprite_refreshBlit( Sprite* s ){
  get_sprite_x8( s->blit_a, s->x, s->y);
  memcpy( s->blit_b, s->blit_a, 32 );
}

void sprite_safe_add( Sprite s ) {
  struct adt_List* group = Z_getSpritesList();
  struct adt_ListNode *position = group->current;
  uchar state = group->state;
  adt_ListPrepend( group, s);
  group->current = position;
  group->state = state;
}

void sprite_update(Sprite *spr, unsigned char delta) {
  spr->prev_y = spr->y;
  spr->prev_x = spr->x;
  spr->clock += delta;
  spr->anim_clock += delta;

    if( spr->customUpdateMethod != NULL ) spr->customUpdateMethod(spr);
    else {
      sprite_anim(spr,30);
      if( sprite_get_flag(spr, SPRITE_STATIC_F)==0) sprite_move(spr);
    }
}

uchar sprite_clock_check( Sprite s, uchar threshold ) {
  if( s->clock < threshold ) return 1;
  s->clock-=threshold;
  return 0;
}

void sprite_anim( Sprite spr, unsigned char speed ) {
  if( spr->anim_clock > speed ) {
    spr->frame++;
    spr->anim_clock-=speed;
  }

  if(spr->frame == spr->anim->size) {
    spr->frame=0;
    if( spr->onAnimationEnds != NULL ) spr->onAnimationEnds(spr);
  }
}

void sprite_move( Sprite spr ) {
  if( spr->speed != 0) {
    if( spr->direction == DIRECTION_UP || spr->direction==DIRECTION_DOWN ) {
      if(spr->direction == DIRECTION_UP ) spr->y -= spr->speed;
      else spr->y += spr->speed;
    } else {
      if(spr->direction == DIRECTION_RIGHT ) spr->x += spr->speed;
      else spr->x -= spr->speed;
    }

    if( (spr->x<=0 || spr->x>=120) || (spr->y<=0 || spr->y>=80) ) {
      if( spr->direction==DIRECTION_RIGHT) spr->direction = DIRECTION_LEFT;
      else if( spr->direction==DIRECTION_LEFT) spr->direction = DIRECTION_RIGHT;
      else if( spr->direction==DIRECTION_UP) spr->direction = DIRECTION_DOWN;
      else if( spr->direction==DIRECTION_DOWN) spr->direction = DIRECTION_UP;
    }

  }
}

void sprites_update( unsigned char delta ){
    struct adt_List *list = Z_getSpritesList();
    Sprite *s = adt_ListFirst( list );
    
    while(s!=NULL) {
        sprite_update(s, delta);
        s = adt_ListNext(list);
    }
}


void sprites_init(){
    struct adt_List *list = Z_getSpritesList();
    unsigned char *current_blit;
    Sprite *spr = adt_ListFirst( list );
    while( spr != NULL ){
      get_sprite_x8( spr->blit_a, spr->x, spr->y);
      memcpy( spr->blit_b, spr->blit_a, 32 );
      spr = adt_ListNext(list);
    }
}

void __FASTCALL__ sprites_draw(){
    struct adt_List *list = Z_getSpritesList();
    Sprite *s = adt_ListFirst( list );
    while(s!=NULL) {
      if( sprite_get_flag(s, SPRITE_DESTROY_F)==0 && sprite_get_flag(s,SPRITE_VISIBLE_F)==1) {
        //put_sprite_x8m(s->frames[s->frame], s->x, s->y);
        put_sprite_x8m(*(s->anim->data+s->frame), s->x, s->y);
      }
      s = adt_ListNext(list);
    }
}

void __FASTCALL__ sprites_store(){
    struct adt_List *list = Z_getSpritesList();
    unsigned char *current_blit;
    Sprite *s = adt_ListFirst( list );
    while(s!=NULL) {
      if(sprite_get_flag(s,SPRITE_STATIC_F) == 0) {
        current_blit = Z_getActiveScreen()==0 ? s->blit_a : s->blit_b;
        get_sprite_x8(current_blit, s->x, s->y);
      }
      s = adt_ListNext(list);
    }
}

void __FASTCALL__ sprites_restore(){
    struct adt_List *list = Z_getSpritesList();
    unsigned char *current_blit;
    Sprite *s = adt_ListFirst( list );
		if(s!=NULL)
    	do sprite_restore(s) while( s = adt_ListNext(list) );
}

void __FASTCALL__ sprites_destroy(){
    struct adt_List *list = Z_getSpritesList();
    Sprite *s = adt_ListFirst( list );

		while(s!=NULL) {
			if(sprite_get_flag(s, SPRITE_DESTROY_F)==1) {
				s->anim = NULL; // el free jode la anim, no se porqué!
				free(s);
				adt_ListRemove(list);
				s = adt_ListCurr(list);
			} else {
				s = adt_ListNext(list);
			}
		}
}

void __FASTCALL__ sprites_destroy_all(){
    struct adt_List *list = Z_getSpritesList();
    Sprite *s = adt_ListFirst( list );

		while(s!=NULL) {
				free(s);
				adt_ListRemove(list);
				s = adt_ListCurr(list);
		}
}


void __FASTCALL__ sprite_restore( Sprite* spr ){
	unsigned char *current_blit;
	current_blit = Z_getActiveScreen()==0 ? spr->blit_a : spr->blit_b;
	if(spr->prev_x&1 == 0){
			//par
			put_sprite_x8_even( current_blit, spr->prev_x>>1, spr->prev_y);
	} else {
			put_sprite_x8( current_blit, spr->prev_x, spr->prev_y);
	}
}
