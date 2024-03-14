#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ROWS 3200
#define COLUMNS 10

int main(){
    float temp[ROWS][COLUMNS];
    FILE *file = fopen("GlobalTemperatures.csv", "r");

    if (file == NULL){
        printf("empty file.");
        exit(-1);
    }

    int row = 0;
    while (!feof(file)){
        if (ferror(file)){
            printf("error reading file");
            exit(-1);
        }
        for (int i = 0; i < COLUMNS; i++){
            if (fscanf(file, "%f", &temp[row][i]) == EOF){
                break;
            }
        }
        row ++;
        if (row == ROWS){
            break;
        }
    }
}