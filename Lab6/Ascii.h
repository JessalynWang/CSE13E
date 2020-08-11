#ifndef ASCII_H
#define ASCII_H

#include <stdint.h>

// Specify the height and width of the characters defined in this library.
#define ASCII_FONT_HEIGHT 8
#define ASCII_FONT_WIDTH  6

/**
 * Pick a font for most of the standard ASCII characters into a byte array. Each character is stored
 * as ASCII_FONT_WIDTH number of bytes which each byte corresponding to a vertical line of 8 pixels
 * on the display.
 *
 */
extern const uint8_t ascii[256][ASCII_FONT_WIDTH];

/**
 * In the Toaster Oven lab, some special "artwork" characters are used to represent 
 * elements of the toaster oven.  These characters are #defined below as string literals 
 * with escape characters, and can be included in strings using string literal concatenation like so:
 * 
 * char *example_string = "Top of oven looks like" OVEN_TOP_ON "when on"
 *  
 * or alternatively, they can be inserted in a string using sprintf format specifiers:
 * 
 * sprintf(dest_str, "Top of oven looks like %s when on", OVEN_TOP_ON);
 * */

#define OVEN_TOP_ON "\x01"
#define OVEN_TOP_OFF "\x02"
#define OVEN_BOTTOM_ON "\x03"
#define OVEN_BOTTOM_OFF "\x04"
#define DEGREE_SYMBOL "\xF8"

#endif // ASCII_H