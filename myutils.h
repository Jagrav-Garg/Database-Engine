#include <stdlib.h>
#include <stdint.h>

#ifndef MYUTILS_H
#define MYUTILS_H

#define PAGE_SIZE 4096
#define TOTAL_PAGES 100


typedef struct row {
    int roll;
    char name[28];
} Row;



#define ROWS_PER_PAGE 128
#define BITMAP_SIZE (ROWS_PER_PAGE / 16)

typedef struct {
    Row rows[ROWS_PER_PAGE];    
} Page;

typedef struct {
    Page* pages[TOTAL_PAGES];
    uint16_t bitmap[TOTAL_PAGES][BITMAP_SIZE];
    uint8_t active_rows[TOTAL_PAGES];
} table;


//bitmap functions to manage row deletion flag

int is_active(uint16_t* bm, int i);
void mark_active(uint16_t* bm, int i);
void mark_inactive(uint16_t* bm, int i);


#endif