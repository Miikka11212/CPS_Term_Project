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

int main(void) 
{
    



//Question 1
double sum =0;
double avg_string[2016-1760];
int pos = datenumber(1760,0);
for (int i = 0; i < 2016-1760; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    {
        sum+=strtod(inquire(pos,1),NULL);
        pos+=1;
	}
    avg_string[i]= sum/12;


}

//question 5 
int max =0;
int min =0;
int len = sizeof(avg_string)/sizeof(avg_string[0]);
for(int n = 0; n < len; n++)
{
        if( avg_string[n]>avg_string[max])
        {
            max = n ;
        }

        if( avg_string[n]<avg_string[min])
        {
            min = n ;
        }
}
printf("Hottest year is %d\n", 1760+max);
printf("Coldest year is %d\n", 1760+min);

//question 6 
int startyr = 1760 ;
len = sizeof(avg_string)/sizeof(avg_string[0]);
FILE*q6;
q6 = fopen("Question6.txt", "w");
for (int n = 0; n < len; n++)
{
    fprintf(q6,"%d %lf\n",startyr+n,avg_string[n]);
    //printf("%d %lf\n",startyr+n,avg_string[n]); // test line 
}

fclose(q6);
return 0;
}
