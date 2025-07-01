#include "functions.h"

void search_table(table* table, int roll){
    
    for (int i = 0; i < TOTAL_PAGES; i++){
        Page* page = table->pages[i];
        
        if (!page || table->active_rows[i] == 0) continue;

        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){
            
            Row row = page->rows[j];
            
            if (row.roll == roll) {
                printf("Page Number: %d\nRow Number: %d\nRoll: %d\nName: %s", i, j, roll, row.name);
            }
        }


    }
}

void print_table(table* table){
    
    for (int i = 0; i < TOTAL_PAGES; i++){
        Page* page = table->pages[i];
        
        if (!page || table->active_rows[i] == 0) continue;

        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){
            
            
            if (is_active(bm, j)) {
                Row* row = &page->rows[j];
                printf("Page Number: %d, Row Number: %d, Roll: %d, Name: %s\n", i, j, row->roll, row->name);
            }
        }
    }
}