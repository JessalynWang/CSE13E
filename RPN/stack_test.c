// Created by Jessalyn Wang (jwang456))
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning jwang456's stack test harness: ####\n\n");

    // stacks a that will be used for multiple tests below
    struct Stack emptyStack;
    StackInit(&emptyStack);
    struct Stack stack;
    StackInit(&stack);
    struct Stack uninitialized;
    
    // tests for init
    printf("Does StackInit() initialize appropriately?\n");
    // first test: test if stack itemIndex is correct
    // second test: test if initialized is TRUE
    if (stack.currentItemIndex == -1
            && stack.initialized == TRUE) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    // tests for push
    printf("Does StackPush() push appropriately?\n");
    
    double val = 2.2;
    int expectedIndex = 0;
    // first test: if all the items in stack are correct
    // second test: if uninitialized returns standard error
    if (StackPush(&stack, val) == SUCCESS
            && stack.currentItemIndex == expectedIndex
            && stack.stackItems[stack.currentItemIndex] == val
            && StackPush(&uninitialized, val) == STANDARD_ERROR) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    // tests for pop
    printf("Does StackPop() pop appropriately?\n");
    
    double returnVal;
    expectedIndex = -1;
    // first test if stack pops correctly
    // second test: if error returns correctly
    if (StackPop(&stack, &returnVal) == SUCCESS
            && stack.currentItemIndex == expectedIndex
            && returnVal == val
            && StackPop(&uninitialized, &returnVal) == STANDARD_ERROR) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    // tests for isempty
    printf("Does StackIsEmpty() work appropriately?\n");
    
    StackPush(&stack, val);
    // first test: if the empty stack returns true
    // second test: if the not empty stack returns false
    if (StackIsEmpty(&emptyStack) == TRUE
            && StackIsEmpty(&stack) == FALSE) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    // tests for isfull
    printf("Does StackIsFull() work appropriately?\n");
    
    // below loop fills the stack until it is full
    // iterates 19 times instead of 20 because the stack already has 1 value
    int iter;
    for (iter = 0; iter < STACK_SIZE - 1; iter++) {
        StackPush(&stack, val);
    }
    // first test: if emptystack returns false
    // second test: if the full stack returns true
    if (StackIsFull(&emptyStack) == FALSE
            && StackIsFull(&stack) == TRUE) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    // tests for getsize
    printf("Does StackGetSize() work appropriately?\n");
    
    // expected stack sizes below
    int stackSize = 20;
    int emptyStackSize = 0;
    // first test: check for stack size on a full stack
    // second test: check for stack size on an empty stack
    // if both tests pass, return success
    if (StackGetSize(&stack) == stackSize
            && StackGetSize(&emptyStack) == emptyStackSize) {
        printf(" passed\n");
    } else {
        printf(" failed\n");
    }
    
    BOARD_End();
    
    while (1);
    return 0;
}


