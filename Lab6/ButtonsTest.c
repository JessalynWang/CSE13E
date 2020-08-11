/* 
 * File:   ButtonsTest.c
 * Author: Jessalyn Wang
 *
 * file for testing the buttons library
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
static uint8_t timerEvent;
// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to jwang456's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);

    
    printf("Please press some buttons!\n");
    
    // initialize buttons so they are all set to input
    ButtonsInit();
    
    while (1) {
        // initially, we point at dashed lines because we don't know if buttons have been pressed yet
        char *b1 = "----";
        char *b2 = "----";
        char *b3 = "----";
        char *b4 = "----";
        
        // if the timer indicates a button event has occurred
        if (timerEvent != BUTTON_EVENT_NONE) {
            // we use a bitwise and to narrow down which buttons have been pressed
            // or which buttons have been released
            if (timerEvent & BUTTON_EVENT_1DOWN) {
                b1 = "DOWN";
            }
            if (timerEvent & BUTTON_EVENT_1UP) {
                b1 = " UP ";
            }
            if (timerEvent & BUTTON_EVENT_2DOWN) {
                b2 = "DOWN";
            }
            if (timerEvent & BUTTON_EVENT_2UP) {
                b2 = " UP ";
            }
            if (timerEvent & BUTTON_EVENT_3DOWN) {
                b3 = "DOWN";
            }
            if (timerEvent & BUTTON_EVENT_3UP) {
                b3 = " UP ";
            }
            if (timerEvent & BUTTON_EVENT_4DOWN) {
                b4 = "DOWN";
            }
            if (timerEvent & BUTTON_EVENT_4UP) {
                b4 = " UP ";
            }
            
            // reset the timerEvent to no event
            timerEvent = BUTTON_EVENT_NONE;
            // print the event and what happened
            printf("Event: 4:%s 3:%s 2:%s 1:%s\n", b4, b3, b2, b1);
        }
        
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    // every time the ISR runs check for events
    timerEvent = ButtonsCheckEvents();
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}