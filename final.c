#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

const char *FILENAME = "GlobalTemperatures.csv";
const int DATE_COL = 0;
const int AVG_TEMP_COL = 1;
const int AVG_TEMP_UNC_COL = 2;


int datenumber(int year, int month) { 
  return 12 * (year - 1750) + month; 
}

/**
 * Get month from date string
 */
int getMonth(char *date) {
  char tmp[strlen(date)];
  strcpy(tmp, date);
  char *yearStr = strtok(tmp, "-");
  char *monthStr = strtok(NULL, "-");
  int month = atoi(monthStr);
  return month;
}

/**
 * Get year from date string
 */
int getYear(char *date) {
  char tmp[strlen(date)];
  strcpy(tmp, date);
  char *yearStr = strtok(tmp, "-");
  int year = atoi(yearStr);
  return year;
}

/**
 * Get number of rows from CSV file
 */
int rowsCount() {
  FILE *data = fopen(FILENAME, "r");
  if (data == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }
  int rows = 0;

  char line[1024];
  while (fgets(line, sizeof(line), data) != NULL) {
    rows++;
  }

  fclose(data);

  return rows;
}

void getColumnValue(int row, int col, char* result)
 {
  FILE *data;
  char wanted[1000];
  int ctr = 0;

  data = fopen(FILENAME, "r");
  if (data == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  while (fgets(wanted, sizeof(wanted), data) != NULL) {
    if (ctr == row) {
      char *thing = strtok(wanted, ",");

      for (int i = 0; i < col; i++) {
        thing = strtok(NULL, ",");
      }

      if (thing != NULL) {
        strcpy(result, thing);
      } else {
        result[0] = '\0';
      }
      
      
      break;
    } else
      ctr++;
  }

  fclose(data);
}
/**
* question 2
*/
void question2() {
  int tempCounts[4] ={0, 0, 0, 0};
  double tempSums[4] = {0, 0, 0, 0};
  
  for (int row = 1; row < rowsCount(); row++) {
    
    
    char date[10];
    getColumnValue(row, DATE_COL, date);
    char avgTemp[100];
    getColumnValue(row, AVG_TEMP_COL, avgTemp);
    double temp = 0;
    if(strlen(avgTemp) > 0) {
      // only if temp is available
      temp = atof(avgTemp);
      int year = getYear(date);
      int century = (int)year/100 + 1;
      
      int index = century - 18;
      tempCounts[index]++;
      tempSums[index] = tempSums[index] + temp;
    } 
  }

  printf("\n\n       Question 2\n");
  printf("=============================\n");
  for(int i=0; i<4; i++) {
    double avg = tempSums[i]/tempCounts[i];
    printf("Century %d:Avg. Temp=%.2lf\n", i+18,  avg);
  }
  printf("=============================\n");
}

/**
* question 3
*/
void question3() {
  int tempCounts[12];
  double tempSums[12];

  // initialize all to 0
  for (int i = 0; i < 12; i++) {
    tempCounts[i] = 0;
    tempSums[i] = 0;
  }

  for (int row = 1; row < rowsCount(); row++) {
    char date[10];
    getColumnValue(row, DATE_COL, date);
    int year = getYear(date);
    if(year < 1900 || year > 2015) { 
      continue;
    }

    int month = getMonth(date);
    
    char avgTemp[100];
    getColumnValue(row, AVG_TEMP_COL, avgTemp);
    double temp = 0;
    if (strlen(avgTemp) > 0) {
      // only if temp is available
      temp = atof(avgTemp);
      
      tempCounts[month - 1]++;
      tempSums[month - 1] = tempSums[month - 1] + temp;
    }
  }

  printf("\n\n       Question 3\n");
  printf("=============================\n");
  for (int i = 0; i < 12; i++) {
    char * monthName;
    switch(i) {
      case 0: monthName = "January"; break;
      case 1: monthName = "February"; break;
      case 2: monthName = "March"; break;
      case 3: monthName = "April"; break;
      case 4: monthName = "May"; break;
      case 5: monthName = "June"; break;
      case 6: monthName = "July"; break;
      case 7: monthName = "August"; break;
      case 8: monthName = "September"; break;
      case 9: monthName = "October"; break;
      case 10: monthName = "November"; break;
      case 11: monthName = "December"; break;

    }
    printf("For %s: Avg. Temp=%.2lf\n", monthName, tempSums[i] / tempCounts[i]);
  }
  printf("=============================\n");
}
/**
* question 4
*/
void question4(void)
{
	int hotind=1, coldind=1, coldmonth, coldyear, hotmonth, hotyear;
	double hot, cold, bufferi;
	char buffer[50];
	getColumnValue(1, 1, buffer);
	if (buffer[0]!='\0')
	{
		bufferi=atof(buffer);
		hot=bufferi;
		cold=bufferi;
	}
	for (int i=2; i<rowsCount(); i++)
	{
		getColumnValue(i, 1, buffer);
		if (buffer[0]!='\0')
		{
			bufferi=atof(buffer);
			if (bufferi>hot)
			{
				hot=bufferi;
				hotind=i;
			}
			if (bufferi<cold)
			{
				cold=bufferi;
				coldind=i;
			}
		}
	}
	getColumnValue(hotind, 0, buffer);
	hotmonth=getMonth(buffer);
	hotyear=getYear(buffer);
	getColumnValue(coldind, 0, buffer);
	coldmonth=getMonth(buffer);
	coldyear=getYear(buffer);
    printf("\n\n       Question 4\n");
    printf("=============================\n");
	printf("the coldest month was %d/%d at %lf\nthe hotest month was %d/%d at %lf\n", coldmonth, coldyear, cold, hotmonth, hotyear, hot);
    printf("=============================\n");
}


/**
 * question 7
 */
void question7(void){
  double yr19avg, yr20avg, yr19sum, yr20sum;
	int year=0, row19=601, row20=1801;
	char buffer[50];
	FILE *out;
	out=fopen("question7.dat", "w");
	for (int i=0; i<100; i++)
	{
		yr19sum=0;
		yr20sum=0;
		for (int j=0; j<12; j++)
		{
			getColumnValue(row19, 1, buffer);
			yr19sum+=atof(buffer);
			row19++;
		}
		for (int j=0; j<12; j++)
		{
			getColumnValue(row20, 1, buffer);
			yr20sum+=atof(buffer);
			row20++;
		}
		yr19avg=yr19sum/12.0;
		yr20avg=yr20sum/12.0;
		fprintf(out, "%d %lf %lf\n", year, yr19avg, yr20avg);
		year++;
	}
	fclose(out);

}

/**
 * question 8
 */
void question8()
{
	double yrmidavg, yrmaxavg, yrminavg, yrmidsum, yrmaxsum, yrminsum;
	int year=1850, row=1201;
	char buffer[50];
	FILE *out;
	out=fopen("question8.dat", "w");
	for (int i=0; i<=165; i++)
	{
		yrmidsum=0;
		yrmaxsum=0;
		yrminsum=0;
		for (int j=0; j<12; j++)
		{
			getColumnValue(row, 1, buffer);
			yrmidsum+=atof(buffer);
			getColumnValue(row, 3, buffer);
			yrmaxsum+=atof(buffer);
			getColumnValue(row, 5, buffer);
			yrminsum+=atof(buffer);
			row++;
		}
		yrmidavg=yrmidsum/12.0;
		yrmaxavg=yrmaxsum/12.0;
		yrminavg=yrminsum/12.0;
		fprintf(out, "%d %lf %lf %lf\n", year, yrmidavg, yrmaxavg, yrminavg);
		year++;
	}
	fclose(out);



}

void question9(void){
  FILE *q9 = fopen("q9.dat","w");
    double sum1, sum2, sum3 = 0;
    double avg1, avg2, avg3 = 0;
    char buffer[25];
    int rows19 = datenumber(1850, 1);
    int rows20 = datenumber(1900, 1);
    int rows21 = datenumber(2000, 1);

    for (int i = 0; i < 600; i ++){
        getColumnValue(rows19, 1, buffer);
        sum1+=atof(buffer);
        getColumnValue(rows19, 3, buffer);
        sum2+=atof(buffer);
        getColumnValue(rows19, 5, buffer);
        sum3+=atof(buffer);
        rows19++;
    }

    avg1 = sum1 / 600.0;
    avg2 = sum2 / 600.0;
    avg3 = sum3 / 600.0;

    fprintf(q9, "19 %lf %lf %lf", avg1, avg2, avg3);

    sum1 = 0; sum2 = 0; sum3 = 0;
    avg1 = 0; avg2 = 0; avg3 = 0;

    for (int i = 0; i < 1200; i ++){
        getColumnValue(rows20, 1, buffer);
        sum1+=atof(buffer);
        getColumnValue(rows20, 3, buffer);
        sum2+=atof(buffer);
        getColumnValue(rows20, 5, buffer);
        sum3+=atof(buffer);
        rows20++;
    }

    avg1 = sum1 / 1200.0;
    avg2 = sum2 / 1200.0;
    avg3 = sum3 / 1200.0;

    fprintf(q9, "20 %lf %lf %lf", avg1, avg2, avg3);

    sum1 = 0; sum2 = 0; sum3 = 0;
    avg1 = 0; avg2 = 0; avg3 = 0;

    for (int i = 0; i < 1200; i ++){
        getColumnValue(rows21, 1, buffer);
        sum1+=atof(buffer);
        getColumnValue(rows21, 3, buffer);
        sum2+=atof(buffer);
        getColumnValue(rows21, 5, buffer);
        sum3+=atof(buffer);
        rows20++;

    }

    avg1 = sum1 / 1200.0;
    avg2 = sum2 / 1200.0;
    avg3 = sum3 / 1200.0;

    fprintf(q9, "21 %lf %lf %lf", avg1, avg2, avg3);




	
}

void question10(void){
        FILE*q10;
    q10 = fopen("gnu/q10.dat", "w");
    char temp[25];
    char temptwo[25];
    double temp_double=0;
    double temp_double_two = 0;
    double increment = 2000;

    for (int i = datenumber(2000,1); i < datenumber(2000,1)+(15*12); i++)
    {
        getColumnValue(i,1,temp);
        getColumnValue(i,2,temptwo);
        temp_double = strtod(temp,NULL);
        temp_double_two = strtod(temptwo,NULL);
        fprintf(q10, "%lf %lf %lf \n", increment,temp_double,temp_double_two);
        increment += 0.08333333333;
        //printf("%f \n", increment);
    }
    
    fclose(q10);




}

  //half done, need to find average and output

void question11(void){
  int startyr = 1850 ;
  double avg_string[2016-1850];
  double avg_stringtwo[2016-1850];
  double sum;
  int pos = datenumber(1850,1);
  char taken[25];
  char gaken[25];


  for (int i = 0; i < 2016-1850; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        getColumnValue(pos, 1, taken);
        sum+=strtod(taken,NULL);
        pos+=1;
	}
    avg_string[i]= sum/12;
}
//  printf("%lf", avg_string[1]);
pos =  datenumber(1850,1);

for (int i = 0; i < 2016-1850; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        getColumnValue(pos,7, gaken);
        sum+=strtod(gaken,NULL);
        pos+=1;
	}
    avg_stringtwo[i]= sum/12;
}
  printf("%lf", avg_stringtwo[1]);



  int len = sizeof(avg_string)/sizeof(avg_string[0]);
  
  FILE *q11 = fopen("gnu/q11.txt", "w");
  for (int n = 0; n < len; n++)
  {
    fprintf(q11,"%d %lf %lf \n", startyr+n, avg_string[n], avg_stringtwo[n]);
    //printf("%d %lf\n",startyr+n,avg_string[n]); // test line 
  }

