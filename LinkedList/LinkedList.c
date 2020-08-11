/* 
 * File:   LinkedList.c
 * Author: Jessalyn Wang
 *
 * Library for ListItem struct and its functions
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"

/**
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 */
ListItem *LinkedListNew(char *data) {
    // allocate the memory for the ListItem
    ListItem *Item = malloc(sizeof(ListItem));

    // if the allocating memory failed for some reason, return the NULL pointer
    if (Item == NULL) {
        return Item;
    }

    // set the nextItem and previousItem pointers to null, as this is a new list
    Item->nextItem = NULL;
    Item->previousItem = NULL;
    Item->data = data;
    return Item;
}

/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, CreateAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */
ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    // allocate the memory for the new item
    ListItem *newItem = malloc(sizeof(ListItem));

    // if allocation fails, return NULL
    if (newItem == NULL) {
        return newItem;
    }

    // if the passed item is null, we act like we are creating a new linked list
    if (item == NULL) {
        newItem->nextItem = NULL;
        newItem->previousItem = NULL;
        newItem->data = data;
    } else {
        // if it is the end of the list, we set the nextItem to null
        if (item->nextItem == NULL) {
            newItem->nextItem = NULL;
        } else {
            // otherwise we insert the item between two items and have to adjust pointers
            item->nextItem->previousItem = newItem; // sets item's old nextItem's prevItem to item
            newItem->nextItem = item->nextItem; // shifts the old next item after the new item
        }
        item->nextItem = newItem; // sets the item's nextItem to the new item
        newItem->previousItem = item; // set the new item's prevItem to item
        newItem->data = data;
    }
    return newItem;
}

/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item) {
    char *dataPointer;
    // if the item is null, we return null
    if (item == NULL) {
        dataPointer = NULL;
        return dataPointer;
    }
    
    // the item isnt null and therefore it has data
    dataPointer = item->data;
    
    // if it comes between two items, we need to adjust pointers so the two items point at each other
    if (item->previousItem
            && item->nextItem) {
        item->previousItem->nextItem = item->nextItem;
        item->nextItem->previousItem = item->previousItem;
    } else if (item->previousItem == NULL
            && item->nextItem) {
        // if it is the head of the list, we make the next item the new head
        item->nextItem->previousItem = NULL;
        free(item);
    } else if (item->previousItem
            && item->nextItem == NULL) {
        // if it is the tail, we make the previous item the new tail
        item->previousItem->nextItem = NULL;
    }
    
    // now we free the memory
    free(item);
    return dataPointer;
}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem *list) {
    // size is a counter for size
    int size = 0;
    
    // find the head and while it is not null, increment
    ListItem *head = LinkedListGetFirst(list);
    while (head) {
        size++;
        head = head->nextItem;
    }
    return size;

}

/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetFirst(ListItem *list) {
    // if the item is null, return null
    if (list == NULL) {
        return NULL;
    }
    // if the previous item is null, we are at the head, so return the item
    if (list->previousItem == NULL) {
        return list;
    }
    // otherwise, recurse on the previous item
    return LinkedListGetFirst(list->previousItem);
}

/**
 * This function operates identically to LinkedListGetFirst(), but returns
 * the tail of a linked list.
 * 
 * @param list An element in a list.
 * @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetLast(ListItem *list) {
    // same concept as getfirst
    if (list == NULL) {
        return NULL;
    }
    // if the nextItem is null, we are at the end so return the item
    if (list->nextItem == NULL) {
        return list;
    }
    // recurse on the next item otherwise
    return LinkedListGetLast(list->nextItem);
}

/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    // if either item is null return null
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }
    
    // store one data in a temp variable
    char *tempData = firstItem->data;
    
    // swap the data
    firstItem->data = secondItem->data;
    secondItem->data = tempData;
    return SUCCESS;
}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem *list) {
    // if the list is null return error
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    
    // otherwise start at the head and print all the data until the tail
    ListItem *head = LinkedListGetFirst(list);
    printf("[");
    while (head != NULL) {
        if (head->nextItem) {
            printf("%s, ", head->data);
        } else {
            printf("%s]\n", head->data);
        }
        head = head->nextItem;
    }
    return SUCCESS;

}
