#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
/*
#define _ARGS(_0, ...) _0
#define NARG2(...) _ARGS(__VA_ARGS__, 0)
#define _NEWLIST_ARGS_1()
#define _NEWLIST_ARGS_2()

#define newList(...) NEWLIST(newList, __VA_ARGS__)

*/

	struct Node {
		int data;
		struct Node* next;
	};

typedef struct List{
	struct Node* Head;
	struct Node* Current;
	struct Node* Tail;  //save O(n) time for O(1) space
	size_t size;
} List;


/*------------------PRIVATE------------------*/
void* giveMem(uint8_t, size_t);
void* linkage(struct Node, struct Node);
struct Node* newNode(int);
void addLast(List*, int);

//memory wrapper
void* giveMem(uint8_t count, size_t size){
	void* mem = calloc(count, size);
	//any memory alocation problems or features
	return mem;
}

//list linkage
void link(struct Node *node, struct Node *next){
	if (next)
		node->next = next;
}

//new linked node
struct Node* newNode(int data){
	struct Node* node = giveMem(1, sizeof(struct Node)); 
	node->data = data;
	node->next = NULL;
}

void addLast(List* self, int data){
	struct Node* node = newNode(data);
	node->next = NULL;
	link(self->Tail, node);	//self->Tail->next = node;
	self->Tail = node;
	self->size++;
}

/*------------------PUBLIC-------------------*/
//init
List* newList(){
	List* list = giveMem(1, sizeof(List));  //calloc(1, sizeof(List));
	list->size = 0;
	list->Head = NULL;
	list->Tail = NULL;
	list->Current = NULL;
	return list;
}

//destroy
void destroyList(List* self){
	struct Node* node = self->Head;
	while(self->Head!=NULL){
		self->Head = node->next;
		free(node);
		node = self->Head;
	}
	free(self);
}

//add in front
void add(List* self, int data){
	struct Node* node = newNode(data);
	if (!self->Head)
		self->Tail = node;
	link(node, self->Head);
	self->Head = node;
	//node->next = self->Head;

	self->size++;
}

void insert(List* self, int data, int position){
	if (position==0){
		add(self, data);
		return;
	}
	if ((position>self->size-1)||(position<0)){
		addLast(self, data);
		return;
	}
	struct Node *prev = self->Head, *node=NULL;
	node = newNode(data);
	for(int i=0; ++i<position; prev=prev->next);
	link(node, prev->next);
	link(prev, node);
	self->size++;
}

size_t size(List *self){
	return self->size;
}

void removeLast(List *self){

}

void removePosition(List *self, uint8_t position){

}

void changeData(List *self, void *data, uint8_t position){

}

//user defined
void print(int data){
	//int d = (int*)data;
	printf("%d ", data);
}

void printList(List* self, void (*printElement)(int)){
	struct Node* node = self->Head;
	while(node!=NULL){
	//printf("%d ", (int*)node->data);
		printElement(node->data);
		node = node->next;
	}
}

int main() {
	List* list = newList();
	add(list, 1);
	add(list, 2);
	add(list, 3);
	add(list, 0);
	insert(list,0,-1);
	insert(list,8,10);
	insert(list,9,0);
	insert(list,7,1);

	printf("Length: %d\n", size(list));
	printList(list, print);
	destroyList(list);
}



/*
common 
	new 
	free
	length
	add
	insert
	append

	remove
	iremove
	delete
	sort
	search


unique
*/