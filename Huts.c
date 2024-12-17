#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Tubig bill (whole month)
Electricity bill (whole month)
Gas (quarterly??)
Subscription (wifi included static)
NATHANIEL
*/

void file_read(char* file) {
    char buffer[1024];
    char* data;
    int COLUMN_WIDTH = 25;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    printf("\n");

    int k = -1;
    while (fgets(buffer, sizeof(buffer), file_out)) {
        if (k++ != -1) printf("%d. ", k); 
        else printf("   ");
        data = strtok(buffer, ",");
        
        int columnIndex = 0; 
        while (data != NULL) {
            printf("%-*s", COLUMN_WIDTH, data); 
            data = strtok(NULL, ",");
            columnIndex++;
        }
        printf("\n"); 
    }

    fclose(file_out);
}
void file_edit(char* file,int edit_row, char* new_row) {
    char buffer[1024];
    char **file_data = NULL;
    int currentSize = 0, capacity = 1;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }
    
    file_data = (char **)malloc(capacity * sizeof(char *));
    if (file_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    while (fgets(buffer, sizeof(buffer), file_out)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 

        char result[1024];
        int j = 0;
        
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\t') { 
                result[j++] = buffer[i]; 
            }
        }
        result[j] = '\0'; 
        strcpy(buffer, result);

        if (currentSize >= capacity) {
            capacity *= 2; 
            char **temp = realloc(file_data, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                break; 
            }
            file_data = temp; 
        }

        file_data[currentSize] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (file_data[currentSize] == NULL) {
            fprintf(stderr, "Memory allocation for string failed\n");
            break; 
        }
        
        strcpy(file_data[currentSize], buffer); 
        currentSize++; 
    }

    fclose(file_out); 

    if (edit_row < 0 || edit_row >= currentSize) {
        printf("ERROR: Invalid row number for replacement\n");
        
        for (int i = 0; i < currentSize; i++) {
            free(file_data[i]);
        }
        free(file_data);
        return;
    }

    free(file_data[edit_row]); 
    file_data[edit_row] = (char *)malloc((strlen(new_row) + 1) * sizeof(char));
    if (file_data[edit_row] == NULL) {
        fprintf(stderr, "Memory allocation for new row failed\n");
        return;
    }
    
    strcpy(file_data[edit_row], new_row); 

    FILE *file_in = fopen(file, "w"); 
    if (file_in == NULL) {
        printf("ERROR: could not open file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize; i++) {
        fprintf(file_in, "%s\n", file_data[i]); 
        free(file_data[i]); 
    }

    free(file_data); 
    fclose(file_in); 

    printf("Row %d edited successfully.\n", edit_row);
}
void file_append(char* file, char* new_row) {
    char buffer[1024];
    char **file_data = NULL;
    int currentSize = 0, capacity = 1;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    
    file_data = (char **)malloc(capacity * sizeof(char *));
    if (file_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    
    while (fgets(buffer, sizeof(buffer), file_out)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 

        
        if (currentSize >= capacity) {
            capacity *= 2; 
            char **temp = realloc(file_data, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                break; 
            }
            file_data = temp; 
        }

        
        file_data[currentSize] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (file_data[currentSize] == NULL) {
            fprintf(stderr, "Memory allocation for string failed\n");
            break; 
        }
        
        strcpy(file_data[currentSize], buffer); 
        currentSize++; 
    }

    fclose(file_out); 

    
    char **new_file_data = (char **)malloc((currentSize + 1) * sizeof(char *));
    if (new_file_data == NULL) {
        fprintf(stderr, "Memory allocation failed for new data\n");
        return;
    }

    
    for (int i = 0; i < currentSize; i++) {
        new_file_data[i] = file_data[i]; 
    }

    
    new_file_data[currentSize] = (char *)malloc((strlen(new_row) + 1) * sizeof(char));
    if (new_file_data[currentSize] == NULL) {
        fprintf(stderr, "Memory allocation for new row failed\n");
        return;
    }
    
    strcpy(new_file_data[currentSize], new_row); 

    free(file_data); 

    
    FILE *file_in = fopen(file, "w"); 
    if (file_in == NULL) {
        printf("ERROR: could not open file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize + 1; i++) {
        fprintf(file_in, "%s\n", new_file_data[i]); 
        free(new_file_data[i]); 
    }

    free(new_file_data); 
    fclose(file_in); 

    printf("Row added successfully.\n");
}
void file_insert(char* file,int insert_row, char* new_row) {
    char buffer[1024];
    char **file_data = NULL;
    int currentSize = 0, capacity = 1;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    file_data = (char **)malloc(capacity * sizeof(char *));
    if (file_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    while (fgets(buffer, sizeof(buffer), file_out)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 

        char result[1024];
        int j = 0; 

        
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\t') { 
                result[j++] = buffer[i]; 
            }
        }
        result[j] = '\0'; 

        strcpy(buffer, result);

        if (currentSize >= capacity) {
            capacity *= 2; 
            char **temp = realloc(file_data, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                break; 
            }
            file_data = temp; 
        }

        file_data[currentSize] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (file_data[currentSize] == NULL) {
            fprintf(stderr, "Memory allocation for string failed\n");
            break; 
        }
        
        strcpy(file_data[currentSize], buffer); 
        currentSize++; 
    }

    fclose(file_out); 

    if (insert_row < 0 || insert_row > currentSize) {
        printf("ERROR: Invalid row number for insertion\n");
        for (int i = 0; i < currentSize; i++) {
            free(file_data[i]);
        }
        free(file_data);
        return;
    }

    char **new_file_data = (char **)malloc((currentSize + 1) * sizeof(char *));
    if (new_file_data == NULL) {
        fprintf(stderr, "Memory allocation failed for new data\n");
        return;
    }

    for (int i = 0; i < currentSize + 1; i++) {
        if (i < insert_row) {
            new_file_data[i] = file_data[i]; 
        } else if (i == insert_row) {
            new_file_data[i] = (char *)malloc((strlen(new_row) + 1) * sizeof(char));
            if (new_file_data[i] == NULL) {
                fprintf(stderr, "Memory allocation for new row failed\n");
                break;
            }
            strcpy(new_file_data[i], new_row); 
        } else {
            new_file_data[i] = file_data[i - 1]; 
        }
    }

    free(file_data);

    FILE *file_in = fopen(file, "w"); 
    if (file_in == NULL) {
        printf("ERROR: could not open file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize + 1; i++) {
        fprintf(file_in, "%s\n", new_file_data[i]); 
        free(new_file_data[i]); 
    }

    free(new_file_data); 
    fclose(file_in); 

    printf("Row added successfully.\n");
}
void file_delete(char* file, int delete_row) {
    char buffer[1024];
    char **file_data = NULL;
    int currentSize = 0, capacity = 1;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    
    file_data = (char **)malloc(capacity * sizeof(char *));
    if (file_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    
    while (fgets(buffer, sizeof(buffer), file_out)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 

        
        if (currentSize >= capacity) {
            capacity *= 2; 
            char **temp = realloc(file_data, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                break; 
            }
            file_data = temp; 
        }

        
        file_data[currentSize] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (file_data[currentSize] == NULL) {
            fprintf(stderr, "Memory allocation for string failed\n");
            break; 
        }
        
        strcpy(file_data[currentSize], buffer); 
        currentSize++; 
    }

    fclose(file_out); 

    
    if (delete_row < 0 || delete_row >= currentSize) {
        printf("ERROR: Invalid row number for deletion\n");
        for (int i = 0; i < currentSize; i++) {
            free(file_data[i]);
        }
        free(file_data);
        return;
    }

    
    char **new_file_data = (char **)malloc((currentSize - 1) * sizeof(char *));
    if (new_file_data == NULL) {
        fprintf(stderr, "Memory allocation failed for new data\n");
        return;
    }

    
    for (int i = 0, j = 0; i < currentSize; i++) {
        if (i != delete_row) { 
            new_file_data[j] = file_data[i];
            j++;
        } else {
            free(file_data[i]); 
        }
    }

    free(file_data); 

    
    FILE *file_in = fopen(file, "w"); 
    if (file_in == NULL) {
        printf("ERROR: could not open file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize - 1; i++) {
        fprintf(file_in, "%s\n", new_file_data[i]); 
        free(new_file_data[i]); 
    }

    free(new_file_data); 
    fclose(file_in); 

    printf("Row deleted successfully.\n");
}
int input_int() {
    int status,input;
    status = scanf("%d", &input);
    while (status != 1 && getchar() != '\n') {
        while (getchar() != '\n');
        printf("Invalid input. Please try again : ");
        status = scanf("%d", &input);
    }
    return input;
}
void input_string(char* input) {
    int status;
    while (1) {
        if (fgets(input, 128, stdin) != NULL) {
            int len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';
            }
            break;
        } else {
            printf("Invalid input. Please try again : ");
        };
    }
}
void display_menu(int display_type) {
    switch (display_type) {
        case -1:
            printf("\n==============================\n");
            printf("   Home Utility Tracking System\n");
            printf("==============================\n");
            printf("[1] View Items\n");
            printf("[2] Manage Bills\n");
            printf("[3] Manage Subscriptions\n");
            printf("[0] Exit\n");
            printf("==============================\n");
            printf("Please enter your choice (0-3): ");
            break;

        case 1:
            printf("\n==============================\n");
            printf("        View Items Menu       \n");
            printf("==============================\n");
            printf("[1] Add an Appliance\n");
            printf("[2] Edit an Appliance\n");
            printf("[3] Delete an Appliance\n");
            printf("[0] Back to Main Menu\n");
            printf("==============================\n");
            printf("Please enter your choice (0-3): ");
            break;

        case 2:
            printf("\n==============================\n");
            printf("        Manage Bills Menu      \n");
            printf("==============================\n");
            printf("[1] Add a Bill\n");
            printf("[2] Edit a Bill\n");
            printf("[3] Delete a Bill\n");
            printf("[0] Back to Main Menu\n");
            printf("==============================\n");
            printf("Please enter your choice (0-3): ");
            break;

        case 3:
            printf("\n==============================\n");
            printf("     Manage Subscriptions Menu  \n");
            printf("==============================\n");
            printf("[1] Add a Subscription\n");
            printf("[2] Edit a Subscription\n");
            printf("[3] Delete a Subscription\n");
            printf("[0] Back to Main Menu\n");
            printf("==============================\n");
            printf("Please enter your choice (0-3): ");
            break;

        default:
            break;
    }
}


int main() {
    int choice, choice2 = 1;

    do {
        display_menu(-1);
        choice = input_int();
        
        switch (choice) {
            case 1:
                do {
                    file_read("Appliances.csv"); // Assuming this function is defined
                    display_menu(1);
                    choice2 = input_int();
                    
                    switch (choice2) {
                        case 1:
                            file_insert("Appliances.csv", 1, "New Appliance Data"); // Placeholder
                            break;
                        case 2:
                            file_insert("Appliances.csv", 2, "Updated Appliance Data"); // Placeholder
                            break;
                        case 3:
                            file_delete("Appliances.csv", 1); // Placeholder for delete function
                            break;
                        case 0:
                            break; // Go back to the main menu
                        default:
                            printf("Invalid choice, please try again.\n");
                            break;
                    }
                } while (choice2 != 0);
                break;

            case 2:
                display_menu(2);
                file_read("Bills.csv"); // Assuming this function is defined
                choice2 = input_int();
                switch (choice2) {
                        case 1:
                            file_insert("Bills.csv", 1, "New Bills Data"); // Placeholder
                            break;
                        case 2:
                            file_insert("Bills.csv", 2, "Updated Bills Data"); // Placeholder
                            break;
                        case 3:
                            file_delete("Bills.csv", 1); // Placeholder for delete function
                            break;
                        case 0:
                            break; // Go back to the main menu
                        default:
                            printf("Invalid choice, please try again.\n");
                            break;
                    }
                break;

            case 3:
                display_menu(3);
                file_read("Subscriptions.csv"); // Assuming this function is defined
                choice2 = input_int();
                switch (choice2) {
                        case 1:
                            file_insert("Subscriptions.csv", 1, "New Subscriptions Data"); // Placeholder
                            break;
                        case 2:
                            file_insert("Subscriptions.csv", 2, "Updated Subscriptions Data"); // Placeholder
                            break;
                        case 3:
                            file_delete("Subscriptions.csv", 1); // Placeholder for delete function
                            break;
                        case 0:
                            break; // Go back to the main menu
                        default:
                            printf("Invalid choice, please try again.\n");
                            break;
                    }
                break;

            case 0:
                printf("Exiting the program. Goodbye!\n");
                break; 
                
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    } while (choice != 0); 

    return 0;
}
