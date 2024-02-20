#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw (void){
    return (PORTD >> 8) & 0xf //send bit 11 to 8 to the least signigifcant bits and sets rest of the bits to 0 

}

int getbtns(void){
    return (PORTD >> 5) & 0x7
}