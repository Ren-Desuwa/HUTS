#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Tubig bill (whole month)
Electricity bill (whole month)
Gas (quarterly??)
Subscription (wifi included static)
*/

void file_read(char* file) {
    char buffer[1024];
    char* data;
    int COLUMN_WIDTH = 20;

    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    printf("\n");

    int k = -1;
    while (fgets(buffer, sizeof(buffer), file_out)) {
        if (k++ != -1) printf("%d.", k); // Print row number aligned
        else printf("  ");
        data = strtok(buffer, ",");
        
        int columnIndex = 0; // Track column index for alignment
        while (data != NULL) {
            printf("%-*s", COLUMN_WIDTH, data); // Print each column with fixed width
            data = strtok(NULL, ",");
            columnIndex++;
        }
        printf("\n"); // New line after each row
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

void file_add(char* file,int add_row, char* new_row) {
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

    if (add_row < 0 || add_row > currentSize) {
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
        if (i < add_row) {
            new_file_data[i] = file_data[i]; 
        } else if (i == add_row) {
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

void display_menu() {
    printf("\n==============================\n");
    printf("   Home Utility Tracking System\n");
    printf("==============================\n");
    printf("[1] View Items\n");
    printf("[2] Add a Bill\n");
    printf("[3] Manage Subscriptions\n");
    printf("[0] Exit\n");
    printf("==============================\n");
    printf("Please enter your choice (0-3): ");
}

int main() {
    int choice;

    do {
        display_menu();
        choice = input_int();
        switch (choice) {
            case 1:
                file_read("test.csv");
                break;
            case 2:
                file_add("test.csv", 2, "michelle,controller,64.5");
                break;
            case 3:
                printf("Managing subscriptions...\n"); 
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
