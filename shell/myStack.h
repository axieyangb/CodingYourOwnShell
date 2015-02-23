#ifndef _STACK_H
#define _STACK_H

typedef char *MyData;
typedef void (*PfCbFree)(MyData);

typedef struct StackRecord
{
	MyData	*array;
	int		eleSize;
	int		loglength;
	int		alloclength;
	PfCbFree	freefn;
} *Stack;

void freeStr(MyData myData);

/* Initialize a stack */
Stack initial(int elemsize, PfCbFree freefn);

/* Dispose the stack */
void dispose(Stack myStack);

/* Empty the given stack */
void empty(Stack myStack);

/* Return true if the stack is empty */
int isEmpty(Stack myStack);

/* Insert a new data onto stack */
void push(Stack myStack, MyData myData);

/* Delete the top data off the stack */
void pop(Stack myStack);

/* Fetch the top data from the stack */
void stack_top(Stack myStack, MyData myData);

/* Fetch & Delete the top data from the stack */
void top(Stack myStack, MyData myData);

#endif

