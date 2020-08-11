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

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60
// None of the return strings will be longer than length 60, if one is, we have error # 7
#define ERROR_7 7

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int returnVal = 0;
    char printString[MAX_INPUT_LENGTH];

    printf("Welcome to jwang456'S RPN calculator.  Compiled on %s %s\n", __DATE__, __TIME__);
    while (1) {
        // returnVal is a flag that will indicate the more than 60 characters error
        returnVal = 0;

        printf("Enter floats and + - / * in RPN format: ");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        // finds and clears out the newline character
        int iter;
        for (iter = 0; iter < strlen(rpn_sentence); iter++) {
            if (rpn_sentence[iter] == '\n') {
                rpn_sentence[iter] = '\0';
            }
        }
        // if the value at index 60 is not null, that means the string is at least
        // 61 characters long and is an error
        if (strlen(rpn_sentence) > MAX_INPUT_LENGTH 
                && rpn_sentence[MAX_INPUT_LENGTH] != '\0') {
            rpn_sentence[MAX_INPUT_LENGTH] = '\0';
            returnVal = ERROR_7;
            for (iter = 0; iter < strlen(rpn_sentence); iter++) {
                rpn_sentence[iter] = '\0';
            }
            while (getchar() != '\n');
        }
        // as long as the string is not too long, we will run it with RPN_Evaluate
        if (returnVal != ERROR_7) {
            ProcessBackspaces(rpn_sentence);
            returnVal = RPN_Evaluate(rpn_sentence, &result);
        }

        // switch statement takes the return of evaluate and determines what to print based
        // on the return
        switch (returnVal) {
            case 1:
                sprintf(printString, "  ERROR: No more room on stack.\n");
                break;
            case 2:
                sprintf(printString, "  ERROR: Not enough operands before the operator.\n");
                break;
            case 3:
                sprintf(printString, "  ERROR: Invalid character in RPN string.\n");
                break;
            case 4:
                sprintf(printString, "  ERROR: Invalid RPN calculation-divide by zero.\n");
                break;
            case 5:
                sprintf(printString, "  ERROR: Invalid RPN calculation-no items on stack.\n");
                break;
            case 6:
                sprintf(printString, "  ERROR: Invalid RPN calculation-too many items on stack.\n");
                break;
            case 7:
                sprintf(printString, "  ERROR: Input string exceeds 60 characters.\n");
                break;
            default:
                sprintf(printString, "  Result = %lf\n", result);
                break;
        }

        printf("%s\n", printString);

    }

    while (1);
}
