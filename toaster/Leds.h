#ifndef LEDS_H
#define LEDS_H

/**
 * @file
 * This library provides an interface for controlling the LEDs on the 
 * chipKit Basic I/O Shield development board.
 *
 * This file provides prototypes for functions defined in Leds.c, which is appropriate for Lab06 ONLY.
 * Future labs will use a header-only version of the file.
 */

/**
 * LEDS_INIT() initializes the LED bar by doing two things:
 *      1) Use the appropriate SFRs to set each LED pin to "output" mode.
 *      2) Use the appropriate SFRs to set each LED pin's output value to 0 (low voltage).
 * 
 * After "calling" LEDS_INIT(), the other functions in this file can be used to manipulate the LED bar.
 */

#define LEDS_INIT() { \
    TRISE = 0x00; \
    LATE = 0x00; \
}


/**
 * LEDS_SET() controls the output on the LED bar.  Input values are 8-bit patterns, where each bit 
 * describes the desired state of the corresponding LED.  So, for example, LEDS_SET(0x80) should 
 * leave the first LED on, and the last 7 LEDs off.  LEDS_SET(0x1F) should turn off the first three
 * LEDs and turn on the remaining five LEDs.
 * 
 * @param newPattern:  An 8-bit value describing the desired output on the LED bar.  
 * 
 * LEDS_SET should not change any LED pins to inputs.
 */
#define LEDS_SET(newPattern) LATE = newPattern


/**
 * LEDS_GET() evaluates to the current state of the LED bar.  "Return" values are 8-bit patterns,
 * where each bit describes the current state of the corresponding LED So, for example, if the 
 * led bar's led's are [ON OFF ON OFF   OFF ON OFF ON], LEDS_GET() should "return" 0xA5.
 * 
 * @return char:  An 8-bit value describing the current output on the LED bar.  
 * 
 * LEDS_GET() should not change the state of the LEDS, or any SFRs.
 */
#define LEDS_GET() LATE

#endif // LEDS_H