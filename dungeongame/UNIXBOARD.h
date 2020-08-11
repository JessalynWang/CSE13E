/* 
 * File:   UNIXBOARD.h
 * Author: Max Dunne
 *
 * Created on December 19, 2012, 2:08 PM
 */

#ifndef UNIXBOARD_H
#define	UNIXBOARD_H


/*******************************************************************************
 * PUBLIC #INCLUDES                                                           *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

 typedef enum _BOOL { FALSE = 0, TRUE } BOOL;


// Define some standard error codes.
enum {
    SIZE_ERROR = -1,
    STANDARD_ERROR,
    SUCCESS
};





/**
 * This should be used when there is an
 * unrecoverable error onboard, like when a subsystem fails to initialize.
 */
#define FATAL_ERROR() exit(EXIT_FAILURE)


#endif	/* UNIXBOARD_H */
