#include "myutils.h"

// bitmap functions

int is_active(uint16_t* bm, int i) {
    return (bm[i / 16] >> (i % 16)) & 1;
}

void mark_active(uint16_t* bm, int i) {
    bm[i / 16] |= (1 << (i % 16));
}

void mark_inactive(uint16_t* bm, int i) {
    bm[i / 16] &= ~(1 << (i % 16));
}