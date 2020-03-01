#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "headers/SLL.h"
/*
#define _ARGS(_0, ...) _0
#define NARG2(...) _ARGS(__VA_ARGS__, 0)
#define _NEWLIST_ARGS_1()
#define _NEWLIST_ARGS_2()

#define newList(...) NEWLIST(newList, __VA_ARGS__)

*/

//adding elements
void add(List*, int); // add to beggining of the list
void insert(List*, int, int); // insert value to specific position in list
void extend(List*, int); // add to the end of the list

//size of the list
inline static size_t size(List*);

//removing from list
void pop(List*); 		//removing first of the list (Head)
void idelete(List*, int); //???
int delete(List*, const void*); //???? 

void reverse(List*); //reverse list 

//searching in list !require cmp
int search(List*, const void*); //search first ocurance of value
int rsearch(List*, const void*); //serach last ocurance of value
int count(List*, const void*);	//count all ocurance of value
struct Node* (find)(List*, int); //return node from index

//update data of single node
void update(struct Node*, int); //update specific node
void iupdate(List*, int, int); 	//update data by posiiton in the list (0)

//sort list

//swap elements of list

//move through list
static inline void reset(List*); //reset curent to the head
void set(List*, int);			 //set current to position
struct Node* (iterate)(List*);   //return curent and move one step


/*------------------PRIVATE------------------*/
//private get in header for user override
int cmp(const void *p, const void *q){
	int l = *(const int *)p;
	int r = *(const int *)q;
	return (l-r);
}

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

/*------------------PUBLIC-------------------*/
//void delete(List*, int value);

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


/*adding to list*/
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

//add in position
void insert(List* self, int data, int position){
	if (position==0){
		add(self, data);
		return;
	}
	if ((position>self->size-1)||(position<0)){
		extend(self, data);
		return;
	}
	struct Node *prev = find(self, position);
	struct Node *node = newNode(data);
	//for(int i=0; ++i<position; prev=prev->next);
	link(node, prev->next);
	link(prev, node);
	self->size++;
}

//add in tail
void extend(List* self, int data){
	struct Node* node = newNode(data);
	node->next = NULL;
	link(self->Tail, node);	//self->Tail->next = node;
	self->Tail = node;
	self->size++;
}
/*--------------*/

//list size
inline size_t size(List *self) {return self->size;}

/*removing from list*/
//remove element in front
void pop(List *self){
	struct Node* node = self->Head;
	self->Head = node->next;
	free(node);
	self->size--;
}

//remove element by position
void idelete(List *self, int position){

	if (position <= 0){
		pop(self);
		return;
	}
	if (position >= self->size) position = self->size-1;
	struct Node *prev = find(self, position-1); 
	struct Node *node = prev->next;
	printf("%d %d\n", node->data, prev->data);
	prev->next = node->next; //link function
	if (node == self->Tail)	self->Tail = prev;
	free(node);
	self->size--;
}


//remove element by value
//-1 if not found
// index if removed
int delete(List *self, const void* value) {
	struct Node* node = self->Head, *prev = NULL;
	while(node){
		if(cmp(&value, &node->data)!=0){

			node = NULL;
		}		
		node = node->next;
	}		
}	

void reverse(List *self){
	self->Current = self->Head;
	struct Node *prev = NULL, *next = NULL;
	while(self->Current){
		next = self->Current->next;
		self->Current->next = prev;
		prev = self->Current;
		self->Current = next;
	}
	self->Head = prev;
}

void update(struct Node* node, int value){
	node->data = value;
}

void iupdate(List *self, int position, int value){
	update(find(self, position), value);
}



// find first occurance value in list
// add from position ???
int search(List *self, const void* value) {
	struct Node* node = self->Head;
	int i = 0; 
	while(node){
		if (cmp(&value, &node->data)==0)
			return i;
		i++;
		node = node->next;
	}
	return -1;
} // void 

// find last occurance value in list 
int rsearch(List *self, const void* value){
	struct Node* node = self->Head;
	int i = 0, result=-1; 
	while(node){
		if (cmp(&value, &node->data)==0)
			result = i;
		i++;
		node = node->next;
	}
	return result;
}

//count number of occurance in the list
int count(List *self, const void* value){
	struct Node* node = self->Head;
	int i = 0, result=-1; 
	while(node){
		if (cmp(&value, &node->data)==0)
			result++;
		i++;
		node = node->next;
	}
	return result;
}

//find node in List by index
struct Node* (find)(List *self, int position) {
	struct Node *node = self->Head;
	if (position<0)
		position = 0;
	if (position >= self->size)
		position = self->size-1;
	for(int i=0; i<position; i++, node=node->next);
	return node;
}

void sort(List *self){}//????

void swap(struct Node* node1, struct Node* node2){}//?????

struct Node* getPrev(List *self, struct Node* node){
	if (node == self->Head) return NULL;
	if (node == NULL) return NULL;
	struct Node* iter=self->Head;
	for(; iter->next!=node; iter=iter->next);
	return iter;
}

static inline void reset(List *self){self->Current = self->Head;}

void set(List *self, int position){
	self->Current = find(self, position);
}

struct Node* (iterate)(List *self){
	struct Node* node = self->Current;
	if (!self->Current)
		reset(self);
	return node;
}






void printList_i(int data){
	printf("%d ", data);
}
void printList_f(float data){
	printf("%f", data);
}
void printList_c(char data){
	printf("%c", data);
}
void printList_s(char* data){
	printf("%s", &data);
}

void printList(void* data){
	printf("%p", data);
}

#define printList(X) _Generic((X), \
								int: printList_i, \
								float: printList_f, \
								char: printList_c, \
								char*: printList_s, \
								default: printList)(X)

void print(List* self){
	struct Node* node = self->Head;
	while(node!=NULL){
		printList(node->data);
		node = node->next;
	}
}

int main() {
	List* list = newList();
	add(list, 1);
	add(list, 2);
	add(list, 3);
	add(list, 0);
	//delete(list,3);
	//insert(list,0,-1);
	//insert(list,8,10);
	//insert(list,9,0);
	//insert(list,7,1);

	printf("Length: %d\n", size(list));
	print(list);
	printf("\n");
	reverse(list);
	print(list);
	printf("\n");
	destroyList(list);
}

