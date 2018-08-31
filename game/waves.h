
unsigned int CURRENT_WAVE = 0;
unsigned char next_wave_settled = 0;

void dropRandomEgg() {
  Tile* tile;
  uchar x=0,y=0;

  do {
    x= rand()&15;
    y= rand()%10;
    tile = Room_getTileAt(room,x,y);
    if(!Tile_isSolid(tile)) break;
  } while(1);

  if( tile!=NULL ) {
    sprite_safe_add( createEgg(x<<3, y<<3) );
  }
}

void create_wave_eggs() {
	uchar i=0;
	
	for(;i<1+CURRENT_WAVE; i++) {
		dropRandomEgg();
	}
	next_wave_settled=0;
}

void waves_update(uchar delta_time){

  if(ENEMIES_NUMBER > 0 || next_wave_settled==1) return;
  
  next_wave_settled=1;
  CURRENT_WAVE++;
  srand(CURRENT_WAVE+delta_time);
  set_timeout( 2000UL, create_wave_eggs, NULL);
}
