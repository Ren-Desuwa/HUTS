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

void display() {

    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input/edit your bills");
    printf("\n[3] input/edit your Subscription");
    printf("\n[0] exit");
    printf("\n\n");
    printf("input your choice:");
    switch (input_int()) {
        case 1:
            file_read("test.csv");
            break;
        case 2:
            file_add("test.csv",2,"hiiii");
            break;
    
        default:
            break;
    }
}

int main() {
    
    display();
    return 0;
}
