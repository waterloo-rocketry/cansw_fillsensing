#define _XTAL_FREQ 1000000

//hall sensor macros
#define HALL_1 RC5
#define HALL_2 RC7
#define HALL_3 RB1
#define HALL_4 RB3
#define HALL_5 RB5
#define HALL_6 RC3
#define HALL_7 RC1
#define HALL_8 RC0
#define HALL_9 RC2
#define HALL_10 RB4
#define HALL_11 RB2
#define HALL_12 RB0
#define HALL_13 RC6
#define HALL_14 RC4

#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

//function to test board; leds should flash for 1s each and cycle
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
    //set RB and RC as input ports
    TRISB &= 0b11111111;
    TRISC &= 0b11111111;
    
    //enable interrupt-on-change for RB and RC on rising edge
    IOCBP &= 0b00000000;
    IOCCP &= 0b00000000;
    
    //disable falling edge interrupts
    IOCBN &= 0b11111111;
    IOCCN &= 0b11111111;
    
}

static void __interrupt() interrupt_handler(){
    
}


int main(int argc, char** argv) {
    //enable global interrupts
    INTCON0.GIE = 1;
    
    //enable interrupt-on-change
    PIE0.IOCIE = 1;
    
    //initialize I/O for pins
    pin_init();
   
    return (EXIT_SUCCESS);
}