fclose(q11);




}

void question1256(void){
    
    
    //Question 1
  printf("\n\n       Question 1\n");
  printf("=============================\n");
  double sum =0;
  double avg_string[2016-1760];
  int pos = datenumber(1760,1);
  char taken[100];
  printf("Year     LandAverageTemperature\n");
  printf("-------------------------------\n");
  for (int i = 0; i < 2016-1760; i++)
  {
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        getColumnValue(pos, 1, taken);
        //printf("%d : ", n);
        //printf("%lf \n", strtod(taken,NULL));
        sum+=strtod(taken,NULL);
        pos+=1;
	  }
  avg_string[i]= sum/12;
  printf("%d:    %lf\n ", 1760+i, avg_string[i]);
  
  }
    
  printf("=============================\n");
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
    printf("\n\n       Question 5\n");
    printf("=============================\n");
    printf("Hottest year is %d\n", 1760+max);
    printf("Coldest year is %d\n", 1760+min);
    printf("=============================\n");
    
    //question 6 
    
    int startyr = 1760 ;
    len = sizeof(avg_string)/sizeof(avg_string[0]);
    FILE*q6;
    q6 = fopen("Question6.dat", "w");
    for (int n = 0; n < len; n++)
    {
        fprintf(q6,"%d %lf\n",startyr+n,avg_string[n]);
        printf("%d %lf\n",startyr+n,avg_string[n]); // test line 
    }

    fclose(q6);
    

}
  //

/**
* Main
 */


int main(void) {
  chdir("/Users/miikka/Desktop/CPS/");

  //question1256();
  
  //question2();
  //question3();
  //question4();

  
  //question9();
  //question10();
  //question11();
  return 0;
}

