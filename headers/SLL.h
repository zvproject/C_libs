#ifndef LIST_H
#define LIST_H

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

/*private ot declared here!!!! remove*/

void* giveMem(uint8_t, size_t);
void* linkage(struct Node, struct Node);
struct Node* newNode(int);
/*public*/



#endif

