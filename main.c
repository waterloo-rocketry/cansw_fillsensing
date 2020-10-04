// TODO(wendi): init external oscillator, then change this to 12MHz
#define _XTAL_FREQ 1000000

#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "canlib/pic18f26k83/pic18f26k83_timer.h"
#include "process_fill.h"
#include "leds.h"

// variable that stores current fill level
volatile uint8_t fill_level = 0;

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

// top level ISR
static void __interrupt() interrupt_handler() {
    if(HALL_FLAG_REG != 0){
        fill_handle_interrupt(&fill_level);
    }
    
    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

int main(int argc, char** argv) {
    // enable interrupt-on-change
    PIE0bits.IOCIE = 1;

    // initialize pins, interrupts
    pin_init();

    // enable global interrupts
    INTCON0bits.GIE = 1;

    // initialize timer
    timer0_init();
    
    // initialize misc variables
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
