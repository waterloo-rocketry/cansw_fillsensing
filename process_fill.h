#ifndef PROCESS_FILL_H
#define	PROCESS_FILL_H

#include <stdint.h>
#include <xc.h>

#include "leds.h"

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

// used to see if any hall interrupts were triggered
#define HALL_FLAG_REG (IOCBF | IOCCF)

void fill_handle_interrupt(volatile uint8_t* fill);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_FILL_H */

