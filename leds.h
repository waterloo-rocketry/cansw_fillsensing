#ifndef LEDS_H
#define	LEDS_H

#include <xc.h>
#include <stdint.h>

#include "canlib/pic18f26k83/pic18f26k83_timer.h"

// QOL LED macros
#define WHITE LATA3
#define BLUE LATA4
#define RED LATA5

// function to test board; red and white LEDs should alternate every second
void leds();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

