
typedef struct znode {
  void *data;
  struct znode* next;
} znode;

typedef struct zlist {
  struct znode* head;
} zlist;


unsigned char zlist_push( zlist* list, void *data ) {
	znode* node = list->head;
	znode* newNode = (znode*) malloc( sizeof(znode) );
	
	if(newNode==NULL) {
		return 0;
	}
	newNode->data = data;
	newNode->next = NULL;
	
	if(list->head == NULL) {
		// es el primer elemento
		list->head = newNode;
		return 1;
	}
	
	while( node->next != NULL) {
		node = node->next;
	}
	node->next = newNode;
	
	return 1;
}

unsigned char zlist_count( zlist* list ){
	znode* node = list->head;
	unsigned char c=0;
	
	while( node != NULL ) {
		c++;
		node = node->next;
	}
	return c;
}

znode* zlist_next( znode* n ) {
	return n->next;
}

znode* zlist_getFirst( zlist* l ) {
	return l->head;
}

znode* zlist_remove( zlist* list, znode* node) {
	znode* cur = list->head;
	
	if(node==list->head) {
		list->head = node->next;
		free(node);
		return list->head;
	}
	
	while( cur->next != node) {
		//buscamos el elemento previo
		cur=cur->next;
	}
	cur->next = node->next;

	free(node);
	return cur->next;
}
