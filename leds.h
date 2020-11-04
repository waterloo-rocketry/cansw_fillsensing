#ifndef LEDS_H
#define	LEDS_H

#include <xc.h>
#include <stdint.h>

#include "canlib/pic18f26k83/pic18f26k83_timer.h"

// QOL LED macros
#define WHITE_LED LATA3
#define BLUE_LED LATA4
#define RED_LED LATA5

// function to test board; red and white LEDs should alternate every second
void leds();

#endif
