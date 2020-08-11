#ifndef ADC_H
#define ADC_H

//CSE13E Support Library
#include "BOARD.h"


#define ADC_MAX_VALUE 1023

/**
 * Initializes the ADC peripheral on the PIC32MX to sample from AN0.
 */
void AdcInit(void);

/**
 * Returns if the ADC value has changed or not. This is an event that should be used before a 
 * call to AdcRead().
 * @return True if the ADC value has changed, false otherwise.
 */
uint8_t AdcChanged(void);

/**
 * This function returns the most recent sample acquired from the ADC.
 * @return The 10-bit value sampled by the ADC for the given channel.
 */
uint16_t AdcRead(void);

#endif // ADC_H
