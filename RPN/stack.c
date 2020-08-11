// Created by Jessalyn Wang (jwang456))
// Include standard libraries below
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// include CSE13 helper library
#include "BOARD.h"
// include user library
#include "stack.h"

/**
 * This function initializes the stack. For a statically allocated stack such
 * as this, this means initializing currentItemIndex to -1 and setting
 * initialized to TRUE.
 * @param:  *stack, a pointer to a stack which is modified in place.
 */
void StackInit(struct Stack *stack)
{
    // -> sets the stack's variables to their respective values
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
    
}

/**
 * Pushes a value onto the stack.  The stack index is incremented, and the passed value
 * is placed on top of the stack
 * @param:  *stack, a pointer to a stack, which is read and modified in place
 * @param:  value, the value to push.
 * @return: SUCCESS if the stack is modified successfully
 *          STANDARD_ERROR if the stack isn't initialized, or is full.
 * Note that SUCCESS and STANDARD_ERROR are defined in BOARD.h.
 */
int StackPush(struct Stack *stack, double value)
{
    int maxIndex = STACK_SIZE - 1; // if the stack is full, current index should be 19
    if (stack->initialized && (stack->currentItemIndex < maxIndex)) {
        // increase the pointer value so it moves to the next spot in the stack
        stack->currentItemIndex++;
        // sets the value
        stack->stackItems[stack->currentItemIndex] = value;
        return SUCCESS;
    }
    // if the if statement does not happen something is wrong, return error
    return STANDARD_ERROR;
}

/**
 * Pop an element off of a stack.   The popped value is passed out by reference, and the 
 * stack index is decremented.  
 * @param:  *stack, a pointer to a stack, which is read and modified in place
 * @param:  *value, pointer to a double which stores the popped value.
 * @return: SUCCESS if the stack is modified successfully
 *          STANDARD_ERROR if the stack isn't initialized, or is empty.
 *
 * NOTE: When trying to return the output into the value variable, you'll need
 * to write it with an extra asterisk, like:
 *   *value = 7.0;
 * This is because "value" is a pointer. K&R 5.1-5.2 should explain this practice of "passing by reference". 
 */
int StackPop(struct Stack *stack, double *value)
{
    int minIndex = 0; // if the stack isn't empty, the index of the stack is at least 0
    if (stack->initialized && (stack->currentItemIndex >= minIndex)) {
        // set the value equal to the value at the top of the stack
        *value = stack->stackItems[stack->currentItemIndex];
        // decrement the stack indexer, essentially "deleting" value
        stack->currentItemIndex--;
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * This function checks for whether the stack is empty or not. In this simple
 * case this merely checks if the currentItemIndex == -1. 
 * @param:  *stack, a pointer to a stack
 * @return: TRUE if stack is initialized and empty
 *          FALSE if the stack isn't initialized, or is not empty.
 * Note that TRUE and FALSE are defined in BOARD.h.
 */
int StackIsEmpty(const struct Stack *stack)
{
    int empty = -1;
    // if the current item index is -1, it is an indication the stack is empty
    if (stack->initialized && stack->currentItemIndex == empty) {
        return TRUE;
    } 
    return FALSE;
}

/**
 * This function checks for whether the stack is empty or not. For this simple
 * implementation that is merely if the currentItemIndex == STACK_SIZE - 1. 
 * @param:  *stack, a pointer to a stack
 * @return: TRUE if the stack is full and FALSE if not.
 *          Also returns FALSE if the stack isn't initialized.
 */
int StackIsFull(const struct Stack *stack)
{
    // if the stack currentItemIndex is 19, it is an indication it is full
    if (stack->initialized && stack->currentItemIndex == STACK_SIZE - 1) {
        return TRUE;
    }
    return FALSE;
}

/**
 * Returns the current size of the stack in terms of how many active elements
 * are in it. 
 * @param:  *stack, a pointer to a stack
 * @return: SIZE_ERROR for uninitialized stacks, 
 *          the number of elements in the stack for initialized stacks, otherwise. 
 *          Note that SIZE_ERROR is declared in the BOARD.h header file.
 */
int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized) {
        // add one to get the number of elements b/c indexing starts at 0
        return stack->currentItemIndex + 1;
    }
    return SIZE_ERROR;
}


