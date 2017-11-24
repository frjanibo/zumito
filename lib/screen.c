uchar CURRENT_SCREEN = 0;
uchar NEXT_SCREEN = 0;

typedef struct {
  uchar id;
  void (*loop)();
  void (*onEnter)();
  void (*onExit)();
} Screen;

Screen* Screen_new(uchar id, void(*loop)() ){
  Screen* s = malloc( sizeof(Screen) );
  s->id=id;

  s->loop = loop;
  s->onEnter = NULL;
  s->onExit = NULL;
  return s;
}
