// Created by Jessalyn Wang (jwang456))
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning jwang456's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    
    // test for success
    // test for add
    char test0[] = "1 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + "
                    "1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 "
                    "+ 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + "
                    "1 + 1 + 1 + 1 + ";
    double result0;
    double expected0 = 66;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error: %d\n", error);
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    // test for subtract
    char test1[] = "1 26.518 -";
    double result1;
    double expected1 = -25.518;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("   Success!\n");
    }
    // test for multiply
    char test2[] = "5 2.1 * 2 *";
    double result2;
    double expected2 = 21;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result2 != expected2) {
        printf("   Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("   Success!\n");
    }
    // test for divide
    char test3[] = "5 2 /";
    double result3;
    double expected3 = 2.5;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result3 != expected3) {
        printf("   Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("   Success!\n");
    }
    // compound test
    char test4[] = "2 -1 + 5 * 2 / 1 + 2 2 + +";
    double result4;
    double expected4 = 7.5;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result4 != expected4) {
        printf("   Failed, expected = %f , result = %f\n", expected4, result4);
    } else {
        printf("   Success!\n");
    }
    
    // Error handling tests below
    // I define emptyResult here because I will be using it for all error tests
    // It should never become defined anyway
    double emptyResult;
    // First test: invalid token
    char test5[] = "-. 1 + ";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test5);
    error = RPN_Evaluate(test5, &emptyResult);
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("   Success! The correct error was found: Invalid token\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }
    // Second test: divide by zero
    char test6[] = "2 -0.0000 / ";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test6);
    error = RPN_Evaluate(test6, &emptyResult);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("   Success! The correct error was found: Divide by zero\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }
    // Third test: stack underflow
    char test7[] = "2 1 + *";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test7);
    error = RPN_Evaluate(test7, &emptyResult);
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("   Success! The correct error was found: Stack underflow\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }
    // Fourth test: too many items remain
    char test8[] = "2 2 + 2";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test8);
    error = RPN_Evaluate(test8, &emptyResult);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("   Success! The correct error was found: Too many items remain\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }
    // Fifth test: Stack overflow
    char test9[] = "2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test9);
    error = RPN_Evaluate(test9, &emptyResult);
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("   Success! The correct error was found: Stack overflow\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }
    // Sixth test: Too few items remain
    char test10[] = "";
    printf("Testing RPN_Evaluate with \"%s\"... \n", test10);
    error = RPN_Evaluate(test10, &emptyResult);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("   Success! The correct error was found: Too few items remain\n");
    } else {
        printf("   Failure! error: %d\n", error);
    }

    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "1234\b\b\b\b\b2\b\b3345";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 3345\n");
    BOARD_End();
    while (1);
}


