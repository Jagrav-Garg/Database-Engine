#include <stdlib.h>
#include <stdint.h>

#ifndef MYUTILS_H
#define MYUTILS_H

#define PAGE_SIZE 4096
#define TOTAL_PAGES 100


typedef struct row {
    int roll;
    char name[27];
} Row;



const size_t ROW_SIZE = sizeof(Row);
#define ROWS_PER_PAGE 128

typedef struct {
    Row rows[ROWS_PER_PAGE];
    uint16_t bitmap[8];
    int num_rows;
} Page;

typedef struct {
    Page* pages[TOTAL_PAGES];
    int total_pages;
    int next_free_page; // last unfilled page
} table;


//bitmap functions to manage row deletion flag

int is_active(uint16_t* bm, int i);
void mark_active(uint16_t* bm, int i);
void mark_inactive(uint16_t* bm, int i);


#endif