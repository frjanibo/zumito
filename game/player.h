

struct in_UDK k;
Sprite* player;
unsigned long score = 0L;
unsigned char allEnemiesShouldStop = 0;
unsigned char playerDead = 0;
unsigned char speedUps = 0;
unsigned char powerUps = 0;
unsigned char playerFlashes = 0;
unsigned char shoot_cooldown = 0;
unsigned char shoots = 0;

extern Room* room;

void ThePlayerUpdate(Sprite*);
void PlayerAnimEnds(Sprite*);
void TheBulletUpdate(Sprite*);
void TheBulletHitUpdate(Sprite*);
void BulletHit_Destroy(Sprite*);

void timeout_playerFlash(Sprite*);
Sprite* Bullet_new(Sprite *);
Sprite* BulletHit_new(Sprite *);
void initPlayerData(void);
Sprite* Explosion_new(Sprite* s);
