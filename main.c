#ifndef STDIO_H
	#include <stdio.h>
#endif
#include <stdlib.h>

#ifndef NEW_H
	#include "headers/New.h"
#endif
#ifndef LIST_H
	#include "headers/List.h"
#endif
#include <stdarg.h>

int main() {
	void* a = new(List);
	//a.add(1);
	//List myList = newList(0);
	//printf("%d ", myList.size);
	//myList.add(1);
	/*Head = newElement();
	ListSetValue(Head, 1);
	for(int i=0; i<9; i++){
		ListAdd(i+4);
	} 
	printList();
	ListFree();*/
}