uchar CURRENT_SCREEN = 0;
uchar NEXT_SCREEN = 0;

typedef struct {
  unsigned char id;
  void (*loop)();
  void (*onEnter)();
  void (*onExit)();
} Screen;

Screen* Screen_new(unsigned char id, void(*loop)(void) ){
  Screen* s = malloc( sizeof(Screen) );
  s->id=id;

  s->loop = loop;
  s->onEnter = NULL;
  s->onExit = NULL;
  return s;
}
