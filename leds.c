#include "leds.h"

// function to test board; red and white LEDs should alternate every second
void leds() {
    uint32_t last_millis = millis();
    while(1) {
        if (millis() - 1000 > last_millis){
            last_millis = millis();
            RED_LED = !RED_LED;
            WHITE_LED = !WHITE_LED;
        }
    }
}