/* 
 * File:   bounce_buttons.c
 * Author: Jessalyn Wang
 *
 * lights up leds based on buttons pressed
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Buttons.h"
#include "Leds_Lab06.h"
// **** Set macros and preprocessor directives ****
enum LEDRegisters{
    LED0 = 0x00,
    LED1 = 0x01,
    LED2 = 0x02,
    LED3 = 0x04,
    LED4 = 0x08,
    LED5 = 0x10,
    LED6 = 0x20,
    LED7 = 0x40,
    LED8 = 0x80
};
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
    T1CONbits.TCKPS = 1; // 1:8 prescaler
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
    printf("Welcome to jwang456's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    
    LEDS_INIT();
    ButtonsInit();
    while (1) {
        if (timerEvent != BUTTON_EVENT_NONE) {
            // get the current led pattern
            char led = LEDS_GET();
            uint8_t switchesState = SWITCH_STATES();
            
            // based on the state of the switches and what happened in the event we toggle the led on
            // or off with a bitwise xor. We do this for every switch and its respective button
            if ((switchesState & SWITCH_STATE_SW1) && (timerEvent & BUTTON_EVENT_1UP)) {
                led = led ^ LED1 ^ LED2;
            } else if (!(switchesState & SWITCH_STATE_SW1) && timerEvent & BUTTON_EVENT_1DOWN) {
                led = led ^ LED1 ^ LED2;
            }
            if ((switchesState & SWITCH_STATE_SW2) && (timerEvent & BUTTON_EVENT_2UP)) {
                led = led ^ LED3 ^ LED4;
            } else if (!(switchesState & SWITCH_STATE_SW2) && timerEvent & BUTTON_EVENT_2DOWN) {
                led = led ^ LED3 ^ LED4;
            }
            if ((switchesState & SWITCH_STATE_SW3) && (timerEvent & BUTTON_EVENT_3UP)) {
                led = led ^ LED5 ^ LED6;
            } else if (!(switchesState & SWITCH_STATE_SW3) && timerEvent & BUTTON_EVENT_3DOWN) {
                led = led ^ LED5 ^ LED6;
            }
            if ((switchesState & SWITCH_STATE_SW4) && (timerEvent & BUTTON_EVENT_4UP)) {
                led = led ^ LED7 ^ LED8;
            } else if (!(switchesState & SWITCH_STATE_SW4) && timerEvent & BUTTON_EVENT_4DOWN) {
                led = led ^ LED7 ^ LED8;
            }
            // we set the led to the result of all the if statements
            LEDS_SET(led);
            // reset the timer event to none
            timerEvent = BUTTON_EVENT_NONE;
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
    // get the events that happened
    timerEvent = ButtonsCheckEvents();

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}