uint total, largest;
unsigned char str[6];
extern Sprite* player;

void copyHud() {
	if( Z_getActiveScreen() == 0 ){
			memcopy(RADAS_SCREEN_ADDR_1+(64*88),RADAS_SCREEN_ADDR_0+(64*88), 64*8);
		} else {
			memcopy(RADAS_SCREEN_ADDR_0+(64*88),RADAS_SCREEN_ADDR_1+(64*88), 64*8);
		}
}

void initHUD() {
	put_sprite_x8m(spr_10x6,0, 88);
}

void updateHUD(){
		char i=0;
        unsigned char outputString[8];

        mallinfo( &total, &largest );

		//put_sprite_x8m(spr_10x6,0, 88);
		mprint( itoa_10(player->life, str,2), 4,90, 2, 1);
        mprint( itoa_10(score,str,5) ,8,90, 9, 1);
        
        
        //print( itoa_10(adt_ListCount(Z_getSpritesList()),str,2), 24, 90);
        mprint( "WAVE", 48,90, 6,1 );
        mprint( itoa_10(CURRENT_WAVE,str,2), 60, 90, 6,1);
        
        print( itoa_10( largest, str,5), 22, 90);
        
        copyHud();
        
        set_timeout( 1000UL, updateHUD, NULL );
}


