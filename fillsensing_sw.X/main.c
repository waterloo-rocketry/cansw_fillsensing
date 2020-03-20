#define _XTAL_FREQ 1000000

//hall sensor macros
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

typedef unsigned char uint8_t;

#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

// variable that stores current fill level
uint8_t fill_level = 0;

// function to test board; leds should flash for 1s each and cycle through
void leds(){
    TRISA &= (0b00000000);
    while(1){
        LATA5 = 1;
        LATA4 = 0;
        __delay_ms(1000);
        LATA4 = 1;
        LATA3 = 0;
        __delay_ms(1000);
        LATA3 = 1;
        LATA5 = 0;
        __delay_ms(1000);
    }
}


void pin_init(){
    // set RB and RC as input ports
    TRISB = 0b11111111;
    TRISC = 0b11111111;
    
    // enable interrupt-on-change for RB and RC on rising edge
    IOCBP = 0b00000000;
    IOCCP = 0b00000000;
    
    // disable falling edge interrupts
    IOCBN = 0b11111111;
    IOCCN = 0b11111111;
    
    // disable analog inputs
    ANSELB = 0b1111111;
    ANSELC = 0b11111111;
    
}

void update_fill(uint8_t& fill, uint8_t new_fill){
    // throw an error if a sensor that's below the fill line gets triggered again
    // otherwise update the new fill level
    if(fill > new_fill){
        // throw some sort of error
    } else { 
        fill = new_fill;
    }
}

static void __interrupt() interrupt_handler(){
    // which sensor went off, update accordingly
    if(HALL_1){
        HALL_1 = 0;
        update_fill(fill_level, 1);
    }
    if(HALL_2){
        HALL_2 = 0;
        update_fill(fill_level, 2);
    }
    if(HALL_3){
        HALL_3 = 0;
        update_fill(fill_level, 3);
    }
    if(HALL_4){
        HALL_4 = 0;
        update_fill(fill_level, 4);
    }
    if(HALL_5){
        HALL_5 = 0;
        update_fill(fill_level, 5);
    }
    if(HALL_6){
        HALL_6 = 0;
        update_fill(fill_level, 6);
    }
    if(HALL_7){
        HALL_7 = 0;
        update_fill(fill_level, 7);
    }
    if(HALL_8){
        HALL_8 = 0;
        update_fill(fill_level, 8);
    }
    if(HALL_9){
        HALL_9 = 0;
        update_fill(fill_level, 9);
    }
    if(HALL_10){
        HALL_10 = 0;
        update_fill(fill_level, 10);
    }
    if(HALL_11){
        HALL_11 = 0;
        update_fill(fill_level, 11);
    }
    if(HALL_12){
        HALL_12 = 0;
        update_fill(fill_level, 12);
    }
    if(HALL_13){
        HALL_13 = 0;
        update_fill(fill_level, 13);
    }
    if(HALL_14){
        HALL_14 = 0;
        update_fill(fill_level, 14);
    } 
}


int main(int argc, char** argv) {    
    // enable interrupt-on-change
    PIE0.IOCIE = 1;
    
    // initialize IO for pins
    pin_init();
    
    // enable global interrupts
    INTCON0.GIE = 1;
   
    return (EXIT_SUCCESS);
}