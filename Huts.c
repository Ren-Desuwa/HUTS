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

    FILE *file_out = fopen(file,"r");
    if (file_out == NULL) {
        printf("ERROR: could not open file");
        exit(-1);
    }
    printf("\n");
    int k = 0;
        printf("    ");
    while (fgets(buffer, sizeof(buffer),file_out)) {
        if (k++ != 0) printf("%d.  ",k);
        data = strtok(buffer,",");
        printf("%s\t",data);
        while (data = strtok(NULL,",")) {
            printf("%s\t\t",data);
        }
        printf("\n");
    }

    fclose(file_out);
}

void file_edit(char* file,int insert_row, char* row) {
    char buffer[1024];
    char **file_data = NULL;
    int currentSize = 0, capacity = 1;

    // Open the file for reading
    FILE *file_out = fopen(file, "r");
    if (file_out == NULL) {
        printf("ERROR: could not open file\n");
        exit(-1);
    }

    // Allocate initial memory for file_data
    file_data = (char **)malloc(capacity * sizeof(char *));
    if (file_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(-1);
    }

    // Read existing data from the file
    while (fgets(buffer, sizeof(buffer), file_out)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

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

    fclose(file_out); // Close the input file

    // Check if the insert_row is valid
    if (insert_row < 0 || insert_row > currentSize) {
        printf("ERROR: Invalid row number for insertion\n");
        // Free allocated memory and exit
        for (int i = 0; i < currentSize; i++) {
            free(file_data[i]);
        }
        free(file_data);
        return;
    }

    // Allocate memory for new data including the new row
    char **new_file_data = (char **)malloc((currentSize + 1) * sizeof(char *));
    if (new_file_data == NULL) {
        fprintf(stderr, "Memory allocation failed for new data\n");
        return;
    }

    // Copy existing data to new array and insert new row
    for (int i = 0; i < currentSize + 1; i++) {
        if (i < insert_row) {
            new_file_data[i] = file_data[i]; // Copy existing rows before insert_row
        } else if (i == insert_row) {
            new_file_data[i] = (char *)malloc((strlen(row) + 1) * sizeof(char));
            if (new_file_data[i] == NULL) {
                fprintf(stderr, "Memory allocation for new row failed\n");
                break;
            }
            strcpy(new_file_data[i], row); // Insert the new row
        } else {
            new_file_data[i] = file_data[i - 1]; // Copy remaining rows
        }
    }

    // Free old data array
    free(file_data);

    // Write modified data back to the file
    FILE *file_in = fopen(file, "w"); // Open file for writing
    if (file_in == NULL) {
        printf("ERROR: could not open file for writing\n");
        exit(-1);
    }

    for (int i = 0; i < currentSize + 1; i++) {
        fprintf(file_in, "%s\n", new_file_data[i]); // Write each line to the file
        free(new_file_data[i]); // Free each string after writing
    }

    free(new_file_data); // Free the array of pointers
    fclose(file_in); // Close the output file

    printf("Row inserted successfully.\n");
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

void display() {

    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input/edit electricity meter");
    printf("\n[3] input/edit your water meter");
    printf("\n[4] input/edit your electricity bill");
    printf("\n[5] input/edit your water bill");
    printf("\n[6] input/edit your water meter");
    printf("\n[7] input/edit your Subscription");
    printf("\n[8] input/edit your Gas");
    printf("\n[0] exit");
    printf("\n\n");
    printf("input your choice:");
    switch (input_int()) {
        case 1:
            file_read("test.csv");
            break;
        case 2:
            file_edit("test.csv",2,"hiiii");
            break;
    
        default:
            break;
    }
}

int main() {
    
    display();
    return 0;
}
