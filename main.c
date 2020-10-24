// TODO(wendi): init external oscillator, then change this to 12MHz
#include <stdint.h>
#include "mcc_generated_files/mcc.h"

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"
#include "canlib/pic18f26k83/pic18f26k83_timer.h"

#include "process_fill.h"
#include "leds.h"

#define MAX_LOOP_TIME_DIFF_ms 1000

// variable that stores current fill level
volatile uint8_t fill_level = 0;
volatile uint8_t direction = 0;

// Memory pool for CAN transmit buffer
uint8_t tx_pool[100];

// Don't need to receive messages?
static void can_msg_handler(const can_msg_t *msg) {};

void pin_init() {
    // set RA as an output port (for LEDs)
    TRISA = 0b00000000;

    // set RB and RC as input ports
    TRISB = 0b00111111;
    TRISC = 0b11111111;

    // enable interrupt-on-change for RB and RC on falling edge
    IOCBN = 0b00111111;
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
    
    // handle CAN interrupts
    if (PIR5) {
        can_handle_interrupt();
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
    
    /***********set up CAN**********/

    // Set up CAN TX
    TRISC0 = 0;
    RC0PPS = 0x33;

    // Set up CAN RX
    TRISC1 = 1;
    ANSELC1 = 0;
    CANRXPPS = 0x11;

    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);

    can_init(&can_setup, can_msg_handler);

    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);
    
    // initialize misc variables
    fill_level = 0;
    uint32_t last_millis = millis();

    // main loop
    while (true) {
        
        if(millis() > last_millis + MAX_LOOP_TIME_DIFF_ms) {
            last_millis = millis();
            
            // heartbeat LED
            BLUE = !BLUE;
            
            can_msg_t fill_msg;
            build_fill_msg(millis(),
                           fill_level,
                           direction,
                           &fill_msg);
            
            txb_enqueue(&fill_msg);
        }
        
        // send queued messages
        txb_heartbeat();

    }

    return (EXIT_SUCCESS);
}
