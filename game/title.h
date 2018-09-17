
void introScreenExit(){
  uchar i;
  for(i=0; i<26; i++) {
          Z_exchangePaletteColors(paleta, 7,8 );
          Z_exchangePaletteColors(paleta, 3,6 );
          wait_int();
  }
  Z_paletteFadeout();
  fastcls(1);
  Z_switchScreen();
  fastcls(1);
  sleep(1);
}

void introScreenUpdate(){
        unsigned char i=0;
        unsigned long timer = 0L;
        uchar title_text_status = 0;
        uchar bgcolor = 1;

        fastcls(bgcolor);
        Z_switchScreen();
        fastcls(bgcolor);

        for(i=1;i<15;i++) {
          put_sprite_x8(room->tileset[0xD]->pixels, i<<3, 0);
          put_sprite_x8(room->tileset[0xD]->pixels, i<<3, 88);
        }
        for(i=1;i<11;i++) {
          put_sprite_x8(room->tileset[4]->pixels, 0, i<<3);
          put_sprite_x8(room->tileset[4]->pixels, 120, i<<3);
        }
        put_sprite_x8(room->tileset[1]->pixels, 0, 0);
        put_sprite_x8(room->tileset[3]->pixels, 120, 0);
        put_sprite_x8(room->tileset[9]->pixels, 0, 88);
        put_sprite_x8(room->tileset[11]->pixels,120, 88);


        put_sprite_x8m(spr_4x4, 20, 44); // vermin
        put_sprite_x8m(spr_6x4, 20, 55); // knight
        put_sprite_x8m(spr_5x4, 20, 66); // bee
        put_sprite_x8m(spr_7x4, 20, 77); // tank

        put_sprite_x8m(spr_2x0, 72, 44); // human 1
        put_sprite_x8m(spr_3x0, 72, 55); // human 2
        put_sprite_x8m(spr_10x2,72, 66); // power up
        put_sprite_x8m(spr_10x4,72, 77); // speed up

        Z_switchScreen();
        Z_copyScreenToShadow();
		
        for(i=1; i<28; i+=2) {
                Z_switchScreen();
                Z_put_sprite(logo,32,14+(26-i), 64, i);
        }
        
        Z_copyScreenToShadow();

        last_step_time = millis();
        while(CURRENT_SCREEN==NEXT_SCREEN) {
                delta_time = millis() - last_step_time;
                last_step_time = millis();
                if( in_KeyPressed( in_LookupKey('1') ) ) {
                        NEXT_SCREEN=1;
                        break;
                }
                if( in_KeyPressed( in_LookupKey('t') ) ) {
                        Z_exchangePaletteColors(paleta, 10,13 );
                        Z_exchangePaletteColors(paleta, 1,2 );
                }

                if( last_step_time - timer > 2000 ) {
                        timer = last_step_time;
                        if( title_text_status == 0) {
                                mprint("VERMIN",30>>1, 44+2, 9,0);
                                mprint("KNIGHT",30>>1, 55+2, 9,0);
                                mprint("BEE   ",30>>1, 66+2, 9,0);
                                mprint("TANK  ",30>>1, 77+2, 9,0);

                                mprint("HUMAN  ",82>>1, 44+2, 9,0);
                                mprint("HUMAN  ",82>>1, 55+2, 9,0);
                                mprint("POWER UP",82>>1, 66+2, 9,0);
                                mprint("SPEED UP",82>>1, 77+2, 9,0);
                                mprint("A LOCOMALITO(TM) RETROPORT",6,90, 1,0);


                        } else {
                                mprint("10 PTS",30>>1, 44+2, 9,0);
                                mprint("20 PTS",30>>1, 55+2, 9,0);
                                mprint("10 PTS",30>>1, 66+2, 9,0);
                                mprint("80 PTS",30>>1, 77+2, 9,0);

                                mprint("PLAYER 1",82>>1, 44+2, 9,0);
                                mprint("PLAYER 2",82>>1, 55+2, 9,0);
                                mprint("POWER UP",82>>1, 66+2, 9,0);
                                mprint("SPEED UP",82>>1, 77+2, 9,0);
                                mprint("     BY ANARKADE 2017     ",6,90, 2,0);
                        }
                        Z_exchangePaletteColors(paleta, 7,8 );
                        //Z_exchangePaletteColors(paleta, 3,6 );
                        Z_switchScreen();
                        title_text_status= !title_text_status;
                }
        }
}
