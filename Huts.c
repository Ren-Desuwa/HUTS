#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Tubig bill (whole month)
Electricity bill (whole month)
Gas (quarterly??)
Subscription (wifi included static)
*/

int file_handle() {
    char buffer[1024];
    char* data;
    int row,column;

    FILE *file_out = fopen("test.csv","r");
    if (file_out == NULL) {
        printf("ERROR: could not open file");
        exit(-1);
    }

    fgets(buffer, sizeof(buffer),file_out);
    printf("%s",buffer);
    data = strtok(buffer,",");
    printf("%s",data);
    char filetype = *data;

    data = strtok(NULL,",");
    printf("%s",data);
    row = *data - '0';

    while (fgets(buffer, sizeof(buffer),file_out)) {
        /* code */
    }
    
    fgets(buffer, sizeof(buffer),file_out);
    printf("%s",buffer);


    fclose(file_out);
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
    char choice;
    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input electricity meter");
    printf("\n[3] input your water meter");
    printf("\n[4] input your electricity bill");
    printf("\n[5] input your water bill");
    printf("\n[6] input your water meter");
    printf("\n[0] exit");
    printf("\n\n");
    printf("input your choice:");
    input_string(choice);
}

int main() {
    
display();
    return file_handle();
}
