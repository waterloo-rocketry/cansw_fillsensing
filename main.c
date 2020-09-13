// TODO(wendi): init external oscillator, then change this to 12MHz
#define _XTAL_FREQ 1000000

// hall sensor interrupt flag macros
#define HALL_1_FLAG IOCCF5
#define HALL_2_FLAG IOCCF7
#define HALL_3_FLAG IOCBF1
#define HALL_4_FLAG IOCBF3
#define HALL_5_FLAG IOCBF5
#define HALL_6_FLAG IOCCF3
#define HALL_7_FLAG IOCCF1
#define HALL_8_FLAG IOCCF0
#define HALL_9_FLAG IOCCF2
#define HALL_10_FLAG IOCBF4
#define HALL_11_FLAG IOCBF2
#define HALL_12_FLAG IOCBF0
#define HALL_13_FLAG IOCCF6
#define HALL_14_FLAG IOCCF4

// QOL LED macros
#define WHITE LATA3
#define BLUE LATA4
#define RED LATA5

#define WHITE_LED_ON() (LATA3 = 0)
#define WHITE_LED_OFF() (LATA3 = 1)
#define BLUE_LED_ON() (LATA4 = 0)
#define BLUE_LED_OFF() (LATA4 = 1)
#define RED_LED_ON() (LATA5 = 0)
#define RED_LED_OFF() (LATA5 = 1)

#include <stdlib.h>

#include "canlib/pic18f26k83/pic18f26k83_timer.h"

#include "mcc_generated_files/mcc.h"

// variable that stores current fill level
volatile uint8_t fill_level = 0;

// function to test board; red and white LEDs should alternate every second

void leds() {
    uint32_t last_millis = millis();
    while(1) {
        if (millis() - 1000 > last_millis){
            last_millis = millis();
            RED = RED == 1 ? 0 : 1;
            WHITE = WHITE == 1 ? 0 : 1;
        }
    }
}

void pin_init() {
    // set RA as an output port (for LEDs)
    TRISA = 0b00000000;


    // set RB and RC as input ports
    TRISB = 0b11111111;
    TRISC = 0b11111111;


    // enable interrupt-on-change for RB and RC on falling edge
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
    // indicator LED
    RED = RED == 1 ? 0 : 1;

    // update the fill level
    *fill = new_fill;
}

// TODO(wendi): investigate better interpolation algorithm
static void __interrupt() interrupt_handler() {
    // check which sensor went off, update accordingly
    if (HALL_1_FLAG) {
        HALL_1_FLAG = 0;
        update_fill(&fill_level, 1);
    } else if (HALL_2_FLAG) {
        HALL_2_FLAG = 0;
        update_fill(&fill_level, 2);
    } else if (HALL_3_FLAG) {
        HALL_3_FLAG = 0;
        update_fill(&fill_level, 3);
    } else if (HALL_4_FLAG) {
        HALL_4_FLAG = 0;
        update_fill(&fill_level, 4);
    } else if (HALL_5_FLAG) {
        HALL_5_FLAG = 0;
        update_fill(&fill_level, 5);
    } else if (HALL_6_FLAG) {
        HALL_6_FLAG = 0;
        update_fill(&fill_level, 6);
    } else if (HALL_7_FLAG) {
        HALL_7_FLAG = 0;
        update_fill(&fill_level, 7);
    } else if (HALL_8_FLAG) {
        HALL_8_FLAG = 0;
        update_fill(&fill_level, 8);
    } else if (HALL_9_FLAG) {
        HALL_9_FLAG = 0;
        update_fill(&fill_level, 9);
    } else if (HALL_10_FLAG) {
        HALL_10_FLAG = 0;
        update_fill(&fill_level, 10);
    } else if (HALL_11_FLAG) {
        HALL_11_FLAG = 0;
        update_fill(&fill_level, 11);
    } else if (HALL_12_FLAG) {
        HALL_12_FLAG = 0;
        update_fill(&fill_level, 12);
    } else if (HALL_13_FLAG) {
        HALL_13_FLAG = 0;
        update_fill(&fill_level, 13);
    } else if (HALL_14_FLAG) {
        HALL_14_FLAG = 0;
        update_fill(&fill_level, 14);
    }
}

int main(int argc, char** argv) {
    // enable interrupt-on-change
    PIE0bits.IOCIE = 1;

    // initialize pins, interrupts
    pin_init();

    // enable global interrupts
    INTCON0bits.GIE = 1;

    timer0_init();
    
    fill_level = 0;
    uint32_t last_millis = millis();

    // keep the board running and listening for interrupts
    while (true) {
        // heartbeat LED
        if (millis() - 1000 > last_millis){
            last_millis = millis();
            BLUE = BLUE == 1 ? 0 : 1;
        }
    }

    return (EXIT_SUCCESS);
}
