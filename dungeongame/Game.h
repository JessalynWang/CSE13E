#ifndef GAME_H
#define GAME_H

#include "UNIXBOARD.h"

#include <stdint.h>

// The initial room that Game should initialize to.
#define STARTING_ROOM 32



// These variable describe the maximum string length of the room title and description respectively.
// Note that they don't account for the trailing '\0' character implicit with C-style strings.
#define GAME_MAX_ROOM_TITLE_LENGTH 21
#define GAME_MAX_ROOM_DESC_LENGTH 255

/**
 * This enum defines flags for checking the return values of GetCurrentRoomExits(). Usage is as
 * follows:
 *
 * if (GetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
 *   // The current room has a west exit.
 * }
 *
 * @see GetCurrentRoomExits
 */
typedef enum {
    GAME_ROOM_EXIT_WEST_EXISTS  = 0b0001,
    GAME_ROOM_EXIT_SOUTH_EXISTS = 0b0010,
    GAME_ROOM_EXIT_EAST_EXISTS  = 0b0100,
    GAME_ROOM_EXIT_NORTH_EXISTS = 0b1000
} GameRoomExitFlags;

/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void);

/**
 * @see GameGoNorth
 */
int GameGoEast(void);

/**
 * @see GameGoNorth
 */
int GameGoSouth(void);

/**
 * @see GameGoNorth
 */
int GameGoWest(void);

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void);

/**
 * Copies the current room title as a NULL-terminated string into the provided character array.
 * Only a NULL-character is copied if there was an error so that the resultant output string
 * length is 0.
 * @param title A character array to copy the room title into. Should be GAME_MAX_ROOM_TITLE_LENGTH+1
 *             in length in order to allow for all possible titles to be copied into it.
 * @return The length of the string stored into `title`. Note that the actual number of chars
 *         written into `title` will be this value + 1 to account for the NULL terminating
 *         character.
 */
int GameGetCurrentRoomTitle(char *title);

/**
 * GetCurrentRoomDescription() copies the description of the current room into the argument desc as
 * a C-style string with a NULL-terminating character. The room description is guaranteed to be less
 * -than-or-equal to GAME_MAX_ROOM_DESC_LENGTH characters, so the provided argument must be at least
 * GAME_MAX_ROOM_DESC_LENGTH + 1 characters long. Only a NULL-character is copied if there was an
 * error so that the resultant output string length is 0.
 * @param desc A character array to copy the room description into.
 * @return The length of the string stored into `desc`. Note that the actual number of chars
 *          written into `desc` will be this value + 1 to account for the NULL terminating
 *          character.
 */
int GameGetCurrentRoomDescription(char *desc);

/**
 * This function returns the exits from the current room in the lowest-four bits of the returned
 * uint8 in the order of NORTH, EAST, SOUTH, and WEST such that NORTH is in the MSB and WEST is in
 * the LSB. A bit value of 1 corresponds to there being a valid exit in that direction and a bit
 * value of 0 corresponds to there being no exit in that direction. The GameRoomExitFlags enum
 * provides bit-flags for checking the return value.
 *
 * @see GameRoomExitFlags
 *
 * @return a 4-bit bitfield signifying which exits are available to this room.
 */
uint8_t GameGetCurrentRoomExits(void);

#endif // GAME_H
