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
    data = strtok(buffer,",");
    char file_name = *data;
    data = strtok(NULL,",");
    row = *data - '0';

    while (fgets(buffer, sizeof(buffer),file_out)) {
        for (int i = 0; i < row; i++) {
            data = strtok(buffer,",");
            printf("%s",data);
        }
    }


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

    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input electric meter");
    printf("\n[3] input your water meterth");
    printf("\n[0] exit");
    printf("\n\n");
    printf("input your choice:");
    switch (input_int()) {
        case 1:
            file_handle();
            break;
    
        default:
            break;
    }
}

int main() {
    
display();
    return file_handle();
}
