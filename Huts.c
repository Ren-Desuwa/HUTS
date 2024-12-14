#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/*  types: 
    int = 0
    string = 1
*/
//test
int file() {

    FILE *file_out;
    
    file_out = fopen("test.txt","a");

    fputs("Jestotoy",file_out);

    fclose(file_out);
}

int input(int type) {
    int input, status = scanf("%c",&input);
    if (status != 1 && getchar() != '\n') {
        printf("done");
    }
    return input;
}

int main() {
    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input electric meter");
    printf("\n[3] input your water meter");
    printf("\n[0] exit");
    printf("\n\n");

    file();

    printf("input your choice:");
    printf("%c", input(0));

    return 0;
}