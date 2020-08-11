/*
 * File:   BOARD.h
 * Author: Max Dunne
 *
 * Created on December 19, 2012, 2:08 PM
 * 
 * Much of the odder code come directly from the microchip peripheral library as reinventing the wheel seemed
 * not necessary
 */

#include "BOARD.h"

// Microchip Libraries
#ifdef PIC32
#include <xc.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// no legacy libc
#ifdef PIC32
#ifdef __C32_LEGACY_LIBC__
#error CSE13E Can not be done with legacy libc. Ensure project properties -> XC32 (Global Options) -> Use legacy libc is UN checked. 
#endif
#endif

/*******************************************************************************
 * PRAGMAS                                                                     *
 ******************************************************************************/
// Configuration Bits
// SYSCLK = 80MHz
// PBCLK  = 20MHz
// using POSC w/ PLL, XT mode
#ifdef PIC32
#pragma config FPBDIV     = DIV_4
#pragma config FPLLIDIV   = DIV_2     // Set the PLL input divider to 2, seems to
#pragma config IESO       = OFF       // Internal/External Switch
#pragma config POSCMOD    = XT        // Primary Oscillator Configuration for XT osc mode
#pragma config OSCIOFNC   = OFF       // Disable clock signal output
#pragma config FCKSM      = CSECMD    // Clock Switching and Monitor Selection
#pragma config WDTPS      = PS1       // Specify the watchdog timer interval (unused)
#pragma config FWDTEN     = OFF       // Disable the watchdog timer
#pragma config ICESEL     = ICS_PGx2  // Allow for debugging with the Uno32
#pragma config PWP        = OFF       // Keep the program flash writeable
#pragma config BWP        = OFF       // Keep the boot flash writeable
#pragma config CP         = OFF       // Disable code protect
#pragma config FNOSC 		= PRIPLL	//Oscillator Selection Bits
#pragma config FSOSCEN 		= OFF		//Secondary Oscillator Enable
#pragma config FPLLMUL 		= MUL_20	//PLL Multiplier
#pragma config FPLLODIV 	= DIV_1 	//System PLL Output Clock Divid
#endif
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define SYSTEM_CLOCK 80000000L
#define PB_CLOCK (SYSTEM_CLOCK / 4)
#define QUEUESIZE 512
//#define TurnOffAndClearInterrupt(Name) INTEnable(Name,INT_DISABLED); INTClearFlag(Name)
#define TurnPortToInput(Tris) Tris=0xFFFF


//#define LAB10_READ_OVERWRITE
/*******************************************************************************
 * PRIVATE DATATYPES                                                           *
 ******************************************************************************/



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
void SERIAL_Init(void);

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * Function: BOARD_Init(void)
 * @param None
 * @return None
 * @brief Initializes the board for 80MHz SYSCLK and 20MHz PBCLK.
 */
void BOARD_Init() {
#ifdef PIC32
    //seeds the random number generator with the time
    char seed1[] = __TIME__;
    unsigned int seed2 = (((unsigned int) (seed1[7] ^ seed1[2])) << 8) | ((unsigned int) (seed1[4] ^ seed1[6]));
    srand(seed2);

    //enables the interrupt system in the new style
    
    //INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR); 
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));
    INTCONSET = _INTCON_MVEC_MASK;
    
    //INTEnableInterrupts();
    int status;
    asm volatile("ei    %0" : "=r"(status));
    // Initialize for serial
    SERIAL_Init();
#endif
}

/**
 * Function: BOARD_End(void)
 * @param None
 * @return None
 * @brief shuts down all peripherals except for serial and A/D. Turns all pins
 * into input
 * @author Max Dunne, 2013.09.20  */
