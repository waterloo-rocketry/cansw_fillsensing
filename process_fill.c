#include "process_fill.h"


void update_fill(volatile uint8_t* fill, volatile uint8_t* direction, uint8_t new_fill) {
    // indicator LED
    RED_LED = !RED_LED;

    // update the fill direction
    if (new_fill > *fill){
        *direction = FILLING;
    }
    else if (new_fill < *fill){
        *direction = EMPTYING;
    }
    // update the fill level
    *fill = new_fill;
}

// TODO(wendi): investigate better interpolation algorithm
void fill_handle_interrupt(volatile uint8_t* fill, volatile uint8_t* direction) {
    // check which sensor went off, update accordingly
    if (HALL_1_FLAG) {
        HALL_1_FLAG = 0;
        update_fill(fill, direction, 1);
    } else if (HALL_2_FLAG) {
        HALL_2_FLAG = 0;
        update_fill(fill, direction, 2);
    } else if (HALL_3_FLAG) {
        HALL_3_FLAG = 0;
        update_fill(fill, direction, 3);
    } else if (HALL_4_FLAG) {
        HALL_4_FLAG = 0;
        update_fill(fill, direction, 4);
    } else if (HALL_5_FLAG) {
        HALL_5_FLAG = 0;
        update_fill(fill, direction, 5);
    } else if (HALL_6_FLAG) {
        HALL_6_FLAG = 0;
        update_fill(fill, direction, 6);
    } else if (HALL_7_FLAG) {
        HALL_7_FLAG = 0;
        update_fill(fill, direction, 7);
    } else if (HALL_8_FLAG) {
        HALL_8_FLAG = 0;
        update_fill(fill, direction, 8);
    } else if (HALL_9_FLAG) {
        HALL_9_FLAG = 0;
        update_fill(fill, direction, 9);
    } else if (HALL_10_FLAG) {
        HALL_10_FLAG = 0;
        update_fill(fill, direction, 10);
    } else if (HALL_11_FLAG) {
        HALL_11_FLAG = 0;
        update_fill(fill, direction, 11);
    } else if (HALL_12_FLAG) {
        HALL_12_FLAG = 0;
        update_fill(fill, direction, 12);
    } else if (HALL_13_FLAG) {
        HALL_13_FLAG = 0;
        update_fill(fill, direction, 13);
    } else if (HALL_14_FLAG) {
        HALL_14_FLAG = 0;
        update_fill(fill, direction, 14);
    }
}


