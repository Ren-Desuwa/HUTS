#include <stdio.h>
#include "sqlite3.h"


/*
Tubig bill (whole month)
Electricity bill (whole month)
Gas (quarterly??)
Subscription (wifi included static)
*/
void sql() {
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("myDatabase.db", &db);
    
}

float get_bill() {
    for (int i = 0; i < 4; i++) {

    }
}

int get_int_input() {
    int status,input;
    status = scanf("%d", &input);
    while (status != 1 && getchar() != '\n') {
        while (getchar() != '\n');
        printf("Invalid input. Please try again : ");
        status = scanf("%d", &input);
    }
    return input;
}
float get_float_input() {
    int status;
    float input;
    status = scanf("%f", &input);
    while (status != 1 && getchar() != '\n') {
        while (getchar() != '\n');
        printf("Invalid input. Please try again : ");
        status = scanf("%f", &input);
    }
    return input;
}

int get_input(int limit,char type) {
    int result;
    do {
        result = get_int_input();


    } while (1);
    return result;
}

int main() {

    printf("Home Utility Tracking System");
    printf("\n[1] input/edit appliance");
    printf("\n[2] input electric meter");
    printf("\n[3] input your water meter");
    printf("\n[0] exit");
    printf("\n\n");

    printf("input your choice:");
    sql();

    return 0;
}
