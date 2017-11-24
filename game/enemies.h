extern Room* room;
uchar ENEMIES_NUMBER = 0;

signed char fast_dist(uchar x1, uchar y1, uchar x2, uchar y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

unsigned char hit_enemy(Sprite* enemy, unsigned char damage){
  if(enemy->life > 0) enemy->life-=damage;
  if(enemy->life==0 && sprite_get_flag(enemy, SPRITE_DESTROY_F)==0) {
    sprite_set_flag(enemy, SPRITE_DESTROY_F, 1);
    sprite_safe_add( Explosion_new(enemy) );
    if(enemy->id < ENEMY_WEB && ENEMIES_NUMBER>0) {
      ENEMIES_NUMBER--;
    }
    return enemy_rewards[ (enemy->id>>4)-1 ];
  }
  if(enemy->id==ENEMY_WEB) enemy->frame=1;
  return 0;
}

void EnemyRandom_Update(Sprite);
void EnemyChaser_Update(Sprite);
Sprite* createBee(unsigned char, unsigned char);
Sprite* createVermin(unsigned char, unsigned char);
Sprite* createKnight(unsigned char, unsigned char);
Sprite* createTank(unsigned char, unsigned char);
void Bee_Update(Sprite);
void Knight_Update(Sprite);
void Tank_Update(Sprite);

Sprite* createBee(unsigned char x, unsigned char y){
        Sprite* s = Sprite_new(x,y);
        s->id = ENEMY_BEE;
        s->direction = DIRECTION_UP;
        s->speed = 1;
        s->anim = anim_bee[s->direction];
        s->customUpdateMethod = Bee_Update;

        Sprite_refreshBlit(s);
        return s;
}

void Bee_Update(Sprite s) {
	
  if(allEnemiesShouldStop) return;
        sprite_anim(s,120);
        if( sprite_clock_check(s,38) ) return;
        RandomBehaviour(s);
        s->anim = anim_bee[s->direction];
        sprite_move(s);
}

void Vermin_Update(Sprite s) {
	if(allEnemiesShouldStop) return;
	sprite_anim(s,120);
	if( sprite_clock_check(s,80) ) return;
	RandomBehaviour(s);
	s->anim = anim_vermin[s->direction];
	
	sprite_move(s);
}

Sprite* createVermin(unsigned char x, unsigned char y){
        Sprite* s = Sprite_new( x,y);
        s->id = ENEMY_VERMIN;
        s->direction = DIRECTION_UP;
        s->speed = 1;
        s->anim = anim_vermin[s->direction];
        s->customUpdateMethod = Vermin_Update;

        Sprite_refreshBlit(s);
        return s;
}

Sprite* createKnight(unsigned char x, unsigned char y){
	Sprite* s = Sprite_new( x,y);
	s->id = ENEMY_KNIGHT;
	s->direction = DIRECTION_UP;
	s->speed = 1;
	s->anim = anim_knight[s->direction];
	s->customUpdateMethod = Knight_Update;

	Sprite_refreshBlit(s);
	return s;
}

void Knight_Update(Sprite s) {
	if(allEnemiesShouldStop) return;
  sprite_anim(s,120);
  if( sprite_clock_check(s,60) ) return;
  if( fast_dist(s->x>>3, s->y>>3, player->x>>3, player->y>>3) > 6 ) {
    ChaserBehaviour(s);
  } else {
    RandomBehaviour(s);
  }
  s->anim = anim_knight[s->direction];
  sprite_move(s);
}


void Tank_Update(Sprite s) {
  Sprite* web;
  if(allEnemiesShouldStop) return;
        sprite_anim(s,120);
        if( sprite_clock_check(s,60) ) return;
        RandomBehaviour(s);
        s->anim = anim_tank[s->direction];
        
        if( (rand()&31) == 0 ){
          if( sprites_count()<32 && Sprite_CollisionList( s, Z_getSpritesList(), ENEMY_WEB ) == NULL) {
            web = createWeb(s->x,s->y);
            if( web ) sprite_safe_add( web );
          }
        }
        
        sprite_move(s);
}

Sprite* createTank(unsigned char x, unsigned char y){
        Sprite* s = Sprite_new(x,y);
        s->id = ENEMY_TANK;
        s->direction = DIRECTION_UP;
        s->speed = 1;
        s->anim = anim_tank[s->direction];
        s->life=4;
        s->customUpdateMethod = Tank_Update;

        Sprite_refreshBlit(s);
        return s;
}

void Web_Update(Sprite* s){
  if( sprite_clock_check(s,200) ) return;
  s->frame=0;
}
Sprite* createWeb(unsigned char x, unsigned char y){
        Sprite* s = Sprite_new(x,y);
        s->id = ENEMY_WEB;
        s->direction = DIRECTION_UP;
        s->speed = 0;
        sprite_set_flag(s, SPRITE_STATIC_F, 1);
        s->anim = anim_web;
        s->customUpdateMethod = Web_Update;
        s->life=3;

        Sprite_refreshBlit(s);
        return s;
}

void Egg_Update(Sprite* s){
  sprite_anim(s,180);
}
void Egg_AnimationEnds(Sprite* s){
  unsigned char luck;
  Sprite* enemy;
  if(s->a==0) {
    // ponemos los frames del huevo rebotando
    s->anim = anim_egg_bounce;
    s->a++;
  } else
  if(s->a==1) {
	  if(s->b++ > 3){
		  // ha terminado de rebotar
		  s->anim = anim_egg_break;
		  s->a++;
		  s->b=0;
	  }
  } else
  if( s->a==2 ) {
	  // fin de la cita
	  
	  luck=((rand()&3)+1)<<4;
		if(luck==ENEMY_VERMIN) enemy=createVermin(s->x, s->y);
		else if(luck==ENEMY_KNIGHT) enemy=createKnight(s->x, s->y);
		else if(luck==ENEMY_BEE) enemy=createBee(s->x, s->y);
		else if(luck==ENEMY_TANK) enemy=createTank(s->x, s->y);
		else enemy=createBee(s->x, s->y);
		
		if(enemy!=NULL) {
		  sprite_safe_add(enemy);
		  sprite_set_flag(s, SPRITE_DESTROY_F, 1);
		}
  }
}

Sprite* createEgg(unsigned char x, unsigned char y){
        Sprite* s = Sprite_new((x>>3)<<3, (y>>3)<<3 );
        if(s!=NULL) {
          s->id = ENEMY_EGG;
          s->direction = DIRECTION_UP;
          s->speed = 0;
          sprite_set_flag(s, SPRITE_STATIC_F, 1);
          s->anim = anim_egg_appear;
          s->customUpdateMethod = Egg_Update;
          s->onAnimationEnds = Egg_AnimationEnds;
          s->life=255;

          ENEMIES_NUMBER++;
          Sprite_refreshBlit(s);
        }
        return s;
}

void EnemyRandom_Update(Sprite s) {
	if(allEnemiesShouldStop) return;
	sprite_anim(s,120);
	if( sprite_clock_check(s,60) ) return;
	RandomBehaviour(s);
	s->anim = anim_vermin[s->direction];
	
	sprite_move(s);
}


void RandomBehaviour(Sprite s) {
  unsigned char luck = rand();
  unsigned char cx = s->x >>3;
  unsigned char cy = s->y >>3;
  unsigned char compass[4];
  unsigned char front, left, right;

  if( (s->x&7) + (s->y&7) ==0 ) {

          compass[0] = Tile_isSolid( Room_getTileAt(room,cx,cy-1) ); // 0: up
          compass[1] = Tile_isSolid( Room_getTileAt(room,cx+1,cy) ); // 1: right
          compass[2] = Tile_isSolid( Room_getTileAt(room,cx,cy+1) ); // 2: down
          compass[3] = Tile_isSolid( Room_getTileAt(room,cx-1,cy) ); // 3: left

          front = compass[ s->direction ];
          right = compass[ (s->direction+1)%4 ];
          left  = compass[ (s->direction+3)%4 ];

          if(front!=0) s->speed=0;
          else s->speed=1U;


          if( s->speed==0 ) {
                  // hay que cambiar de direccion porque no podemos seguir de frente
                  if( rand() & 1 ) s->direction= (s->direction+1)%4; //right
                  else s->direction= (s->direction+3)%4; // left

                  s->speed=(compass[s->direction]==0); // ponemos la velocidad a 0/1 segun haya espacio libre o no
          } else {
                  // hay que comprobar si podemos girar
                  if(right==0 || left==0 ) {
                          if( right==0 && left==0 ) {
                                  // podemos girar a cualquier direccion
                                  if( rand() & 1) {
                                          // giramos
                                          if( rand() & 1 ) s->direction= (s->direction+1)%4; //right
                                          else s->direction= (s->direction+3)%4; // left
                                          s->speed=(compass[s->direction]==0); // ponemos la velocidad a 0/1 segun haya espacio libre o no
                                  }
                          } else {
                                  // solo podemos girar en 1 direccion
                                  if( rand() &1){
                                  if(right==0) s->direction=(s->direction+1)%4; //right
                                  if(left==0) s->direction=(s->direction+3)%4; //left
                                  s->speed=1;
                                }
                          }
                  }
          }
  }
}

void ChaserBehaviour(Sprite s) {
  unsigned char cx = s->x >>3;
  unsigned char cy = s->y >>3;
  unsigned char compass[4];
  unsigned char distances[4];
  unsigned char target_x = player->x >> 3;
  unsigned char target_y = player->y >> 3;
  unsigned char selection= s->direction;
  unsigned char closest = 255;

  if( (s->x&7) + (s->y&7) ==0 ) {

          compass[0] = Tile_isSolid( Room_getTileAt(room,cx,cy-1) ); // 0: up
          distances[0] = (compass[0]==0) ? fast_dist(cx,cy-1, target_x,target_y) : 255;

          compass[1] = Tile_isSolid( Room_getTileAt(room,cx+1,cy) ); // 1: right
          distances[1] = (compass[1]==0) ? fast_dist(cx+1,cy, target_x,target_y) : 255;

          compass[2] = Tile_isSolid( Room_getTileAt(room,cx,cy+1) ); // 2: down
          distances[2] = (compass[2]==0) ? fast_dist(cx,cy+1, target_x,target_y) : 255;

          compass[3] = Tile_isSolid( Room_getTileAt(room,cx-1,cy) ); // 3: left
          distances[3] = (compass[3]==0) ? fast_dist(cx-1,cy, target_x,target_y) : 255;

          if( distances[s->direction] < closest ) closest=distances[s->direction];
          if( distances[(s->direction+1)%4] < closest ) {
            closest=distances[(s->direction+1)%4];
            selection = (s->direction+1)%4;
          }
          if( distances[(s->direction+3)%4] < closest ) {
            closest=distances[(s->direction+3)%4];
            selection = (s->direction+3)%4;
          }
          s->direction = selection;


          if(compass[s->direction]!=0)  {
            // giro obligatorio, callejon sin salida!
            s->direction = (s->direction+1)%4;
            s->speed=0;
          } else {
            s->speed=1;
          }

  }

}

void EnemyChaser_Update(Sprite s) {
	if(allEnemiesShouldStop) return;
        sprite_anim(s,120);
        if( sprite_clock_check(s,60) ) { return; }
        ChaserBehaviour(s);
        // TODO: setear la animacion que toca
        sprite_move(s);
}
