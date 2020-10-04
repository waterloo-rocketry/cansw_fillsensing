#include "process_fill.h"


void update_fill(volatile uint8_t* fill, uint8_t new_fill) {
    // indicator LED
    RED = RED == 1 ? 0 : 1;

    // update the fill level
    *fill = new_fill;
}

// TODO(wendi): investigate better interpolation algorithm
void fill_handle_interrupt(volatile uint8_t* fill) {
    // check which sensor went off, update accordingly
    if (HALL_1_FLAG) {
        HALL_1_FLAG = 0;
        update_fill(fill, 1);
    } else if (HALL_2_FLAG) {
        HALL_2_FLAG = 0;
        update_fill(fill, 2);
    } else if (HALL_3_FLAG) {
        HALL_3_FLAG = 0;
        update_fill(fill, 3);
    } else if (HALL_4_FLAG) {
        HALL_4_FLAG = 0;
        update_fill(fill, 4);
    } else if (HALL_5_FLAG) {
        HALL_5_FLAG = 0;
        update_fill(fill, 5);
    } else if (HALL_6_FLAG) {
        HALL_6_FLAG = 0;
        update_fill(fill, 6);
    } else if (HALL_7_FLAG) {
        HALL_7_FLAG = 0;
        update_fill(fill, 7);
    } else if (HALL_8_FLAG) {
        HALL_8_FLAG = 0;
        update_fill(fill, 8);
    } else if (HALL_9_FLAG) {
        HALL_9_FLAG = 0;
        update_fill(fill, 9);
    } else if (HALL_10_FLAG) {
        HALL_10_FLAG = 0;
        update_fill(fill, 10);
    } else if (HALL_11_FLAG) {
        HALL_11_FLAG = 0;
        update_fill(fill, 11);
    } else if (HALL_12_FLAG) {
        HALL_12_FLAG = 0;
        update_fill(fill, 12);
    } else if (HALL_13_FLAG) {
        HALL_13_FLAG = 0;
        update_fill(fill, 13);
    } else if (HALL_14_FLAG) {
        HALL_14_FLAG = 0;
        update_fill(fill, 14);
    }
}


