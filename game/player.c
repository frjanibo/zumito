
void initPlayerData(void){
        k.fire  = in_LookupKey(' ');
        k.left  = in_LookupKey('o');
        k.right = in_LookupKey('p');
        k.up    = in_LookupKey('q');
        k.down  = in_LookupKey('a');

        player = Sprite_new( 8, 8);
        player->id = 1;
        player->anim = anim_player_walk[player->direction];
        
        player->customUpdateMethod = ThePlayerUpdate;
        player->onAnimationEnds = PlayerAnimEnds;
        score=0;
        speedUps = 0;
        powerUps = 0;
        player->life = 3;
}

void unfreeze_enemies(){
	allEnemiesShouldStop = 0;
}
void timeout_invulnerable(Sprite* s) {
	sprite_set_flag(s, SPRITE_INVULNERABLE_F, 0);
	playerFlashes=0;
}
void timeout_playerAppearAfterDeath(Sprite* s) {
	if( s->life > 1 ) s->life--;
	else {
		NEXT_SCREEN = 0;
		return;
	}

	s->x=8*7; s->y=8*3;
	//s->direction=DIRECTION_RIGHT;
	sprite_set_flag(s,SPRITE_VISIBLE_F,1);
	sprite_set_flag(s, SPRITE_INVULNERABLE_F, 1);
	playerDead=0;
	speedUps=0;
	powerUps=0;
	allEnemiesShouldStop=1;
	s->a=0; s->b=0;
	set_timeout( 2000UL, unfreeze_enemies, NULL);
	
	playerFlashes=1;
	timeout_playerFlash(s);
	set_timeout( 2000UL, timeout_invulnerable, s );
}

void timeout_playerFlash(Sprite* s) {
	if( playerFlashes == 1 ) {
		s->flags ^= 1U << SPRITE_VISIBLE_F;
		set_timeout( 80UL, timeout_playerFlash, s);
	} else {
		sprite_set_flag(s, SPRITE_VISIBLE_F, 1);
	}
}


void PlayerAnimEnds(Sprite* s){
	
	if(s->a==1) { // reproducimos la anim de flash 4 veces
		if(s->b++ > 3) {
			s->a++;
			s->b=0;
			s->anim = (Animation*)anim_player_dead; // y cambiamos a la anim de death
		}
	} else
	if(s->a==2) { // cuando acaba la anim de death, ponemos un timeout hasta que el player aparezca de nuevo
		s->a++;
		sprite_set_flag(s, SPRITE_VISIBLE_F, 0);
		set_timeout( 2000UL, timeout_playerAppearAfterDeath, s );
	}
}

void killPlayer(Sprite* spr) {
	spr->a = 1; spr->b=0;
	spr->frame=0;
	spr->anim = (Animation*)anim_player_flash;
	allEnemiesShouldStop=1;
	playerDead = 1;
	spr->speed = 0;
}

void ThePlayerUpdate(Sprite* spr) {
        unsigned char speed_delay = 32 - (speedUps<<1);
        unsigned char anim_speed = 120;
        Sprite* s;

        s=Sprite_CollisionList( spr, Z_getSpritesList(), ENEMY_WEB );
        if( s != NULL && spr->speed!=0 ) {
          speed_delay = speed_delay<<1;
          sprite_anim(s,140);
        }
        
        
        if( sprite_clock_check(spr,speed_delay) ) return;

        if(spr->a == 0) {
			
			if( sprite_get_flag(spr, SPRITE_INVULNERABLE_F) == 0) {
				s=Sprite_CollisionList_AND( spr, Z_getSpritesList(), ENEMY_MORTAL_FLAG );
				if( s!= NULL ) {
					killPlayer(spr);
					return;
				}
			}
			
			s=Sprite_CollisionList_AND( spr, Z_getSpritesList(), ITEM_FLAG );
			if( (s!=NULL) && (s->id & ITEM_FLAG) ) {
				if(s->id==ITEM_SPEEDUP && speedUps < 4) speedUps++;
				if(s->id==ITEM_POWERUP && powerUps < 4) powerUps++;
				score += 15;
				sprite_set_flag(s, SPRITE_DESTROY_F, 1);
			}

			// continuar andando hasta el siguiente tile
			if( (spr->x&7)==0 && (spr->y&7)==0 ) spr->speed = 0;

			
			if( in_KeyPressed(k.right) && Room_canMove(room,spr->x,spr->y, DIRECTION_RIGHT) ) {
					if(spr->direction==DIRECTION_RIGHT) spr->speed=1;
					else spr->direction=DIRECTION_RIGHT;
			} else
			if( in_KeyPressed(k.left) && Room_canMove(room, spr->x,spr->y, DIRECTION_LEFT) ) {
					if(spr->direction==DIRECTION_LEFT) spr->speed=1;
					else spr->direction=DIRECTION_LEFT;
			}
			if( in_KeyPressed(k.up) && Room_canMove(room,spr->x,spr->y, DIRECTION_UP)) {
							if(spr->direction==DIRECTION_UP) spr->speed=1;
							else spr->direction=DIRECTION_UP;
			} else
			if( in_KeyPressed(k.down) && Room_canMove(room,spr->x,spr->y, DIRECTION_DOWN)) {
							if(spr->direction==DIRECTION_DOWN) spr->speed=1;
							else spr->direction=DIRECTION_DOWN;
			}


			if( in_KeyPressed(k.fire) && shoot_cooldown==0 && shoots < 2 + powerUps) {
					s =  (Sprite*)Bullet_new(player);
					if( s ) {
							sprite_safe_add( s );
							shoot_cooldown += 4 + (rand()%3);
							shoots++;
					}
			}
			if( in_KeyPressed( in_LookupKey('1') ) ) {
					s = (Sprite*)createVermin( 8, 72 );
					if( s ) sprite_safe_add( s );
			}
			if( in_KeyPressed( in_LookupKey('2') ) ) {
					s = (Sprite*)createKnight(8, 72 );
					if( s ) sprite_safe_add( s );
			}
			if( in_KeyPressed( in_LookupKey('3') ) ) {
					s = (Sprite*)createBee(8, 72 );
					if( s ) sprite_safe_add( s );

			}
			if( in_KeyPressed( in_LookupKey('4') ) ) {
					s = (Sprite*)createTank(8,72);
					if( s ) sprite_safe_add( s );
			}
			if( in_KeyPressed( in_LookupKey('5') ) ) {
					spr->a = 1; spr->b=0;
					spr->frame=0;
					spr->anim = (Animation*)anim_player_flash;
					allEnemiesShouldStop=1;
					playerDead = 1;
					spr->speed = 0;
					return;
			}
			if( in_KeyPressed( in_LookupKey('0') ) ) {
					NEXT_SCREEN=0;
			}

			spr->anim = anim_player_walk[spr->direction];
		}
        
        if(shoot_cooldown>0) shoot_cooldown--;

        sprite_anim(spr,anim_speed);
        sprite_move(spr);
        if( spr->a==0 && spr->x==spr->prev_x && spr->y==spr->prev_y ) spr->frame=0;
}

