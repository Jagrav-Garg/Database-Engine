#include <stdio.h>
#include "myutils.h"
#include "functions.h"


int main(){
    table* my_table= create_table(); // Create a new table
    if (!my_table) {
        return 1; // If table creation fails, exit the program
    }
    int choice;
    while(1){
        printf("\nMenu:\n");
        printf("1. Insert Row\n");
        printf("2. Search Row\n");
        printf("3. Print Table\n");
        printf("4. Delete Row\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // Insert a new row into the table
            // Prompt user for roll number and name
            printf("Inserting a new row...\n");
            int roll; 
            char name[28]; 
            printf("Enter Roll Number: ");
            scanf("%d", &roll);
            if( roll <= 0) { // Check if the roll number is a positive integer
                printf("Invalid roll number. Roll number is a positive integer.\n");
                continue; // Skip this iteration if the roll number is invalid
            }
            if( search_table(my_table, roll)) { // Check if the roll number already exists in the table
                printf("\nRoll number %d already exists. Please enter a unique roll number.\n", roll);
                continue; // Skip this iteration if the roll number already exists
            }
            printf("Enter Name: ");
            getchar();  // Consume newline character left by previous scanf
            fgets(name, sizeof(name), stdin); // Use fgets to read the name with spaces
            if(!adjust_name(name, MAX_NAME_LENGTH)) { // Adjust the name to ensure it is null-terminated and does not exceed max length
                printf("Invalid name. Please enter a name with less than %d characters.\n", MAX_NAME_LENGTH);
                continue; // Skip this iteration if the name is invalid
            }
            insert_row(my_table, roll, name); // Call the function to insert the new row
            break;

        case 2:
            // Search for a row in the table
            printf("Enter Roll Number to Search: ");
            scanf("%d", &roll);
            if (!search_table(my_table, roll)) {
                printf("Roll number %d not found.⛔\n", roll);
            }
            break;

        case 3:
            // Print the entire table
            print_table(my_table);
            break;

        case 4:
            // Delete a row from the table
            printf("Enter Roll Number to Delete: ");
            scanf("%d", &roll);
            delete_row(my_table, roll);
            break;

        case 5:
            // Exit the program
            printf("Exiting...\n");
            for (int i = 0; i < TOTAL_PAGES; i++) {// Free all allocated pages in the table
            // Check if the page is not NULL before freeing it
                if (my_table->pages[i]) {
                    free(my_table->pages[i]);
                }
            }
            free(my_table);// Free the table itself
            return 0;

        default:
            break;
        }
    }
}