
void gameScreenUpdate(){
        last_step_time = millis();
        while(CURRENT_SCREEN==NEXT_SCREEN) {
                delta_time = millis() - last_step_time;
                last_step_time = millis();
                sprites_update( (unsigned char) delta_time ); // call update method on every sprite
                Z_Render();
                waves_update(delta_time);
        }
}

void gameScreenEnter(){
  unsigned char i,j, cell;
  fastcls(1);
  
  CURRENT_WAVE=0;
  ENEMIES_NUMBER=0;
  
  initPlayerData();
  sprite_safe_add( player );

  for(j=0; j<11; j++) {
          for(i=0; i < 16; i++) {
                  cell = Room_getcell(room, i, j);
                  put_sprite_x8_even( room->tileset[cell]->pixels, i<<2, j<<3);
          }
  }
  
  initHUD();
  updateHUD();
  Z_switchScreen();
  memcopy(Z_getWorkingScreenAddress(), Z_getVisibleScreenAddress(), RADAS_SCREEN_NUM_BYTES);  
  sprites_init();
  
  Z_setPalette( paleta );
  Z_setPaletteOffset( PAL_TILESET_Spaceship, 10 );
}

void gameScreenExit(){
	clear_timeouts();
	sprites_destroy_all();
}
