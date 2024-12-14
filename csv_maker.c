#include <stdio.h>
#include <string.h>

int input() {
    int status,input;
    status = scanf("%d", &input);
    while (status != 1 && getchar() != '\n') {
        while (getchar() != '\n');
        printf("Invalid input. Please try again : ");
        status = scanf("%d", &input);
    }
    while (getchar() != '\n');
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

int main() {
    printf("START PROGRAM");
    printf("\nnumber of column: ");
    int column = input();
    printf("number of rows: ");
    int row = input() + 1;
    
    char file_data[column + 3][128];
    printf("File type : ");
    input_string(file_data[0]);
    sprintf(file_data[1], "%d", row + 2);
    sprintf(file_data[2], "%d", column);
    
    printf("\n");

    char data[row][column][128];
    char header[column][128];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0) {
                printf("Header %d : ",j + 1);
                input_string(header[j]);
                printf("Datatype : ");
                input_string(file_data[j+3]);
            } else {
                printf("%s on row %d : ",header[j],i);
                input_string(data[i][j]);
            }
        }
        printf("\n");   
    }

    printf("\n");


    for (int i = 0; i < column + 3; i++) {
        printf("%s",file_data[i]);
        if (i < column + 2) printf(",");
        if (i == 2) printf("\n");
    }

    printf("\n");

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0) printf("%s",header[j]);
            else printf("%s",data[i][j]);
            if (j < column - 1) printf(",");
        }
        printf("\n");
    }
    return 0;
}