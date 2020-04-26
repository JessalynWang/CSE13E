/* 
 * 
 * File:   Calculator.c
 * Author: Jessalyn Wang (jwang456@ucsc.edu)
 *
 * Created on April 13, 2020, 2:00 PM
 */
// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Tangent(double operand);
double Round(double operand);
//add more prototypes here

void CalculatorRun(void) {
    printf("\n\nWelcome to Jessalyn's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);


    // Your code here
    char operator;
    double op1, op2, result;
    while (1) {
        printf("\n Enter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,r,q): ");
        scanf(" %c", &operator);
        printf("\n     Character received was: %c\n", operator);

        switch (operator) {
            case '*':
                printf("     Enter the first operand: ");
                //checks if operand is correct
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                printf("     Enter the second operand: ");
                if (scanf(" %lf", &op2) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //calculates result
                result = Multiply(op1, op2);
                //prints accordingly
                printf("     Result of (%f * %f): %f\n", op1, op2, result);
                break;
            case '/':
                printf("     Enter the first operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                printf("     Enter the second operand: ");
                if (scanf(" %lf", &op2) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = Divide(op1, op2);
                //if result is a huge val there is a divide by 0 error
                if (result == HUGE_VAL) {
                    printf("     Divide by 0 error!\n");
                    break;
                }
                printf("     Result of (%f / %f): %f\n", op1, op2, result);
                break;
            case '+':
                printf("     Enter the first operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                printf("     Enter the second operand: ");
                if (scanf(" %lf", &op2) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = Add(op1, op2);
                printf("     Result of (%f + %f): %f\n", op1, op2, result);
                break;
            case '-':
                printf("     Enter the first operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                printf("     Enter the second operand: ");
                if (scanf(" %lf", &op2) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = Subtract(op1, op2);
                printf("     Result of (%f - %f): %f\n", op1, op2, result);
                break;
            case 'm':
                printf("     Enter the first operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                printf("     Enter the second operand: ");
                if (scanf(" %lf", &op2) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = Average(op1, op2);
                printf("     Result of the average of %f and %f): %f\n", op1, op2, result);
                break;
            case 'a':
                printf("     Enter the operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = AbsoluteValue(op1);
                printf("     Result of |%f|: %f\n", op1, result);
                break;
            case 'c':
                printf("     Enter the operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = FahrenheitToCelsius(op1);
                printf("     Result of (%f deg->C): %f\n", op1, result);
                break;
            case 'f':
                printf("     Enter the operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = CelsiusToFahrenheit(op1);
                printf("     Result of (%f deg->F): %f\n", op1, result);
                break;
            case 't':
                printf("     Enter the operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //tan at all iterations of 90 degrees is infinity
                if ((floor(op1) == op1) && ((int) op1 % 90) == 0) {
                    printf("     Result of tan(%f): infinity\n", op1);
                    break;
                }
                result = Tangent(op1);
                printf("     Result of tan(%f): %f\n", op1, result);
                break;
            case 'r':
                printf("     Enter the operand: ");
                if (scanf(" %lf", &op1) != 1) {
                    getchar();
                    printf("\n     Invalid operand!\n");
                    break;
                }
                //If the character after scanf is done scanning is not enter, it is invalid
                if (getchar() != '\n') {
                    printf("\n     Invalid operand!\n");
                    break;
                }
                result = Round(op1);
                printf("     Result of round(%f): %f\n", op1, result);
                break;
            case 'q':
                return;
            default:
                printf("     Error, not a valid operator \n");
        }

        //code for line mode or linux 
        //while (getchar() != '\n');

    }
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    if (operand2 == 0) {
        return HUGE_VAL;
    }
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    if (operand < 0) {
        return -operand;
    }
    return operand;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    return (operand - 32.0) * 5.0 / 9.0;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    return 9.0 / 5.0 * operand + 32.0;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    return (operand1 + operand2) / 2.0;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    //convert to radians then run through the tan function
    double rad = operand * M_PI / 180.0;
    return tan(rad);
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    //checks how to round based on how the distance from the operand to the ceiling
    if (operand > 0) {
        if ((ceil(operand) - operand) <= .5) {
            return ceil(operand);
        }
        return floor(operand);
    }
    if ((ceil(operand) - operand) >= 0.5) {
        return floor(operand);
    }
    return ceil(operand);
}


