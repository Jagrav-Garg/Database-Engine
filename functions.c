#include "functions.h"

// function to search for a specific row in table
void search_table(table* table, int roll){
    
    // loop over all pages
    for (int i = 0; i < TOTAL_PAGES; i++){
        Page* page = table->pages[i];
        
        // checks if page is empty or not
        if (!page || table->active_rows[i] == 0) continue;

        // check gets bitmap for rows of that page
        uint16_t* bm = table->bitmap[i];

        // loop over all rows
        for (int j = 0; j < ROWS_PER_PAGE; j++){
            
            // check if row contains any data or not
            if (!is_active(bm, j)) continue;

            Row row = page->rows[j];
            
            if (row.roll == roll) {
                printf("Page Number: %d\nRow Number: %d\nRoll: %d\nName: %s", i, j, roll, row.name);
            }
        }


    }
}

// function to print all rows in table
void print_table(table* table){
    

    for (int i = 0; i < TOTAL_PAGES; i++){
        Page* page = table->pages[i];
        
        if (!page || table->active_rows[i] == 0) continue;

        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){
            
            // check if row contains data or not
            if (is_active(bm, j)) {
                Row* row = &page->rows[j];
                printf("Page Number: %d, Row Number: %d, Roll: %d, Name: %s\n", i, j, row->roll, row->name);
            }
        }
    }
}