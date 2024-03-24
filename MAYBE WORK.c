#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
    for (int ctr = 0; ctr < 24; ctr++) // change 24 to datenimer to determine an end point
    {
        printf("%s\n", inquire(ctr, 0)); // change ctr to datenumber to satrt at a certin point and 0 with to the index of the data wanted
    }
    return 0;



//Question 1
double sum =0;
char avg_string[2015-1760];
int pos = datenumber(1760,1);
for (int i = 0; i < 2015-1760; i++)
{
    sum = 0;

    for (int n = 0; n < 12; n++)
        sum+=strtod(inquire(pos,1));
        pos+=1;
    datenumber[i]= sum/12;


}

//question 5 
int max =0;
int min =0;
int len = sizeof(avg_string)/sizeof(avg_string[0]);
for (int n = 0; n < len; n++)
        if( avg_string[n]>avg_string[max])
        {
            max = n ;
        }

        if( avg_string[n]<avg_string[min])
        {
            min = n ;
        }

printf("Hottest year is %d", 1760+max);
printf("Coldest year is %d", 1760+min);

//question 6 
int startyr = 1760 ;
int len = sizeof(avg_string)/sizeof(avg_string[0]);
File*q6;
q6 = fopen("Question6.txt", "w");
for (int n = 0; n < len; n++)
{
    fprintf(q6,"%lf %lf\n",startyr+n,avg_string[n]);
}

fclose(q6);