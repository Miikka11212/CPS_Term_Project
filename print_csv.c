#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(void) {
    chdir("/Users/miikka/Desktop/CPS/");
    char data[300][3200];
    char buffer[1000];
    char *dt;

//make file reader called temp
    FILE *temp = fopen("GlobalTemperatures.csv", "r");
    //error load
    if (temp == NULL) {
        printf("Error: could not open file\n");
        exit(-1);
    }
//gets ONLY FIRST LINE
    fgets(buffer, sizeof(buffer), temp);
    //the first three tokens of the first line
    dt = strtok(buffer,",");
    printf("the first token is: %s \n ", dt);

    dt = strtok(NULL,",");
    printf("the second token is: %s \n ", dt);
    
    dt = strtok(NULL,",");
    printf("the third token is: %s \n ", dt);

    //prints out whole csv file
    //while(fgets(buffer, sizeof(buffer), temp)){
    //    printf("%s\n", buffer);
    //}

    int line = 0;
    
    while(!feof(temp) && !ferror(temp)){
        if(fgets(data[line], 3200, temp) != NULL){
            line++;
        }
    }

    for (int i = 0; i < line; i++){
        printf("%s", data[i]);
    }


    fclose(temp);
}