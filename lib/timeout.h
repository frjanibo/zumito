
typedef struct {
	unsigned long time;
	void (*timeout_function)();
	void* param;
} Timeout;

struct adt_List* Z_TimeoutList;

void init_timeout_system(){
	Z_TimeoutList=adt_ListCreate();
}

void set_timeout(unsigned long delay, void *function, void *param ){
	Timeout* timeout = malloc( sizeof(Timeout) );
	timeout->time = millis() + delay;
	timeout->timeout_function=function;
	if(param!=NULL) timeout->param = param;
	
	adt_ListPushFront(Z_TimeoutList, timeout);
}

void __FASTCALL__ clear_timeouts(){
    
    Timeout *s = adt_ListFirst( Z_TimeoutList );

		while(s!=NULL) {
				free(s);
				adt_ListRemove(Z_TimeoutList);
				s = adt_ListCurr(Z_TimeoutList);
		}
}


void check_timeouts() {
	struct adt_ListNode *position;
	uchar state;
	
	unsigned long current_time = millis();
    Timeout *t = adt_ListFirst( Z_TimeoutList );
    
    while(t!=NULL) {
        if( current_time > t->time ){
			// guardamos el estado de la lista
			position = Z_TimeoutList->current;
			state = Z_TimeoutList->state;
			// llamamos a la funcion
			t->timeout_function( t->param );
			// restauramos el estado
			Z_TimeoutList->current = position;
			Z_TimeoutList->state = state;
			free(t);
			adt_ListRemove(Z_TimeoutList);
			t=adt_ListCurr(Z_TimeoutList);
        } else {
			t = adt_ListNext(Z_TimeoutList);
		}
    }
}