Sprite* Bullet_new( Sprite *player ){
        Sprite* bullet = Sprite_new( player->x & 0xFE, player->y & 0xFE );
        bullet->customUpdateMethod = TheBulletUpdate;
        bullet->direction = player->direction;
        bullet->speed = 1;
        bullet->frame = 0;
        bullet->anim = anim_bullet[bullet->direction];

        Sprite_refreshBlit(bullet);

        return bullet;
}

void TheBulletUpdate(Sprite* bullet) {
        Sprite *collides;
        unsigned int points=0;
        unsigned char x = bullet->x;
        unsigned char y = bullet->y;

        while( bullet->clock >= 10) {
                bullet->clock-=10;

                x = (bullet->direction==DIRECTION_RIGHT) ? bullet->x+8 : bullet->x;
                y = (bullet->direction==DIRECTION_DOWN) ? bullet->y+8 : bullet->y;

                if( Tile_isSolid(Room_getTileAt(room, x>>3, y>>3))) {
                        bullet->speed = 0;
                        sprite_set_flag( bullet, SPRITE_DESTROY_F, 1);
                        shoots--;
                        sprite_safe_add( BulletHit_new(bullet) );
                        return;
                }
                sprite_move(bullet);
        }
        
        collides = Sprite_CollisionList_AND( bullet, Z_getSpritesList(), 0xF0 );
		if( collides!=NULL ) {
				bullet->speed = 0;
				sprite_set_flag(bullet, SPRITE_DESTROY_F, 1);
				points = hit_enemy(collides, 1+powerUps);
				if( points == 0 ) {
				  sprite_safe_add( BulletHit_new(bullet) );
				}
				score+=points;
				shoots--;
				return;
		}
}
void GenericDestroyEvent(Sprite* hit) {
	sprite_set_flag(hit, SPRITE_DESTROY_F, 1);
}

Sprite* BulletHit_new( Sprite *bullet ){
        Sprite* hit = Sprite_new( bullet->x , bullet->y  );
        hit->direction = bullet->direction;
        hit->speed = 0;
        hit->anim = anim_bullethit[bullet->direction];
        sprite_set_flag(hit, SPRITE_STATIC_F, 1);
        
        hit->customUpdateMethod = TheBulletHitUpdate;
        hit->onAnimationEnds= GenericDestroyEvent;

        Sprite_refreshBlit(hit);
        return hit;
}

void TheBulletHitUpdate(Sprite* hit) {
        //if( sprite_clock_check(hit,24) ) return;
        sprite_anim(hit,42);
}

void ExplosionUpdate(Sprite* s) {
        //if( sprite_clock_check(s,32) ) return;
        sprite_anim(s,128);
}

Sprite* Explosion_new(Sprite* s){
        Sprite* e = Sprite_new( s->x, s->y );
        e->customUpdateMethod = ExplosionUpdate;
        e->direction = s->direction;
        e->speed = 0;
        sprite_set_flag(e, SPRITE_STATIC_F, 1);
        e->onAnimationEnds= GenericDestroyEvent;
        e->anim = (Animation*)anim_explosion;
        e->frame=0;

        Sprite_refreshBlit(e);
        return e;
}
