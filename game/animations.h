
/* ----------        PLAYER ANIMATIONS ------------------ */
unsigned char *frames_player_moving_up[] = {spr_2x4, spr_2x5};
unsigned char *frames_player_moving_right[] = {spr_2x0, spr_2x1}; // right
unsigned char *frames_player_moving_down[] = {spr_2x6, spr_2x7}; // down
unsigned char *frames_player_moving_left[] = {spr_2x2, spr_2x3}; // left
unsigned char* frames_player_flashing[] = {spr_9x0, spr_9x1 }; // flash
unsigned char* frames_player_dead[] = { spr_9x2,spr_9x3,spr_9x4,spr_9x5, spr_9x6,spr_9x7 }; // dead

Animation anim_player_up = {2, frames_player_moving_up };
Animation anim_player_down = {2, frames_player_moving_down };
Animation anim_player_left = {2, frames_player_moving_left };
Animation anim_player_right = {2, frames_player_moving_right };
Animation anim_player_dead = {6, frames_player_dead};
Animation anim_player_flash = {2, frames_player_flashing};

Animation* anim_player_walk[] = {anim_player_up, anim_player_right, anim_player_down, anim_player_left };


// BULLET ANIMATIONS
unsigned char* frames_bullet_up[] = {spr_0x2};
unsigned char* frames_bullet_right[] = {spr_0x0};
unsigned char* frames_bullet_down[] = {spr_0x3};
unsigned char* frames_bullet_left[] = {spr_0x1};

Animation anim_bullet_up = {1, frames_bullet_up };
Animation anim_bullet_right = {1, frames_bullet_right };
Animation anim_bullet_down = {1, frames_bullet_down };
Animation anim_bullet_left = {1, frames_bullet_left };
Animation* anim_bullet[] = { anim_bullet_up, anim_bullet_right, anim_bullet_down, anim_bullet_left };

// Bullet Hit
unsigned char* frames_bullethit_up[] = {spr_1x4, spr_1x5 };
unsigned char* frames_bullethit_right[] = {spr_1x0, spr_1x1};
unsigned char* frames_bullethit_down[] = {spr_1x6, spr_1x7};
unsigned char* frames_bullethit_left[] = {spr_1x2, spr_1x3};

Animation anim_bullethit_up = {2, frames_bullethit_up };
Animation anim_bullethit_right = {2, frames_bullethit_right };
Animation anim_bullethit_down = {2, frames_bullethit_down };
Animation anim_bullethit_left = {2, frames_bullethit_left };
Animation* anim_bullethit[] = { anim_bullethit_up, anim_bullethit_right, anim_bullethit_down, anim_bullethit_left };

// Explosion
unsigned char* frames_explosion[] = {spr_0x4, spr_0x5 };
Animation anim_explosion = {2, frames_explosion };


/* ----------------- ENEMIES ANIMATIONS --------------------- */

// VERMIN ---------------
unsigned char* frames_vermin_up[] = {spr_4x0, spr_4x1 };
unsigned char* frames_vermin_right[] = {spr_4x4, spr_4x5 };
unsigned char* frames_vermin_down[] = {spr_4x2, spr_4x3 };
unsigned char* frames_vermin_left[] = {spr_4x6, spr_4x7 };

Animation anim_vermin_up = {2, frames_vermin_up };
Animation anim_vermin_right = {2, frames_vermin_right };
Animation anim_vermin_down = {2, frames_vermin_down };
Animation anim_vermin_left = {2, frames_vermin_left };
Animation* anim_vermin[] = {anim_vermin_up,anim_vermin_right,anim_vermin_down,anim_vermin_left};

// KNIGHT
unsigned char* frames_knight_up[] = {spr_6x0, spr_6x1 };
unsigned char* frames_knight_right[] = {spr_6x4, spr_6x5 };
unsigned char* frames_knight_down[] = {spr_6x2, spr_6x3 };
unsigned char* frames_knight_left[] = {spr_6x6, spr_6x7 };

Animation anim_knight_up = {2, frames_knight_up };
Animation anim_knight_right = {2, frames_knight_right };
Animation anim_knight_down = {2, frames_knight_down };
Animation anim_knight_left = {2, frames_knight_left };
Animation* anim_knight[] = {anim_knight_up,anim_knight_right, anim_knight_down, anim_knight_left};

// TANK
unsigned char* frames_tank_up[] = {spr_7x0, spr_7x1 };
unsigned char* frames_tank_right[] = {spr_7x4, spr_7x5 };
unsigned char* frames_tank_down[] = {spr_7x2, spr_7x3 };
unsigned char* frames_tank_left[] = {spr_7x6, spr_7x7 };

Animation anim_tank_up = {2, frames_tank_up };
Animation anim_tank_right = {2, frames_tank_right };
Animation anim_tank_down = {2, frames_tank_down };
Animation anim_tank_left = {2, frames_tank_left };
Animation* anim_tank[] = { anim_tank_up, anim_tank_right, anim_tank_down, anim_tank_left };

// BEE
unsigned char* frames_bee_up[] = {spr_5x0, spr_5x1 };
unsigned char* frames_bee_right[] = {spr_5x4, spr_5x5 };
unsigned char* frames_bee_down[] = {spr_5x2, spr_5x3 };
unsigned char* frames_bee_left[] = {spr_5x6, spr_5x7 };

Animation anim_bee_up = {2, frames_bee_up };
Animation anim_bee_right = {2, frames_bee_right };
Animation anim_bee_down = {2, frames_bee_down };
Animation anim_bee_left = {2, frames_bee_left };
Animation* anim_bee[] = { anim_bee_up, anim_bee_right, anim_bee_down, anim_bee_left };

// WEB
unsigned char* frames_web[] = { spr_0x6, spr_0x7 };
Animation anim_web = {2, frames_web };

// EGG
unsigned char* frames_egg_appear[] = {spr_8x0, spr_8x1, spr_8x2, spr_8x3};
unsigned char* frames_egg_bounce[] = {spr_8x2, spr_8x3};
unsigned char* frames_egg_break[] = {spr_8x4, spr_8x5, spr_8x6, spr_8x7};
Animation anim_egg_appear = {4, frames_egg_appear};
Animation anim_egg_bounce = {2, frames_egg_bounce};
Animation anim_egg_break  = {4, frames_egg_break};
