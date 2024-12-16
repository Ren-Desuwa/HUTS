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
    int k = -1;
        printf("    ");
    while (fgets(buffer, sizeof(buffer),file_out)) {
        if (++k != 0) printf("%d.  ",k);
        data = strtok(buffer,",");
        printf("%s\t",data);
        while (data = strtok(NULL,",")) {
            printf("%s\t\t",data);
        }
        printf("\n");
    }

    fclose(file_out);
}

void file_edit() {
    char buffer[1024];
    char* data;

    FILE *file_out = fopen("test.csv","r");
    if (file_out == NULL) {
        printf("ERROR: could not open file");
        exit(-1);
    }

    while (fgets(buffer, sizeof(buffer),file_out)) {
        data = strtok(buffer,",");
        printf("%s.",data);
        while (data = strtok(NULL,",")) {
            printf("%s\t\t",data);
        }
        printf("\n");
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
    
        default:
            break;
    }
}

int main() {
    
    display();
    return 0;
}
