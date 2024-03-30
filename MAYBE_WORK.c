#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>



int datenumber(int year, int month) {
    return 12 * (year - 1750) + month;
}

char* inquire(int x, int y) {
    FILE *data;
    char wanted[1000];
    static char returnable[100]; 
    int ctr = 0;

    data = fopen("GlobalTemperatures.csv", "r");

    while (fgets(wanted, sizeof(wanted), data) != NULL) {
        if (ctr == x) {
            char *thing = strtok(wanted, ",\n");

            for (int i = 0; i < y; i++) {
                thing = strtok(NULL, ",\n");
            }

            strcpy(returnable, thing); 
            break;
        }
        else
            ctr++;
    }

    fclose(data);
    return returnable;
}

int main(void) {
    chdir("/Users/miikka/Desktop/CPS/");

    for (int ctr = 0; ctr < 24; ctr++) // change 24 to datenimer to determine an end point
    {
        printf("%s\n", inquire(ctr, 0)); // change ctr to datenumber to satrt at a certin point and 0 with to the index of the data wanted
    }
    return 0;
}
