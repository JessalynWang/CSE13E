/* 
 * File:   BOARD.h
 * Author: Max Dunne
 *
 * Created on December 19, 2012, 2:08 PM
 */

#ifndef BOARD_H
#define	BOARD_H


/*******************************************************************************
 * PUBLIC #INCLUDES                                                           *
 ******************************************************************************/
#ifdef PIC32
#include <GenericTypeDefs.h>
#include <xc.h>
#else
#include <stdlib.h>
#endif
#include <stdint.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#ifndef PIC32
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;
#endif
//suppresses various warnings that we don't need to worry about for CSE13E
#ifndef _SUPPRESS_PLIB_WARNING
#define _SUPPRESS_PLIB_WARNING
#endif

#ifndef _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#endif

// Define some standard error codes.
enum {
    SIZE_ERROR = -1,
    STANDARD_ERROR,
    SUCCESS
};

// Specify the default UART to use. UART1 is selected the Uno32, as it's the one on the USB port.
#define UART_USED UART1

// Set the baud rate for use with the UART. This is chosen as it's the default baud rate for Tera
// Term.
#define UART_BAUD_RATE 115200

/*
 * Set some helper macros for interfacing with the switches
 */

// Define macros for referring to the single-bit values of the switches.
#define SW1 PORTDbits.RD8
#define SW2 PORTDbits.RD9
#define SW3 PORTDbits.RD10
#define SW4 PORTDbits.RD11

/**
 * Provides a way to quickly get the status of all 4 switches as a nibble, where a bit is 1 if
 * the button is being pressed and 0 if it's not. The buttons are ordered such that bit 3 is switch
 * 4 and bit 0 is switch 1.
 * @see enum ButtonStateFlags
 */
#define SWITCH_STATES() ((PORTD >> 8) & 0x0F)

/**
 * The SwitchStateFlags enum provides a bitmask for use with the SWITCH_STATES macro. By bitwise-
 * ANDing any of these enum values with the return value from SWITCH_STATES, the current state of
 * the switches can be tested.
 *
 * For example:
 *
 * uint8_t switchesState = SWITCH_STATES();
 * if (switchesState & SWITCH_STATE_SW3) {
 *   // Switch 3 is on.
 * }
 *
 * @see SWITCH_STATES()
 */
enum SwitchStateFlags {
    SWITCH_STATE_SW1 = 0x1,
    SWITCH_STATE_SW2 = 0x2,
    SWITCH_STATE_SW3 = 0x4,
    SWITCH_STATE_SW4 = 0x8
};

/*
 * Set some helper macros for interfacing with the buttons
 */

// Define macros for referring to the single-bit values of the buttons.
#define BTN1 PORTFbits.RF1
#define BTN2 PORTDbits.RD5
#define BTN3 PORTDbits.RD6
#define BTN4 PORTDbits.RD7

/**
 * Provides a way to quickly get the status of all 4 pushbuttons in to 4-bits, where a bit is 1 if
 * the button is being pressed and 0 if it's not. The buttons are ordered such that bit 3 is button
 * 4 and bit 0 is button 1.
 * @see enum ButtonStateFlags
 */
#define BUTTON_STATES() (((PORTD >> 4) & 0x0E) | ((PORTF >> 1) & 0x01))

/**
 * The ButtonStateFlags enum provides a bitmask for use with the BUTTON_STATES macro. By bitwise-
 * ANDing any of these enum values with the return value from BUTTON_STATES, the current state of
 * the buttons can be tested.
 *
 * For example:
 *
 * uint8_t buttonsState = BUTTON_STATES();
 * if (buttonsState & BUTTON_STATE_3) {
 *   // Buttons 3 is pressed down.
 * }
 *
 * @see BUTTON_STATES()
 */
enum ButtonStateFlags {
    BUTTON_STATE_1 = 0x1,
    BUTTON_STATE_2 = 0x2,
    BUTTON_STATE_3 = 0x4,
    BUTTON_STATE_4 = 0x8
};

/**
 * Enter an infinite loop and flash one of the status LEDs. This should be used when there is an
 * unrecoverable error onboard, like when a subsystem fails to initialize.
 */
#ifdef PIC32
#define FATAL_ERROR() do {                                     \
                          TRISFCLR = 1;                        \
                          LATFCLR = 1;                         \
                          while (1) {                          \
                              unsigned long int i;             \
                              for (i = 0; i < 600000; ++i);    \
                              LATFINV = 1;                     \
                          }                                    \
                      } while (0);
#else
#define FATAL_ERROR() exit(EXIT_FAILURE)
#endif
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                     *
 ******************************************************************************/

/**
 * Function: BOARD_Init(void)
 * @param None
 * @return None
 * @brief Set the clocks up for the board, initializes the serial port, and turns
 * on the A/D subsystem for battery monitoring
 * @author Max Dunne, 2013.09.15  */
void BOARD_Init();


/**
 * Function: BOARD_End(void)
 * @param None
 * @return None
 * @brief shuts down all peripherals except for serial and A/D. Turns all pins
 * into input
 * @author Max Dunne, 2013.09.20  */
void BOARD_End();

/**
 * Function: BOARD_GetPBClock(void)
 * @param None
 * @return PB_CLOCK - speed the peripheral clock is running in hertz
 * @brief returns the speed of the peripheral clock.  Nominally at 20Mhz
 * @author Max Dunne, 2013.09.01  */
unsigned int BOARD_GetPBClock();


/**
 * Function: BOARD_GetSysClock(void)
 * @param None
 * @return SYS_CLOCK - speed the main clock is running at
 */
unsigned int BOARD_GetSysClock();

#endif	/* BOARD_H */
