// Lab08_main.c
// Jessalyn Wang
// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
#define NO_EXITS 0b0000
// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    printf("Welcome to my RPG game!\n");
    int result = GameInit();
    
    if (result == STANDARD_ERROR) {
        FATAL_ERROR();
    }
    
    char title[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    char input;
    uint8_t exits;
    int check;
    // loops while the user has not quit
    while (1) {

        // get and print the title
        GameGetCurrentRoomTitle(title);
        printf("\n%s\n", title);
        // get and print the description
        GameGetCurrentRoomDescription(description);
        printf("\n%s\n", description);
        // get and print the possible exits
        exits = GameGetCurrentRoomExits();
        printf("Possible exits are: ");
        if (exits & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("North ");
        }
        if (exits & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("East ");
        }
        if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("South ");
        }
        if (exits & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("West ");
        }
        if (exits == NO_EXITS) {
            printf("None. Press q to quit.");
        }
        printf("\n");
            
        while (1) {
            
            // intentional so it prints where would you like to go? again in case of invalid input
            printf("\nWhere would you like to go? (enter n for North, e for East, etc. Enter q to quit): ");
            // take input
            input = getchar();
            // if the input is more than one character, prompt again
            if (getchar() != '\n') {
                while (getchar() != '\n');
                printf("Input invalid, please try again!\n");
                continue;
            }
            
            // once the input is one character, check to see if its valid
            switch (input) {
                case 'n':
                    check = GameGoNorth();
                    // if invalid, break away and prompt again
                    if (check == STANDARD_ERROR) {
                        printf("There is no North exit!\n");
                    }
                    break;
                case 's':
                    check = GameGoSouth();
                    // same as case n
                    if (check == STANDARD_ERROR) {
                        printf("There is no South exit!\n");
                    }
                    break;
                case 'e':
                    // same as case n
                    check = GameGoEast();
                    if (check == STANDARD_ERROR) {
                        printf("There is no East exit!\n");
                    }
                    break;
                case 'w':
                    // same as case n
                    check = GameGoWest();
                    if (check == STANDARD_ERROR) {
                        printf("There is no West exit!\n");
                    }
                    break;
                case 'q':
                    printf("\nYou have quit the game!\n");
                    break;
                default:
                    // if the input is none of the above, enter again
                    printf("Invalid entry please try again!\n");
                    break;
            }
            // if the input is q or the direction is go-able, go to the next room/quit
            if (input == 'q' || check == SUCCESS) {
                break;
            }
        }
        // if the input is q, quit
        if (input == 'q') {
            exit(SUCCESS);
        }

    }
    /**************************************************************************************************/
}

