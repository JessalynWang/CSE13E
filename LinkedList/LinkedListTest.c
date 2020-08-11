/* 
 * File:   LinkedListTest.c
 * Author: Jessalyn Wang
 *
 * Created on May 4, 2020, 12:40 PM
 * Test harness for LinkedList.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"

// some constants defined here
#define HELLO "Hello"
#define MYFRIEND "my friend"
#define GOODBYE "Goodbye!"

/*
 * 
 */
int main(void) {
    
    BOARD_Init();

    printf("\nWelcome to jwang456's LinkedListTest.c, compiled on %s %s.\n\n", __DATE__, __TIME__);
    
    // test for linkedlistnew
    char *data = "Hello";
    ListItem *Link1 = LinkedListNew(data);
    printf("Testing new: \n\tShould print 'Hello': %s\n", Link1->data);
    
    if (!strcmp(Link1->data, HELLO)) {
        printf("\tLinkedListNew: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for createafter
    char *data2 = "Goodbye!";
    ListItem *Link2 = LinkedListCreateAfter(Link1, data2);
    printf("Testing createafter: \n\tShould print 'Hello Goodbye!': %s %s\n", 
            Link2->previousItem->data, Link2->data);
    
    char *data3 = "my friend";
    ListItem *Link3 = LinkedListCreateAfter(Link1, data3);
    printf("\tShould print 'Hello my friend Goodbye!': %s %s %s\n", 
            Link3->previousItem->data, Link3->data, Link3->nextItem->data);
    
    if (!strcmp(Link3->previousItem->data, HELLO) && !strcmp(Link3->data, MYFRIEND)
            && !strcmp(Link3->nextItem->data, GOODBYE)) {
        printf("\tLinkedListCreateAfter: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for remove
    char *data4 = LinkedListRemove(Link2);
    printf("Testing remove: \n\tShould print 'Hello my friend' (removed = Goodbye!): "
            "%s %s (removed = %s)\n", Link3->previousItem->data, Link1->nextItem->data, data4);
    Link2 = LinkedListCreateAfter(Link3, data2);
    
    char *data5 = LinkedListRemove(Link3);
    printf("\tShould print 'Hello Goodbye!' (removed = my friend): "
            "%s %s (removed = %s)\n", Link2->previousItem->data, Link1->nextItem->data, data5);
    Link3 = LinkedListCreateAfter(Link1, data3);
    
    char *data6 = LinkedListRemove(Link1);
    printf("\tShould print 'my friend Goodbye!' (removed = Hello): "
            "%s %s (removed = %s)\n", Link2->previousItem->data, Link3->nextItem->data, data6);
    
    if (data4 && data5 && data6) {
        printf("\tLinkedListRemove: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for getfirst
    Link1 = LinkedListGetFirst(Link2);
    printf("Testing getfirst: \n\tShould print 'my friend': %s\n", Link1->data);
    Link1 = LinkedListGetFirst(Link3);
    printf("\tShould print 'my friend': %s\n", Link1->data);
    
    if (!strcmp(Link1->data, MYFRIEND)) {
        printf("\tLinkedListGetFirst: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for getlast
    Link1 = LinkedListGetLast(Link2);
    printf("Testing getlast: \n\tShould print 'Goodbye!': %s\n", Link1->data);
    Link1 = LinkedListGetLast(Link3);
    printf("\tShould print 'Goodbye!': %s\n", Link1->data);
    
    if (!strcmp(Link1->data, GOODBYE)) {
        printf("\tLinkedListGetLast: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for size
    int size = LinkedListSize(Link2);
    printf("Testing size: \n\tShould print 2: %d\n", size);
    
    if (size == 2) {
        printf("\tLinkedListSize: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for swap
    int swap = LinkedListSwapData(Link2, Link3);
    printf("Testing swap: \n\t");
    if (swap) {
        printf("Should print 'Goodbye! my friend': %s %s\n",
                Link3->data, Link2->data);
    } else {
        printf("failed!\n");
    }
    swap = LinkedListSwapData(Link2, Link3);
    if (swap) {
        printf("\tShould print 'my friend Goodbye!': %s %s\n",
                Link3->data, Link2->data);
    }
    LinkedListSwapData(Link2, Link3);
    
    if (!strcmp(Link2->data, MYFRIEND) && !strcmp(Link3->data, GOODBYE)) {
        printf("\tLinkedListGetSwapData: Passed!\n");
    } else {
        printf("\tFailed!\n");
    }
    
    // test for print
    printf("Testing print: \n\tShould print '[Goodbye!, my friend]': ");
    LinkedListPrint(Link3);
    Link2->data = NULL;
    printf("\tShould print '[Goodbye!, (null)]': ");
    LinkedListPrint(Link2);
    
    ListItem *Link4 = NULL;
    ListItem *Link5 = NULL;
    
    printf("Testing null inputs: \n\t");
    if (LinkedListRemove(Link4) == NULL && LinkedListSize(Link4) == 0 
            && LinkedListGetFirst(Link4) == NULL && LinkedListGetLast(Link4) == NULL 
            && LinkedListSwapData(Link4, Link5) == STANDARD_ERROR) {
        printf("All tests passed: (5/5) \n");
    } else {
        printf("failed!\n");
    }
    
    BOARD_End();
    while (1);
    return 0;
}

