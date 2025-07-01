#include "functions.h"

bool adjust_name(char* name, size_t max_len) {
    if (strchr(name, '\n') == NULL) {
        // Overflow occurred, clear the input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return false; // Indicate overflow
    }
    // Remove newline character from name if present
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
        len--;
    }
    if (name[len] != '\0') {
        name[len] = '\0'; // Ensure the name is null-terminated
    }
    return true; // No overflow
}


Page* create_page() { // Function to create a new page
    // Allocate memory for a new page
    Page* new_page = (Page*)malloc(sizeof(Page));
    if (!new_page) {
        printf("Not enough Memory for a page😭😭😭.\n");
        // Print relevant information if memory allocation fails
        return NULL;
    }
    for (int i = 0; i < ROWS_PER_PAGE; i++) { // Initialize all rows in the page
        new_page->rows[i].name[0] = '\0'; // Initialize the name
        new_page->rows[i].roll = 0; // Initialize the roll number
    }
    return new_page;
}

table* create_table() { // Function to create a new table
    // Allocate memory for a new table
    table* new_table = (table*)malloc(sizeof(table));
    if (!new_table) {
        printf("Not enough Memory for a table😭😭😭.\n");
        return NULL; // If memory allocation fails, print an error message and return NULL
    }
    
    for (int i = 0; i < TOTAL_PAGES; i++) {
        new_table->pages[i] = NULL; // Initialize all pages to NULL
        new_table->active_rows[i] = 0; // Initialize active rows count to 0
        for (int j = 0; j < BITMAP_SIZE; j++) {
            new_table->bitmap[i][j] = 0; // Initialize bitmap to 0
        }
    }
    
    return new_table; // Return the newly created table
}

bool search_table(table* table, int roll){
    
    for (int i = 0; i < TOTAL_PAGES; i++){
        Page* page = table->pages[i];
        
        if (!page || table->active_rows[i] == 0) continue;

        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){
            
            if(is_active(bm, j) == 0) continue; // Check if the row is active
            Row row = page->rows[j];
            
            if (row.roll == roll) {
                printf("Page Number: %d\nRow Number: %d\nRoll: %d\nName: %s", i, j, roll, row.name);
                return true; // If the roll number matches, print the row details and return true
            }
        }

    }
    return false; // If no matching row is found, return false
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

bool insert_row(table* table, int roll, const char* name){

    for (int i = 0; i < TOTAL_PAGES; i++){// Traverse through all pages
        Page* page = table->pages[i];
        if(!page){// If the page is NULL, it means it has not been allocated yet
            page = create_page(); // Create a new page
            if (!page) return false; // If page creation fails, return false
            table->pages[i] = page; // Assign the newly created page to the table
        }
        else if (table->active_rows[i] == ROWS_PER_PAGE) continue; // If the page is full, skip to the next page

        uint16_t* bm = table->bitmap[i];// Get the bitmap array for the current page, where each bit represents the status of a row
        for (int j = 0; j < ROWS_PER_PAGE; j++){// Traverse through all rows in the page
            // Check if the row is inactive
            if (!is_active(bm, j)){
                page->rows[j].roll = roll; // Insert the new row into the page
                strcpy(page->rows[j].name, name);
                mark_active(bm, j); // Mark the row as active in the bitmap
                table->active_rows[i]++;  // Increase the count of active rows in the page
                // Print a success message
                printf("✅ Inserted Row: Page Number: %d, Row Number: %d, Roll: %d, Name: %s\n", i, j, roll, name);
                return true; // Return true to indicate successful insertion
            }
        }
    }
    printf("Table is full, cannot insert new row.🙅‍♂️\n");
    // If no inactive row is found in any page, print a message indicating that the table is full and cannot insert the new row
    return false; // Return false to indicate that the insertion failed

}

void delete_row(table* table, int roll){
    
    for (int i = 0; i < TOTAL_PAGES; i++){// Traverse through all pages
        Page* page = table->pages[i];
        // If the page is NULL or has no active rows, skip it
        if (!page || table->active_rows[i] == 0) continue;
        // Get the bitmap array for the current page, where each bit represents the status of a row 
        uint16_t* bm = table->bitmap[i];

        for (int j = 0; j < ROWS_PER_PAGE; j++){// Traverse through all rows in the page
            // Check if the row is active
            if (!is_active(bm, j)) continue;
            Row* row = &(page->rows[j]);
            
            if (row->roll == roll) {// If the roll number matches, delete the row
                printf("⚠️ Deleting Row: Page Number: %d, Row Number: %d, Roll: %d, Name: %s\n", i, j, row->roll, row->name);
                table->active_rows[i]--;// Decrease the count of active rows in the page
                mark_inactive(bm, j);// Mark the row as inactive in the bitmap
                row->roll = 0; // Clear the roll number
                for(int k = 0; k < 28; k++) {
                    row->name[k] = '\0'; // Mask the name with null characters
                }
                // Mask the name with null characters to ensure that the name is not guessable
                if(table->active_rows[i] == 0) {
                    free(page); // If there are no active rows left in the page, free the page memory
                    table->pages[i] = NULL; // Set the page pointer to NULL
                }
                return;
            }
        }
    }
    printf("Roll number %d not found in the table.⛔\n", roll);// If the roll number is not found, print a message

}
