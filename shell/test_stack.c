//
//  test_main.c
//  shell
//
//  Created by xieyangyang on 2/16/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "test_stack.h"
#include "myStack.h"
#include "test_helper.h"
#include "shellerror.h"


char *testName;

void test_Stack()
{
    Stack stack_test;
    stack_test = initial(sizeof(char)*100, freeStr);
    testName="test the stack";
    ASSERT_EQUALS_INT(isEmpty(stack_test), 1, "stack is empty");
    push(stack_test, "first");
    push(stack_test, "second");
    push(stack_test, "third");
    push(stack_test, "fourth");
    push(stack_test, "fifth");
    ASSERT_EQUALS_INT(isEmpty(stack_test), 0, "stack is not empty");
    char * tmp=malloc(sizeof(char)*100);
    stack_top(stack_test,tmp);
    ASSERT_EQUALS_STRING(tmp,"fifth","test_pop_elements");
    pop(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 0, "stack is not empty");
    stack_top(stack_test,tmp);
    ASSERT_EQUALS_STRING(tmp,"fourth","test_pop_elements");
    pop(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 0, "stack is not empty");
    stack_top(stack_test,tmp);
    ASSERT_EQUALS_STRING(tmp,"third","test_pop_elements");
    pop(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 0, "stack is not empty");
    stack_top(stack_test,tmp);
    ASSERT_EQUALS_STRING(tmp,"second","test_pop_elements");
    pop(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 0, "stack is not empty");
    stack_top(stack_test,tmp);
    ASSERT_EQUALS_STRING(tmp,"first","test_pop_elements");
    pop(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 1, "stack is empty");
    push(stack_test, "first");
    push(stack_test, "second");
    push(stack_test, "third");
    push(stack_test, "fourth");
    push(stack_test, "fifth");
    empty(stack_test);
    ASSERT_EQUALS_INT(isEmpty(stack_test), 1, "stack is empty");
    push(stack_test, "first");
    bzero(tmp, 100);
    top(stack_test, tmp);
    ASSERT_EQUALS_STRING(tmp,"first","test_get_top_element_and delete_it");
    ASSERT_EQUALS_INT(isEmpty(stack_test), 1, "stack is empty");
    int i=0;
    for(;i<100;i++)
    {
        bzero(tmp, 100);
        tmp[0]=i;
        push(stack_test,tmp);
    }
    i=99;
    for(;i>=0;i--)
    {
        bzero(tmp, 100);
        stack_top(stack_test,tmp);
        ASSERT_EQUALS_INT((int)(tmp[0]), i, "stack pop one by one");
        pop(stack_test);
        
    }
     ASSERT_EQUALS_INT(isEmpty(stack_test), 1, "stack is empty");
    
    
    TEST_DONE();
}
int main(void){
    testName= "";
    test_Stack();
    return 0;

}



