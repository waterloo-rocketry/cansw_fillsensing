#define _XTAL_FREQ 1000000

// hall sensor macros
#define HALL_1 IOCCF5
#define HALL_2 IOCCF7
#define HALL_3 IOCBF1
#define HALL_4 IOCBF3
#define HALL_5 IOCBF5
#define HALL_6 IOCCF3
#define HALL_7 IOCCF1
#define HALL_8 IOCCF0
#define HALL_9 IOCCF2
#define HALL_10 IOCBF4
#define HALL_11 IOCBF2
#define HALL_12 IOCBF0
#define HALL_13 IOCCF6
#define HALL_14 IOCCF4

// QOL led macros
#define WHITE LATA3
#define BLUE LATA4
#define RED LATA5

typedef unsigned char uint8_t;

#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

// variable that stores current fill level
volatile uint8_t fill_level = 92;

// function to test board; leds should flash for 1s each and cycle through

void leds() {
    while (1) {
        RED = 1;
        BLUE = 0;
        __delay_ms(1000);
        BLUE = 1;
        WHITE = 0;
        __delay_ms(1000);
        WHITE = 1;
        RED = 0;
        __delay_ms(1000);
    }
}

void pin_init() {
    // set RB and RC as input ports
    TRISB = 0b11111111;
    TRISC = 0b11111111;


    // enable interrupt-on-change for RB and RC on rising edge
    IOCBN = 0b11111111;
    IOCCN = 0b11111111;


    // disable analog inputs
    ANSELB = 0b00000000;
    ANSELC = 0b00000000;

    // clear flags (just in case)
    IOCCF = 0b00000000;
    IOCBF = 0b00000000;

}

void update_fill(volatile uint8_t* fill, uint8_t new_fill) {
    // update the fill level
    *fill = new_fill;
}

static void __interrupt() interrupt_handler() {
    // which sensor went off, update accordingly
    if (HALL_1) {
        HALL_1 = 0;
        update_fill(&fill_level, 1);
    } else if (HALL_2) {
        HALL_2 = 0;
        update_fill(&fill_level, 2);
    } else if (HALL_3) {
        HALL_3 = 0;
        update_fill(&fill_level, 3);
    } else if (HALL_4) {
        HALL_4 = 0;
        update_fill(&fill_level, 4);
    } else if (HALL_5) {
        HALL_5 = 0;
        update_fill(&fill_level, 5);
    } else if (HALL_6) {
        HALL_6 = 0;
        update_fill(&fill_level, 6);
    } else if (HALL_7) {
        HALL_7 = 0;
        update_fill(&fill_level, 7);
    } else if (HALL_8) {
        HALL_8 = 0;
        update_fill(&fill_level, 8);
    } else if (HALL_9) {
        HALL_9 = 0;
        update_fill(&fill_level, 9);
    } else if (HALL_10) {
        HALL_10 = 0;
        update_fill(&fill_level, 10);
    } else if (HALL_11) {
        HALL_11 = 0;
        update_fill(&fill_level, 11);
    } else if (HALL_12) {
        HALL_12 = 0;
        update_fill(&fill_level, 12);
    } else if (HALL_13) {
        HALL_13 = 0;
        update_fill(&fill_level, 13);
    } else if (HALL_14) {
        HALL_14 = 0;
        update_fill(&fill_level, 14);
    }
}

int main(int argc, char** argv) {
    // enable interrupt-on-change
    PIE0bits.IOCIE = 1;

    // initialize IO for pins
    pin_init();

    // enable global interrupts
    INTCON0bits.GIE = 1;

    //for LED testing
    TRISA = 0b00000000;
    WHITE = 1;
    BLUE = 1;
    RED = 1;

    fill_level = 0;

    // keep the board running and listening for interrupts
    while (true) {
        BLUE = 0;
        __delay_ms(1000);
        BLUE = 1;
        __delay_ms(1000);
    }

    return (EXIT_SUCCESS);
}