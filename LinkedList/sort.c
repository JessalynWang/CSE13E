/* 
 * File:   sort.c
 * Author: Jessalyn Wang
 *
 * File for comparing sorting algorithm times that also holds the sorting functions
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"


// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);


/* Students should not need to modify main! */
int main(void)
{
    BOARD_Init();

    printf("\n\nWelcome to jwang456's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;

    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    BOARD_End();
    while (1);
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list)
{
    //YOUR CODE GOES HERE!
    /* Selection sort looks through a doubly linked list, starting from a pointer to the first link. 
     * It then uses a second pointer to parse through the rest of the items after the first link. 
     * If it finds an item that should come before the first link, it swaps the data for the two. 
     * After reaching the end of the list with the second pointer, it sets the first pointer to the
     * value adjacent to its original link, the second pointer to the first pointer's adjacent item
     * and parses again. This continues until we reach the end of the list.*/
    int zero = 0;
    ListItem *firstUnsorted = LinkedListGetFirst(list);
    while (firstUnsorted->nextItem) {
        ListItem *compare = firstUnsorted->nextItem;
        while (compare) {
            if (strcmp(firstUnsorted->data, compare->data) > zero) {
                LinkedListSwapData(firstUnsorted, compare);
            }
            compare = compare->nextItem;
        }
        firstUnsorted = firstUnsorted->nextItem;
    }
    return LinkedListGetFirst(list);
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * InsertionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list)
{
    //YOUR CODE GOES HERE!
    int zero = 0;
    ListItem *scan;
    // start at the last item
    ListItem *firstSorted = LinkedListGetLast(list);
    
    // while we are not at the head of the list
    while (firstSorted->previousItem) {
        // we set unsorted to the previous item of firstSorted
        ListItem *unsorted = firstSorted -> previousItem;
        // if unsorted is first alphabetically, we advance first sorted
        if (strcmp(unsorted->data, firstSorted->data) < zero) {
            firstSorted = unsorted;
        } else {
            // we set scan equal to first sorted and find the place where unsorted
            // should be inserted behind firstSorted
            scan = firstSorted;
            while (scan->nextItem) {
                if (strcmp(scan->nextItem->data, unsorted->data) > zero) {
                    break;
                } else {
                    scan = scan->nextItem;
                }
            }
            // remove unsorted from its current position
            char *data = LinkedListRemove(unsorted);
            // place it where it belongs
            LinkedListCreateAfter(scan, data);
        }
    }
    return LinkedListGetFirst(list);
}

/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
 char* wordList[] = {
        "decide",   "toothpaste",   "lowly",        "robin",        "reign",        "crowd",
        "pies",     "reduce",       "tendency",     "surround",     "finger",       "rake", 
        "alleged",  "hug",          "nest",         "punishment",   "eggnog",       "side", 
        "beef",     "exuberant",    "sort",         "scream",       "zip",          "hair", 
        "ragged",   "damage",       "thought",      "jump",         "frequent",     "substance",
        "head",     "step",         "faithful",     "sidewalk",     "pig",          "raspy",
        "juggle",   "shut",         "maddening",    "rock",         "telephone",    "selective",
        NULL};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};


    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if(tail == NULL){
            printf("ERROR:  Heap full! Please increase heap size.\n");
            FATAL_ERROR();
        }
    }
    return head;
}
// </editor-fold>
