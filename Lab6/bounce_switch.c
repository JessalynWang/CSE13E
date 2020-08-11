/* 
 * File:   bounce_switch.c
 * Author: Jessalyn Wang
 *
 * controls the speed of a moving led with switches
 */
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
					


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

#include "Leds_Lab06.h"

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer Timer1;
enum direction {
    LEFT,
    RIGHT
};
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
    printf("Welcome to jwang456's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    
    Timer1.event = FALSE;
    // initialized state is nothing
    int state = -1;
    char leftMost = 0x80;
    char rightMost = 0x01;
    // starts with the led on the right
    char currentLED = 0x01;
    
    LEDS_INIT();
							 
	while(1){
        //poll timer events and react if any occur
        if (Timer1.event) {
            // set the led to what it currently is
            LEDS_SET(currentLED);
            
            // if the current led is an edge case we make sure to reverse the direction of the led
            if (currentLED == leftMost) {
                state = RIGHT;
            } else if (currentLED == rightMost) {
                state = LEFT;
            }
            // depending on the direction the led is moving we shift the led that is lit left or
            // right by one
            if (state == LEFT) {
                currentLED <<= 1;
            } else {
                // edge case to account for mplabx padding with 1
                if (currentLED == leftMost) {
                    currentLED = (currentLED >> 1) ^ currentLED;
                } else {
                    currentLED >>= 1;
                }
            }
            // set the event to false to indicate the end
            Timer1.event = FALSE;
        }
        
        
    }			


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}


/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    int scale = 3; // number to scale the switch count by
    Timer1.timeRemaining--; // decrement the time remaining, a variable that counts the time until
                            // until the next led lights up
    
    // if it is time to light the next led up
    if (Timer1.timeRemaining <= 0) {
        // we set the event to true to indicate it is time
        Timer1.event = TRUE;
        
        // now we tally the switches to see if a speed change needs to occur
        // overall there will be 16 different speeds, based on the combination made by the four switches
        uint8_t switchCount = 0x00;
        
        // returns the state of the switches
        uint8_t switchesState = SWITCH_STATES();
        
        // we or the switches into the count if they are up
        if (switchesState & SWITCH_STATE_SW4) {
            switchCount |= SWITCH_STATE_SW4;
        }
        if (switchesState & SWITCH_STATE_SW3) {
            switchCount |= SWITCH_STATE_SW3;
        }
        if (switchesState & SWITCH_STATE_SW2) {
            switchCount |= SWITCH_STATE_SW2;
        }
        if (switchesState & SWITCH_STATE_SW1) {
            switchCount |= SWITCH_STATE_SW1;
        }
        switchCount *= scale; // scale switch count to make the difference more noticeable
        // set the timeRemaining to the speed given by the scaled switchCount
        Timer1.timeRemaining = switchCount;
        
    }
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}