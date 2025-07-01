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

void delete_table(table* table, int roll){
    
    for (int i = 0; i < TOTAL_PAGES; i++){// Traverse through all pages
        Page* page = table->pages[i];
        // If the page is NULL or has no active rows, skip it
        if (!page || table->active_rows[i] == 0) continue;
        // Get the bitmap array for the current page, where each bit represents the status of a row 
        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){// Traverse through all rows in the page
            // Check if the row is active
            if (!is_active(bm, j)) continue;
            Row row = page->rows[j];
            
            if (row.roll == roll) {// If the roll number matches, delete the row
                table->active_rows[i]--;// Decrease the count of active rows in the page
                mark_inactive(bm, j);// Mark the row as inactive in the bitmap
                row.roll = 3*row.roll+1;
                while(row.roll % 2 == 0) {// While the roll number is even, divide it by 2
                    row.roll /= 2;
                }
                // Changing the roll number by multiplying it by 3 and adding 1, then reducing it by 2 so that the roll number gets encrypted
                // This is a simple encryption technique to ensure that the roll number is not easily guessable
                for(int k = 1; k < 28; k++) {
                    row.name[k] = '*'; // Mask the name with asterisks
                }
                row.name[0] = '\0'; // Clear the name field
                // Mask the name with asterisks to ensure that the name is not easily guessable
                return;
            }
        }
    }
    printf("Roll number %d not found in the table.\n", roll);// If the roll number is not found, print a message

}