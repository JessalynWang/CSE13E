// Player.c
// Jessalyn Wang
#include "UNIXBOARD.h"
#include <stdint.h>
#include "Player.h"

static int playerInventory[INVENTORY_SIZE];
static int currentIndex = 0;

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item) {
    // if the current index of the next space in the array is within the array, add the item
    if (currentIndex < INVENTORY_SIZE) {
        playerInventory[currentIndex] = item;
        return SUCCESS;
    }
    return STANDARD_ERROR;
    
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item) {
    // iterate backwards through the array, and look for the item
    int copy;
    for (copy = currentIndex; copy >= 0; copy--) {
        if (playerInventory[copy] == item) {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
