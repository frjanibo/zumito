
void gameScreenUpdate(){
        last_step_time = millis();
        while(CURRENT_SCREEN==NEXT_SCREEN) {
                delta_time = millis() - last_step_time;
                last_step_time = millis();
                sprites_update( (unsigned char) delta_time ); // call update method on every sprite
                Z_Render();
                //waves_update(delta_time);
        }
}

void gameScreenEnter(){
  unsigned char i,j, cell;

  Z_setPalette( paleta );
  Z_setPaletteOffset( PAL_TILESET_Rocks, 10 );
  fastcls(1);
  
  CURRENT_WAVE=0;
  ENEMIES_NUMBER=0;
  
  initPlayerData();
  sprite_safe_add( player);

  iCurrentScreen = 0;
  for(j=0; j<11; j++) {
          for(i=0; i < 16; i++) {
                  cell = Room_getcell(room, i, j);
                  put_sprite_x8_even( room->tileset[cell]->pixels, i<<2, j<<3);
          }
  }
  
  updateHUD(); // esto se llama cada 1 seg, el timeout lo pone la propia funcion

  memcpy(RADAS_SCREEN_ADDR_1,RADAS_SCREEN_ADDR_0, RADAS_SCREEN_NUM_BYTES);
  iCurrentScreen = 1;
  sprites_init();
}

void gameScreenExit(){
	clear_timeouts();
  sprites_destroy_all();
}