void BOARD_End() {
#ifdef PIC32
    // set all interrupt enable flags to zero
    IEC0 = 0;
    IEC1 = 0;

    //set all flags to zero
    IFS0 = 0;
    IFS1 = 0;

    // disable timer interrupts, clear flags and turn off module
    T1CON = 0;
    T2CON = 0;
    T3CON = 0;
    T4CON = 0;
    T5CON = 0;


    // disable input capture interrupts, clear flags and turn off module
    IC1CONCLR = _IC1CON_ICM_MASK;
    IC2CONCLR = _IC2CON_ICM_MASK;
    IC3CONCLR = _IC3CON_ICM_MASK;
    IC4CONCLR = _IC4CON_ICM_MASK;
    IC5CONCLR = _IC5CON_ICM_MASK;

    // disable output compare interrupts, clear flags and turn off module
    OC1CONCLR = _OC1CON_ON_MASK;
    OC2CONCLR = _OC2CON_ON_MASK;
    OC3CONCLR = _OC3CON_ON_MASK;
    OC4CONCLR = _OC4CON_ON_MASK;
    OC5CONCLR = _OC5CON_ON_MASK;

    // disable I2C interrupts, clear flags and turn off module
    I2C1CONCLR = _I2C1CON_ON_MASK;
    I2C2CONCLR = _I2C2CON_ON_MASK;

    //disable spi interrupts, clear flags and turn off module
    SPI1CONCLR = _SPI1CON_ON_MASK;
    SPI2CONCLR = _SPI2CON_ON_MASK;

    // disable external interrupts, clear flags and turn off module

    // set all ports to be digital inputs
    TurnPortToInput(TRISB);
    TurnPortToInput(TRISC);
    TurnPortToInput(TRISD);
    TurnPortToInput(TRISE);
    TurnPortToInput(TRISF);
    TurnPortToInput(TRISG);

#else
    exit(0);
#endif   
}

/**
 * Function: BOARD_GetPBClock(void)
 * @param None
 * @return
 */
unsigned int BOARD_GetPBClock() {
    return PB_CLOCK;
}

/**
 * Function: BOARD_GetSysClock(void)
 * @param None
 * @return
 */
unsigned int BOARD_GetSysClock() {
    return SYSTEM_CLOCK;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function SERIAL_Init(void)
 * @param none
 * @return none
 * @brief  Initializes the UART subsystem to 115200 and sets up the circular buffer
 * @author Max Dunne, 2011.11.10 */

void SERIAL_Init(void) {
#ifdef PIC32
    // we first clear the Configs Register to ensure a blank state and peripheral is off.
    U1MODE = 0;
    U1STA = 0;
    //UARTConfigure(UART1, 0x00);

    //we then calculate the required frequency, note that this comes from plib source to avoid rounding errors
    int sourceClock = BOARD_GetPBClock() >> 3;
    int brg = sourceClock / 115200;
    brg++;
    brg >>= 1;
    brg--;
    U1BRG = brg;
    //UARTSetDataRate(UART1, PB_CLOCK, 115200);
    //UARTSetFifoMode(UART1, UART_INTERRUPT_ON_RX_NOT_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);

    //we now enable the device

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.UARTEN = 1;

    //UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX | UART_RX));
    __XC_UART = 1;
    //printf("\r\n%d\t%d",U1BRG,brg);
#endif
}



/*******************************************************************************
 * OVERRIDE FUNCTIONS                                                          *
 ******************************************************************************/

/**
 * @Function read(int handle, void *buffer, unsigned int len)
 * @param handle
 * @param buffer
 * @param len
 * @return Returns the number of characters read into buffer
 * @brief Overrides the built-in function called for scanf() to ensure proper functionality
 */
#ifdef PIC32
#ifndef LAB10_READ_OVERWRITE

int read(int handle, char *buffer, unsigned int len) {
    int i;
    if (handle == 0) {
        while (!U1STAbits.URXDA) {
            if (U1STAbits.OERR) {
                U1STAbits.OERR = 0;
            }
            continue;
        }
        i = 0;
        while (U1STAbits.URXDA) {
            char tmp = U1RXREG;
            if (tmp == '\r') {
                tmp = '\n';
            }
            *(char*) buffer++ = tmp;
            //WriteUART1(tmp);
            U1TXREG = tmp;
            i++;
        }
        return i;
    }
    return 0;
}
#endif
#endif


#ifdef BOARD_TEST

int main(void) {
    BOARD_Init();
    printf("\r\nThis stub tests SERIAL Functionality with scanf");
    printf("\r\nIt will intake integers and divide by 2");
    printf("\r\n Peripheral Clock: %d", BOARD_GetPBClock());
    printf("\r\n Peripheral Clock: %d\r\n", BOARD_GetSysClock());
    char trash;
    int input;
    while (1) {
        scanf("%d%c", &input, &trash);
        printf("\r\nEntered: %d\t/2: %d\r\n", input, input / 2);
    }
    while (1);
    return 0;
}
#endif