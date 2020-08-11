#ifndef OLED_H
#define OLED_H

/**
 * This file provides a complete interface for interacting with the OLED on Digilent's I/O Shield.
 * It works by storing a backend array of pixel data for storing modifications and then flushing
 * that to the screen to update it when OledUpdate() is called. Since OledUpdate() is very slow,
 * this allows for batching together a lot of drawing operations before finally updating the screen
 * at the end in one go.
 *
 * This OLED is a monochrome display, offering black and white as your color options. These can be
 * specified as arguments to OledDrawChar() and OledClear(). Note that this coloring can be inverted
 * on the display itself by calling OledSetDisplayInverted(). This doesn't actually modify the data
 * stored in the pixels, but merely switches what colors each bit value represents.
 *
 * The OLED offers both a pixel interface and a text interface for drawing. Individual pixels can be
 * read and changed with the Oled*Pixel() functions.
 *
 * Higher-level text operations can be done through OledDrawChar() and OledDrawString, with the
 * latter function being the easier one to use. It allows for writing text across all OLED_NUM_LINES
 * lines on the display where each line can hold up to OLED_CHARS_PER_LINE complete characters.
 *
 * The font (defined in Ascii.h) used for drawing characters is a custom monospaced font. It
 * provides glyphs for most of the basic ASCII character set, but is incomplete. Additionally some
 * non-printing characters have been repurposed for custom characters for specific uses
 * (@see Ascii.h).
 */


#include "Ascii.h"
#include "OledDriver.h"
#include "BOARD.h"

/**
 * Define constants for available colors for the OLED: either white or black.
 */
typedef enum {
    OLED_COLOR_BLACK = 0,
    OLED_COLOR_WHITE = 1
} OledColor;

// Define how many lines of text the display can show.
#define OLED_NUM_LINES         (OLED_DRIVER_PIXEL_ROWS / ASCII_FONT_HEIGHT)

// Define how many complete characters can be displayed on a row of text.
#define OLED_CHARS_PER_LINE  (OLED_DRIVER_PIXEL_COLUMNS / ASCII_FONT_WIDTH)

/**
 * Initializes the OLED, turns it on, and clears the screen.
 */
void OledInit(void);

/**
 * Sets a specific pixel in the frame buffer, available colors are black or white.
 * @note OledUpdate() must be called before the OLED will actually display these changes.
 * @param x The X position (left is zero)
 * @param y The Y position (top is zero)
 * @param color OLED_COLOR_WHITE or OLED_COLOR_BLACK
 */
void OledSetPixel(int x, int y, OledColor color);

/**
 * Reads a pixel from the frame buffer.
 * @param x The X position (left is zero)
 * @param y The Y position (top is zero)
 * @return OLED_COLOR_WHITE or OLED_COLOR_BLACK
 */
int OledGetPixel(int x, int y);

/**
 * Draws the specified character at the specified position, using Ascii.h as the font.
 * @note OledUpdate() must be called before the OLED will actually display these changes.
 * @param x The x-position to use as the left-most value for the character.
 * @param y The y-position to use as the top-most value for the character
 * @param c The character to write. Uses the character array defined in Ascii.h
 * @return True if the write succeeded. Fails on invalid inputs.
 */
uint8_t OledDrawChar(int x, int y, char c);

/**
 * Draws a string to the screen buffer, starting on the top line. OLED_CHARS_PER_LINE characters fit
 * on each of the OLED_NUM_LINES lines on the screen. A newline in the string will start the
 * subsequent characters on the next line, otherwise once a line has run out of room no more
 * characters will display on the screen. There is no other special processing of the input string
 * besides this newline functionality, for example backspace characters just render as blank
 * characters.
 *
 * For example, the following code example shows Hello World I'm Working! on the OLED with each word
 * on its own line:
 *   OledInit();
 *   OledDrawString("Hello\nWorldI'm\nWorking!\n");
 *   OledUpdate();
 *
 * @note OledUpdate() must be called before the OLED will actually display these changes.
 * @param string A null-terminated string to print.
 */
void OledDrawString(const char *string);

/**
 * Writes the specified color pixels to the entire frame buffer.
 * @note OledUpdate() must be called before the OLED will actually display these changes.
 * @param p The color to write all pixels in the OLED to.
 */
void OledClear(OledColor p);

/**
 * Sets the display to display pixels the opposite color than what was intended. This does not
 * change the stored value for any pixel.
 * @see OledSetDisplayNormal
 */
void OledSetDisplayInverted(void);

/**
 * Displays all pixels as they are stored, where a 0 indicates black and a 1 indicates white. This
 * is the default setting for the OLED on startup. This undoes `OledSetDisplayInverted()`.
 * @see OledSetDisplayInverted
 */
void OledSetDisplayNormal(void);

/**
 * Turns on the OLED display.
 * @note This is not required as part of initialization, as `OledInit()` already does this.
 */
void OledOn(void);

/**
 * Turns off the OLED display.
 * @note This is not required as part of initialization, as `OledInit()` already does this.
 */
void OledOff(void);

/**
 * Refreshes the OLED display to reflect any changes. Should be called after any operation that
 * changes the display: OledSetPixel(), OledDrawChar(), OledDrawString(), and OledClear().
 *
 * This function is very slow and so shouldn't be called too often or the OLED might look dim or
 * even show no data at all. This is because it uses a blocking SPI interface to push out the entire
 * screen of pixel data every time it's called. Like I said, very slow function!
 *
 * For example, the following code example shows Hello World I'm Workin! on the OLED with each word
 * on its own line:
 *   OledInit();
 *   OledDrawString("Hello\nWorldI'm\nWorking!\n");
 *   OledUpdate();
 */
void OledUpdate(void);

#endif