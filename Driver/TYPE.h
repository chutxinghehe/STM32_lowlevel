#ifndef __TYPE_H
#define __TYPE_H

#include <stdint.h>

typedef union {
    uint32_t REG ;
    struct {
        uint32_t bit_0   : 1;
        uint32_t bit_1   : 1;
        uint32_t bit_2   : 1;
        uint32_t bit_3   : 1;
        uint32_t bit_4   : 1;
        uint32_t bit_5   : 1;
        uint32_t bit_6   : 1;
        uint32_t bit_7   : 1;
        uint32_t bit_8   : 1;
        uint32_t bit_9   : 1;
        uint32_t bit_10  : 1;
        uint32_t bit_11  : 1;
        uint32_t bit_12  : 1;
        uint32_t bit_13  : 1;
        uint32_t bit_14  : 1;
        uint32_t bit_15  : 1;
        uint32_t bit_16  : 1;
        uint32_t bit_17  : 1;
        uint32_t bit_18  : 1;
        uint32_t bit_19  : 1;
        uint32_t bit_20  : 1;
        uint32_t bit_21  : 1;
        uint32_t bit_22  : 1;
        uint32_t bit_23  : 1;
        uint32_t bit_24  : 1;
        uint32_t bit_25  : 1;
        uint32_t bit_26  : 1;
        uint32_t bit_27  : 1;
        uint32_t bit_28  : 1;
        uint32_t bit_29  : 1;
        uint32_t bit_30  : 1;
        uint32_t bit_31  : 1;
    }Bits;
}__32BITS;


#endif