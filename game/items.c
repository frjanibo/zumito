
Sprite* createItem(uchar type, Animation* animation, unsigned char x, unsigned char y){
        Sprite* s = Sprite_new(x,y);
        s->id = type;
        s->direction = DIRECTION_UP;
        s->anim = animation;
		sprite_set_flag(s, SPRITE_STATIC_F, 1);
        Sprite_refreshBlit(s);
        return s;
}

void createRandomItem(uchar x, uchar y) {
	uchar item = rand()%3 + ITEM_STAR;
	if( item==ITEM_STAR )
		sprite_safe_add( createItem( ITEM_STAR, anim_star, x, y ) );
	if( item==ITEM_POWERUP )
		sprite_safe_add( createItem( ITEM_POWERUP, anim_powerup, x, y ) );
	if( item==ITEM_SPEEDUP )
		sprite_safe_add( createItem( ITEM_SPEEDUP, anim_speedup, x, y ) );
}
