// Game.c
// Jessalyn Wang
#include "UNIXBOARD.h"
#include <stdint.h>
#include "Player.h"
#include "Game.h"
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

// room struct
struct Room{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    int northExit;
    int southExit;
    int eastExit;
    int westExit;
};

static struct Room currentRoom;
static char fileOpenString[25];

uint8_t fileOpen(int roomNum);
/**
 * These function transitions between rooms. Each call should return SUCCESS if the current room has
 * an exit in the correct direction and the new room was able to be loaded, and STANDARD_ERROR
 * otherwise.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded.
 */
int GameGoNorth(void) {
    if (currentRoom.northExit != 0x00 && fileOpen(currentRoom.northExit) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoEast(void) {
    if (currentRoom.eastExit != 0x00 && fileOpen(currentRoom.eastExit) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoSouth(void) {
    if (currentRoom.southExit != 0x00 && fileOpen(currentRoom.southExit) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * @see GameGoNorth
 */
int GameGoWest(void) {
    if (currentRoom.westExit != 0x00 && fileOpen(currentRoom.westExit) == SUCCESS) {
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void) {
    uint8_t passed = fileOpen(STARTING_ROOM);
    if (passed == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

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
int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, currentRoom.title);
    return strlen(title);
}

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
int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, currentRoom.description);
    return strlen(desc);
}

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
uint8_t GameGetCurrentRoomExits(void) {
    uint8_t exits = 0b0000;
    if (currentRoom.northExit) {
        exits |= 0b1000;
    } 
    if (currentRoom.eastExit) {
        exits |= 0b0100;
    } 
    if (currentRoom.southExit) {
        exits |= 0b0010;
    } 
    if (currentRoom.westExit) {
        exits |= 0b0001;
    }
    return exits;
}

// helper function for opening and reading the file and storing the values in the struct
uint8_t fileOpen(int roomNum) {
    // format the string so it can look for whatever room we want to open
    sprintf(fileOpenString, "RoomFiles/room%d.txt", roomNum);
    
    // make the file pointer and int for length, and a flag for items
    FILE *fp;
    int length;
    int flag = 1;
    // open the file
    fp = fopen(fileOpenString, "r");
    if (fp == NULL) {
        FATAL_ERROR();
    }
    // set the file pointer 3 values in to skip the RPG portion of the file
    fseek(fp, 3, SEEK_SET);
    // find the length of the title and read it into the title of the room
    length = fgetc(fp);
    fread(currentRoom.title, length, 1, fp);
    // add the null terminator to the end of the string
    currentRoom.title[length] = '\0';
    if (strlen(currentRoom.title) != length) {
        return STANDARD_ERROR;
    }
    
    // rewrite length with items required
    // get number of items required
    length = fgetc(fp);
    // see if they are in the inventory
    while (length) {
        uint8_t item = fgetc(fp);
        if (FindInInventory(item) == STANDARD_ERROR) {
            // item is not in inventory, set flag to 0
            flag = 0;
            break;
        }
        length--;
    }
    
    // rewrite length with length of description
    // get length of description
    length = fgetc(fp);
    // read the characters into the description
    fread(currentRoom.description, length, 1, fp);
    currentRoom.description[length] = '\0';
    if (strlen(currentRoom.description) != length) {
        return STANDARD_ERROR;
    }
    
    
    // rewrite with amnt of collectables in room
    // find number of collectables
    length = fgetc(fp);
    // iterate over number and put them in if they are not in already
    while (length) {
        uint8_t collect = fgetc(fp);
        if (FindInInventory(collect) == STANDARD_ERROR) {
            int r = AddToInventory(collect);
            if (r == STANDARD_ERROR) {
                return STANDARD_ERROR;
            }
        }
        length--;
    }
    
    // write exits into the exit members
    currentRoom.northExit = fgetc(fp);
    currentRoom.eastExit = fgetc(fp);
    currentRoom.southExit = fgetc(fp);
    currentRoom.westExit = fgetc(fp);
    
    // if the flag is 0, we have another room to version. writes that version to the members
    if (flag == 0) {
        // rewrite with amnt of requirements in room version 2
        length = fgetc(fp);
        // redundant because should have 0 items needed, but here just in case
        while (length) {
            uint8_t item = fgetc(fp);
            if (FindInInventory(item) == STANDARD_ERROR) {
                return STANDARD_ERROR;
            }
            length--;
        }
        
        // rest of code is the same as above
        length = fgetc(fp);
        
        
        fread(currentRoom.description, length, 1, fp);
        currentRoom.description[length] = '\0';
        
        length = fgetc(fp);
        while (length) {
            uint8_t collect2 = fgetc(fp);
            if (FindInInventory(collect2) == STANDARD_ERROR) {
                int r = AddToInventory(collect2);
                if (r == STANDARD_ERROR) {
                    return STANDARD_ERROR;
                }
            }
            length--;
        }

        currentRoom.northExit = fgetc(fp);
        currentRoom.eastExit = fgetc(fp);
        currentRoom.southExit = fgetc(fp);
        currentRoom.westExit = fgetc(fp);
    }
    
    fclose(fp);
    
    return SUCCESS;
    
}
