// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
//CSE13E Support Library
#include "BOARD.h"

//Lab specific libraries
#include "Leds.h"
#include "Adc.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING, EXTRA_CREDIT
} OvenState;

typedef struct {
    OvenState state;
    //add more members to this struct
    uint16_t initialCookTime; // used to store the time cooked
    uint16_t cookingTimeLeft; // used when cooking to change the time left
    uint16_t temperature; // temperature setting
    uint16_t buttonPressTime; // used to measure how long a button was pressed
    uint8_t mode; // used to determine what cooking mode the toaster is in
} OvenData;

// enum for the different cooking modes of the toaster
typedef enum {
    BAKE, TOAST, BROIL
} CookingStates;

// variables declared below
// consist of various flags and counters and variables for storing/keeping track of values
static OvenData ovenData;
static uint16_t TIMER_TICK = FALSE;
static uint16_t freeTime = 0;
static uint8_t adcChange = FALSE;
static uint8_t buttonEvent = BUTTON_EVENT_NONE;
static uint16_t adcValue;
static uint8_t editingTemp = FALSE;
static uint16_t storedFreeTime = 0;
static uint16_t timeTickCounter = 0;
static uint16_t LEDSInterval;
static uint16_t remainder;
static char currentLEDS;
static uint8_t inverted = FALSE;
static uint16_t tempHolder;
// **** Define any module-level, global, or external variables here ****
// constants defined below
#define SECOND 5
#define DEFAULT_TEMP 350
#define BROIL_TEMP 500
#define ALL_LEDS_ON 0xFF
#define CLEAR_LEDS 0x00
// **** Put any helper functions here ****


