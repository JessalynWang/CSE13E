// Created by Jessalyn Wang (jwang456))
// Include standard libraries below
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// include CSE13 helper library
#include "BOARD.h"
// include user library
#include "stack.h"
#include "rpn.h"

// helper functions defined here
int TokenCheck(char * token);

// 0 will be used for many different purposes, such as the first index of a string
// or other things a constant for the divide by 0 error
#define ZERO_CONSTANT 0

/* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate rpn_error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
int RPN_Evaluate(char * rpn_string, double * result)
{
    // get the first token
    char* token = strtok(rpn_string, " ");
    // variable uses: currentToken will be the float version of token
    // firstVal will be the first object popped from stack
    // secondVal will be the second item popped from stack
    double currentToken, firstVal, secondVal;
    // create and initiate an empty stack here
    struct Stack stack = {};
    StackInit(&stack);
    // to do operations we need at least two values on the stack
    // at the end of the operation handling we want one value to be on the stack
    // thus, minStackLen and idealLen are defined respectively
    int minStackLen = 2, idealLen = 1;
    
    // if the token is not null, some operation needs to be done still
    while (token != NULL) {
        // if the tokenCheck function says it is not a number, we need to check if the
        // invalid token is an operand
        if (!TokenCheck(token)) {
            if (strlen(token) != 1) {
                // all operands are single chars, so if the length is > 1 the token is invalid
                return RPN_ERROR_INVALID_TOKEN;
            }
            // otherwise, we know the token has length one and we look at the first char to compare
            // the switch does each mathematical operation based on the token it finds
            // in cases that order matters, secondVal, which as pushed first but popped second, comes
            // first in the hierarchy 
            switch (token[ZERO_CONSTANT])
            {
                case '+':
                    if (StackGetSize(&stack) >= minStackLen) {
                        StackPop(&stack, &firstVal);
                        StackPop(&stack, &secondVal);
                        StackPush(&stack, firstVal + secondVal);
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    break;
                case '-':
                    if (StackGetSize(&stack) >= minStackLen) {
                        StackPop(&stack, &firstVal);
                        StackPop(&stack, &secondVal);
                        StackPush(&stack, secondVal - firstVal);
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    break;
                case '*':
                    if (StackGetSize(&stack) >= minStackLen) {
                        StackPop(&stack, &firstVal);
                        StackPop(&stack, &secondVal);
                        StackPush(&stack, firstVal * secondVal);
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    break;
                case '/':
                    if (StackGetSize(&stack) >= minStackLen) {
                        StackPop(&stack, &firstVal);
                        StackPop(&stack, &secondVal);
                        // if firstVal is 0, we have a divide by 0 error
                        if (firstVal == ZERO_CONSTANT) {
                            return RPN_ERROR_DIVIDE_BY_ZERO;
                        }
                        StackPush(&stack, secondVal / firstVal);
                    } else {
                        return RPN_ERROR_STACK_UNDERFLOW;
                    }
                    break;
                default:
                    // if the token is not an acceptable operand, it is an invalid token
                    return RPN_ERROR_INVALID_TOKEN;
            }
        } else {
            // the token is a valid umber, thus we need to push to stack
            if (StackIsFull(&stack)) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
            currentToken = atof(token);
            StackPush(&stack, currentToken);
        }
        // get the next token
        token = strtok(NULL, " ");
    }
    
    if (StackGetSize(&stack) > idealLen) {
        // if the stack has more than one value, we have too many items
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    } else if (StackGetSize(&stack) < idealLen) {
        // if the stack is empty, we have too many items
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    // otherwise, the stack has just what we need and we put it into result and return 0
    StackPop(&stack, result);
    return RPN_NO_ERROR;
    
}

/**
 * This function should read through an array of characters, checking for backspace characters. 
 * When it encounters a backspace character, it eliminates the backspace, the preceeding character
 * (if such a character exists), and shifts all subsequent characters as appropriate.
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings of at least 255 length.
 * 
 * */
int ProcessBackspaces(char *rpn_sentence)
{
    // variable usage: innerIter is the iterator for the for loop
    // oneDel and twoDel are numbers we need to shift the iterators by
    // flag is to tell when we have reached the backspace character
    // currentLen is the length of the string
    int innerIter, oneDel = 1, twoDel = 2;;
    int flag = 0, iter = 0, currentLen = strlen(rpn_sentence);
    
    // while we have not reached the end of the string, we need to check for backspaces
    while (iter < currentLen) {
        // if we find a backspace, there are two cases: there is/isn't something to delete
        if (rpn_sentence[iter] == '\b') {
            if (iter != ZERO_CONSTANT) {
                // this means there is something to delete
                for (innerIter = 0; innerIter + flag < currentLen; innerIter++) {
                    // loop overwrites the string
                    if (innerIter == iter - oneDel) {
                        // if we reach the character we want to delete, skip past it by changing flag
                        flag = twoDel;
                    }
                    rpn_sentence[innerIter] = rpn_sentence[innerIter + flag];
                }
                flag = 0;
                // change currentlen to reflect the deletion
                currentLen = currentLen - twoDel;
                // decrement iter to check the correct next character
                iter--;
                // put a null where the string should stop
                rpn_sentence[innerIter] = '\0';
            } else {
                // case for nothing to be deleted
                // iterate and simply skip the first value, which is a backspace
                for (innerIter = 1; innerIter < currentLen; innerIter++) {
                    rpn_sentence[innerIter - oneDel] = rpn_sentence[innerIter];
                }
                rpn_sentence[innerIter - oneDel] = '\0';
                currentLen--;
            }
        } else {
            iter++;
        }
    }
    // return the length of the string
    return strlen(rpn_sentence);
}

/**
 * If atof return 0.0, there could be an error or the number passed in could just be 0!
 * This function checks if the token is really a number before doing atof
 * 
 */
int TokenCheck(char * token)
{
    // intcounter and period counter check for floats and ints
    int iter, intCounter = 0, periodCounter = 0;
    // posNeg = -, posDec = ., firstInt = 0, lastInt = 9
    char posNeg = 0x2D, posDec = 0x2E, firstInt = 0x30, lastInt = 0x39;
    
    //loop through the token
    for (iter = 0; iter < strlen(token); iter++) {
        // if the char is not between 0 and 9
        if (!(token[iter] >= firstInt && token[iter] <= lastInt)) {
            // if the char is - and the first char, it is okay
            if (token[iter] == posNeg && (iter == ZERO_CONSTANT)) {
                continue;
            }
            // if the char is a decimal and it is the first one it is okay
            if (token[iter] == posDec && (periodCounter == ZERO_CONSTANT)){
                periodCounter++;
                continue;
            }
            // else, the token is not a number and we return false
            return FALSE;
        } else {
            // if the token is an int and we tally that
            intCounter++;
        }
    }
    // if everything passes and there existed ints in the token, we return true
    if (intCounter >= 1) {
        return TRUE;
    }
    return FALSE;
}
