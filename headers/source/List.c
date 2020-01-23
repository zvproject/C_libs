#include <stdlib.h>
#include <stdio.h>
#include "../List.h"
#include "../New.h"
 
	typedef struct Node{
		int data;  //void 
	 	struct Node *next;
	} Node;

struct List{
	//const void* class;
	
	Node *Head;
	Node *Tail; //for convinience
	int size;

	//struct List 
	Node* (*newElement)();
	void (*ListFree)();
	void (*ListSetValue)(Node*, int);
	int (*ListGetValue)(Node*);
	void (*add)(int);
};


static void* List_Init(void* _self){
	struct List* self = _self;

	//Node* node = newElement();
	//self->Head = node;
	//self->Tail = Head;

	self->Head = NULL;
	self->Tail = self->Head;
	self->size = 0;
	return self;
}	

static void* List_Destroy(void* _self){
	struct List *self = _self;
	self->Head = NULL;
	self->Tail = NULL;
	self->size = 0;
	return self;
}

Node* newElement(){
	Node* node = calloc(1, sizeof(Node));
	if (node==NULL){
		fprintf(stderr, "Not enoght mememory!!!");
		return NULL;
	}
	node->next = NULL;
	return node;
}

void add(void* _self, int value){
	struct List *self = _self;
	Node* newNode = newElement();
	newNode->data = value;
	newNode->next = self->Head;
	self->Head = newNode;
	self->size++;
}

/*
void ListFree(struct List *self, ...){
	Node* tmp = NULL;
	while(self->Head != NULL){
		tmp = self->Head->next;
		free(self->Head);
		self->Head = tmp;
	}
}*/

void ListSetValue(Node* node, int value){
	node->data = value;
}

int ListGetValue(Node* node){
	return node->data;
}



//___________________________________
static const struct Class _List = {
	sizeof(struct List),
	List_Init,
	List_Destroy
};

const void *List = & _List;