/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData){
    //update OLED here
    // the following store the special characters that are used to draw the oven into strings
    char toPrint[60] = "";
    char topOn[6];
    sprintf(topOn, "%s%s%s%s%s", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON);
    char topOff[6];
    sprintf(topOff, "%s%s%s%s%s", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, 
            OVEN_TOP_OFF);
    char botOn[6];
    sprintf(botOn, "%s%s%s%s%s", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, 
            OVEN_BOTTOM_ON);
    char botOff[6];
    sprintf(botOff, "%s%s%s%s%s", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, 
            OVEN_BOTTOM_OFF);
    
    // switch statement to determine what to print. The logic works as follows:
    // we have cases based on the cooking mode of the toaster
    // if the state of the oven is not in cooking or reset pending then we print the same thing
    // else, if the state is cooking or reset pending, we print with specifications to what the toaster looks
    // like when it is cooking
    // the cook times are divided by 60 to get the minute, and modulused by 60 to get the second, because
    // there are sixty seconds in a minute
    switch (ovenData.mode) {
        case BAKE:
            if (!(ovenData.state == COOKING || ovenData.state == RESET_PENDING)) {
                if (!editingTemp) {
                    sprintf(toPrint, "|%s| Mode: Bake\n|     | >Time: %d:%02d\n|-----|  Temp: %d%sF"
                            "\n|%s|", topOff, ovenData.initialCookTime/60, ovenData.initialCookTime%60,
                            ovenData.temperature, DEGREE_SYMBOL, botOff);
                } else {
                    sprintf(toPrint, "|%s| Mode: Bake\n|     |  Time: %d:%02d\n|-----| >Temp: %d%sF"
                            "\n|%s|", topOff, ovenData.initialCookTime/60, ovenData.initialCookTime%60,
                            ovenData.temperature, DEGREE_SYMBOL, botOff);
                }
            } else {
                sprintf(toPrint, "|%s| Mode: Bake\n|     |  Time: %d:%02d\n|-----|  Temp: %d%sF"
                            "\n|%s|", topOn, ovenData.cookingTimeLeft/60, ovenData.cookingTimeLeft%60,
                            ovenData.temperature, DEGREE_SYMBOL, botOn);
            }
            break;
        case TOAST:
            if (!(ovenData.state == COOKING || ovenData.state == RESET_PENDING)) {
                sprintf(toPrint, "|%s| Mode: Toast\n|     |  Time: %d:%02d\n|-----|"
                        "\n|%s|", topOff, ovenData.initialCookTime/60, ovenData.initialCookTime%60,
                         botOff);
            } else {
                sprintf(toPrint, "|%s| Mode: Toast\n|     |  Time: %d:%02d\n|-----|"
                        "\n|%s|", topOff, ovenData.cookingTimeLeft/60, ovenData.cookingTimeLeft%60,
                         botOn);
            }
            break;
        case BROIL:
            if (!(ovenData.state == COOKING || ovenData.state == RESET_PENDING)) {
                sprintf(toPrint, "|%s| Mode: Broil\n|     |  Time: %d:%02d\n|-----|  Temp: 500%sF"
                        "\n|%s|", topOff, ovenData.initialCookTime/60, ovenData.initialCookTime%60,
                        DEGREE_SYMBOL, botOff);
            } else {
                sprintf(toPrint, "|%s| Mode: Broil\n|     |  Time: %d:%02d\n|-----|  Temp: 500%sF"
                        "\n|%s|", topOn, ovenData.cookingTimeLeft/60, ovenData.cookingTimeLeft%60,
                        DEGREE_SYMBOL, botOff);
            }
            break;
    }
    
    // after determining what to print and storing it in a string
    // we clear the oled to reset it
    // draw the string on the oled
    // if we have just finished cooking and are flashing the screen to display so, we check to see
    // if the oled is invert it and invert/display normally accordingly
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(toPrint);
    if (ovenData.state == EXTRA_CREDIT) {
        if (inverted) {
            OledSetDisplayNormal();
        } else {
            OledSetDisplayInverted();
        }
    }
    // update oled to make sure changes show
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    switch (ovenData.state) {
        case SETUP:
            if (adcChange) {
                adcValue = AdcRead();
                // shifts 2 bits because there are six zeros at the end
                // ands with the mask 0000001111111100 to get the top 8 bits
                // then we shift the integer two bits to get rid of extra zeros at the end
                // thus we have isolated the top 8 bits
                adcValue = (adcValue & 0x03FC) >> 2;
                
                // if we are editing the temperature, scale the adcValue by adding 300 to get
                // within the range of desired temperatures
                // else add 1 to get within the range of desired cooking times
                if (ovenData.mode == BAKE && editingTemp) {
                    ovenData.temperature = adcValue + 300;
                } else {
                    ovenData.initialCookTime = adcValue + 1;
                    ovenData.cookingTimeLeft = ovenData.initialCookTime;
                }
                
                // update the oled
                updateOvenOLED(ovenData);
            }
            
            // if button 3 is pressed, we move to selector change pending because either we will
            // change from editing temp to editing time, or change cooking modes
            // store the free time
            if (buttonEvent & BUTTON_EVENT_3DOWN) {
                ovenData.buttonPressTime = freeTime;
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }
            
            // if button four is pressed, we start cooking
            // I store the initial cook time multiplied by 5 and divided by 8 because that converts
            // the cook time to the number of timer ticks it will take to cook, and i store the
            // remainder of the division in a remainder variable. These variables will be used to
            // keep track of when the LED bar should tick down as accurately as possible
            if (buttonEvent & BUTTON_EVENT_4DOWN) {
                storedFreeTime = freeTime;
                ovenData.state = COOKING;
                updateOvenOLED(ovenData);
                LEDS_SET(ALL_LEDS_ON);
                LEDSInterval = (ovenData.initialCookTime * 5) / 8;
                remainder = (ovenData.initialCookTime * 5) % 8;
                timeTickCounter = 0;
            }
            break;
        case SELECTOR_CHANGE_PENDING:
            // once a button 3 has been released we calculate how much time it took to do that
            // if it took 1 second or over to release and we are in bake mode, we change from
            // editing time to temperature and vice versa
            // afterwards, we update the oled and go back to the setup state
            if (buttonEvent & BUTTON_EVENT_3UP) {
                uint16_t elapsedTime = freeTime - ovenData.buttonPressTime;
                if (elapsedTime >= SECOND) {
                    if (ovenData.mode == BAKE) {
                        if (editingTemp) {
                            editingTemp = FALSE;
                        } else {
                            editingTemp = TRUE;
                        }
                    }
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                } else {
                    
                    // else, the button took less than a second to be released, and we change
                    // between modes
                    if (ovenData.mode == BROIL) {
                        ovenData.mode = BAKE;
                    } else {
                        ovenData.mode++;
                    }
                    if (ovenData.mode == BROIL) {
                        tempHolder = ovenData.temperature;
                        ovenData.temperature = 500;
                    } else if (ovenData.mode == BAKE) {
                        ovenData.temperature = tempHolder;
                    }
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                    
                }
            }
            break;
        case COOKING:
            
            // every time there is a timer tick, we check if we need to reduce the time on the oled
            // by a second, or if a led needs to go off
            if (TIMER_TICK) {
                // timeTickCounter keeps track of how many timer ticks have happened
                // if the amount is equal to the amount of timer ticks it should take for one of
                // the leds to turn off, then it turns off an LED. We occasionally add one to the
                // # of ticks it takes to turn off an LED because we only have 8 LEDs to represent
                // the progress bar and time is not always divisible by 8. Thus, the remaining
                // after a division by 8 are distributed evenly among the the turning off of each
                // LED, so it represents as close to 1/8 of the time as we can get
                timeTickCounter++;
                if ((remainder > 0 && timeTickCounter == LEDSInterval + 1) || 
                        (remainder == 0 && timeTickCounter == LEDSInterval)) {
                    currentLEDS = LEDS_GET();
                    timeTickCounter = 0;
                    remainder--;
                    LEDS_SET(currentLEDS << 1);
                }
                
                // if the cook time is 0, we go to the finished, flashing extra credit mode
                if (ovenData.cookingTimeLeft == 0) {
                    ovenData.cookingTimeLeft = ovenData.initialCookTime;
                    ovenData.state = EXTRA_CREDIT;
                    updateOvenOLED(ovenData);
                    LEDS_SET(CLEAR_LEDS);
                    break;
                }
                
                // if the freeTime - the free time that was stored is divisible by 5, that means a
                // second has passed and it is time to change the oled
                if ((freeTime - storedFreeTime) % 5 == 0) {
                    ovenData.cookingTimeLeft--;
                    updateOvenOLED(ovenData);
                }
            }
            
            // if button 4 is pressed, it means the user could want to reset the cook time and we
            // go to reset pending mode
            if (buttonEvent & BUTTON_EVENT_4DOWN) {
                ovenData.state = RESET_PENDING;
                ovenData.buttonPressTime = freeTime;
            }
            break;
        case RESET_PENDING:
            
            // while we determine if a timer is reset, there is a possibility that a
            // second could pass or a LED could turn off in the time it takes the button to
            // be pressed. Because of this the code from the cooking state is added to ensure
            // the oled updates accordingly if that is the case
            // otherwise, if the button is held for a second or more then the timer resets and
            // if it is held and released for less than a second the we go back to the cooking
            // state
            if (TIMER_TICK) {
                timeTickCounter++;
                if ((remainder > 0 && timeTickCounter == LEDSInterval + 1) || 
                        (remainder == 0 && timeTickCounter == LEDSInterval)) {
                    currentLEDS = LEDS_GET();
                    timeTickCounter = 0;
                    remainder--;
                    LEDS_SET(currentLEDS << 1);
                }
                if ((freeTime - storedFreeTime) % 5 == 0) {
                    if (ovenData.cookingTimeLeft) {
                        ovenData.cookingTimeLeft--;
                        updateOvenOLED(ovenData);
                    }
                }
                if (freeTime - ovenData.buttonPressTime >= SECOND) {
                    ovenData.cookingTimeLeft = ovenData.initialCookTime;
                    ovenData.state = SETUP;
                    updateOvenOLED(ovenData);
                    LEDS_SET(CLEAR_LEDS);
                    break;
                }
            }
            if (buttonEvent & BUTTON_EVENT_4UP && (freeTime - ovenData.buttonPressTime < SECOND)) {
                    ovenData.state = COOKING;
            }
            break;
        case EXTRA_CREDIT:
            
            // extra credit case
            // when cooking is done it routes here, and if the screen looks normal it becomes
            // inverted, otherwise if it is inverted it becomes normal, creating a flashing effect.
            // this is done with a flag
            if (TIMER_TICK) {
                if (inverted) {
                    inverted = FALSE;
                } else {
                    inverted = TRUE;
                }
                updateOvenOLED(ovenData);
            }
            if (buttonEvent & BUTTON_EVENT_4UP) {
                inverted = TRUE;
                updateOvenOLED(ovenData);
                ovenData.state = SETUP;
                updateOvenOLED(ovenData);
            }
            break;
    }
}


int main()
{
    BOARD_Init();

     //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
   
    printf("Welcome to jwang456's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    ovenData.buttonPressTime = 0;
    ovenData.initialCookTime = 1;
    ovenData.cookingTimeLeft = 1;
    ovenData.temperature = DEFAULT_TEMP;
    ovenData.state = SETUP;
    ovenData.mode = BAKE;
    
    OledInit();
    ButtonsInit();
    AdcInit();
    LEDS_INIT();
    
    updateOvenOLED(ovenData);
    while (1){
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
        if (buttonEvent != BUTTON_EVENT_NONE || adcChange || TIMER_TICK) {
            runOvenSM();
            buttonEvent = BUTTON_EVENT_NONE;
            adcChange = FALSE;
            TIMER_TICK = FALSE;
        }
    };
}


/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    // set Timer_tick to true
    // increment free time
    TIMER_TICK = TRUE;
    freeTime++;
}


/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    
    //add event-checking code here
    adcChange = AdcChanged();
    buttonEvent = ButtonsCheckEvents();
}