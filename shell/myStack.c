#include "myStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_STACK_SIZE (4)

void freeStr(MyData myData)
{
    free(*(char **)myData);
}

/* Initialize a stack */
Stack
initial(int eleSize, PfCbFree freefn)
{
	Stack myStack;
	myStack = malloc(sizeof(struct StackRecord));
	if ( myStack == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	myStack->array = malloc(eleSize * MIN_STACK_SIZE);
	if (myStack->array == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	myStack->eleSize = eleSize;
	myStack->loglength = 0; 
	myStack->alloclength = MIN_STACK_SIZE;
    return myStack;
}

/* Dispose the stack*/
void 
dispose(Stack myStack)
{
	empty(myStack);
	free(myStack->array);
	free(myStack);
}

/* Empty the given stack*/
void 
empty(Stack myStack)
{
	if ( myStack->freefn ) {
		int i;
		for ( i = 0; i < myStack->loglength; ++i) {
			myStack->freefn((char *)myStack->array + 
				    i * myStack->eleSize);
		}
	}
	myStack->loglength = 0;
}

/* Return true if the stack is empty*/
int 
isEmpty(Stack myStack)
{
	return myStack->loglength == 0;
}

static void 
stack_grow(Stack myStack)
{
	myStack->alloclength *= 2;
	myStack->array = realloc(myStack->array, 
	                     myStack->alloclength * myStack->eleSize);
}

/* Insert a new data onto stack */
void 
push(Stack myStack, MyData myData)
{
	MyData target;
	if ( myStack->loglength == myStack->alloclength )
		stack_grow(myStack);
	target = (char *)myStack->array + myStack->loglength * myStack->eleSize;
	memcpy(target, myData, myStack->eleSize);
	myStack->loglength++;	
}

/* Delete the top data off the stack */
void 
pop(Stack myStack)
{
	MyData target;
	if ( isEmpty(myStack) ) {
		fprintf(stderr, "Empty stack\n");
		exit(1);
	}
	if ( myStack->freefn ) {
		target = (char *)myStack->array + 
                         (myStack->loglength-1) * myStack->eleSize;
		myStack->freefn(target);
	}
	myStack->loglength--;
}

/* Fetch the top data from the stack */
void 
stack_top(Stack myStack, MyData myData)
{
	void *target = (char *)myStack->array + 
                       (myStack->loglength-1) * myStack->eleSize;
	memcpy(myData, target, myStack->eleSize);
}

/* Fetch and delete the top data from the stack */
void 
top(Stack myStack, MyData myData)
{
	MyData target;
	if ( isEmpty(myStack) ) {
		fprintf(stderr, "Empty stack\n");
		exit(1);
	}
	target = (char *)myStack->array + 
                 (myStack->loglength-1) * myStack->eleSize;
	memcpy(myData, target, myStack->eleSize);
	myStack->loglength--;
}

