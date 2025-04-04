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
char* inquire(int x, int y)
 {
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
	printf("the coldest month was %d/%d at %lf\nthe hotest month was %d/%d at %lf\n", coldmonth, coldyear, cold, hotmonth, hotyear, hot);
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
	printf("question7.dat created\n");
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
	printf("question8.dat created\n");

{
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
	printf("question7.dat created\n");
}
}

void question9(void){
  FILE *q9 = fopen("gnu/q9.txt","w");

	// Write the header line to the file
	fprintf(q9,"# Century AverageLandTemp AverageMaxLandTemp AverageMinLandTemp\n");
	int count = 0; 
  int century = 0; 
  double land_max_temp = 0;
  double land_min_remp = 0;
  int z = 0;
  int n =0;
  double year_average[255];
  double land_max_tempa[1024];
  double landmintempa[1024];

	
	// Loop through the years from 1850 to 2016
	for (int i = 1850; i <= 1850+196; i++){
		// If the current year is a century year or the year 2016
		if  (i % 100 ==0 || i  == 2016){
			
			// Calculate the average temperature, max temperature, and min temperature for the century
			century /= count;
			land_max_temp /= count;
			land_min_remp /=count;
			
			fprintf(q9,"%d %d-%d   %lf %lf %lf \n",z,i-count,i-1,century,land_max_temp,land_min_remp);

			z++;
			n++;

			count= 0;
			century = 0;
			land_max_temp = 0;
			land_min_remp = 0;
		}
		
		century += year_average[i-1760] ;
		land_max_temp += land_max_tempa[i-1850];
		land_min_remp += landmintempa[i-1850];
		count++;

	}
}

void question10(void){
  char temp[100];
  char data[17];
  int rows = rowsCount();
  //printf ("%d", rows);
  double value = 0;
  FILE *q10 = fopen("gnu/q10.csv", "w");

  //fprintf(q10, "jan, feb, mar, apr, may, june, july, aug, sept, oct, noc, dec");
  //fprintf(q10, "\n");
  //printf("%s", temp);
  for (int j = 0; j < 180; j ++){
    for (int i = 0; i < 12; i++){
      getColumnValue(i + j + 3001, 1, temp); 
      fprintf(q10, temp);
      //printf("%s \n", temp);
      fprintf(q10, ", ");
    }
    j += 11;
      fprintf(q10, "\n");
  }
  //here
  getColumnValue(2, 1, data);
  printf("%s", data);

  char line[1024];
  double sum = 0.0;
  int count = 0;
  FILE *file = fopen("gnu/q10.csv", "wr");
  fgets(line, 1024, file);

  // Read lines from the file
  while (fgets(line, 1024, file) != NULL) {
      // Tokenize the line to extract the value from the first column
      char *token = strtok(line, ",");
      if (token != NULL) {
          // Convert the token to a double and add it to the sum
          double value = atof(token);
          sum += value;
          count++;
      }
  }

  // Close the file
  fclose(file);

  // Calculate and print the average for the first column
  double average = (count > 0) ? (sum / count) : 0.0;
  printf("Average of the first column: %.2f\n", average);

  

  



  


 
    



}

  //half done, need to find average and output

void question11(void){
  int startyr = 1760 ;
  double avg_string[2015-1850];
  double avg_stringtwo[2015-1850];
  int sum;
  int pos = datenumber(1850,0);
  char taken[25];
  char gaken[25];


  for (int i = 0; i < 2016-1850; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        //getColumnValue(pos,1, taken);
        //sum+=strtod(taken,NULL);
        sum+=strtod(inquire(pos,1),NULL);
        pos+=1;
	}
    avg_string[i]= sum/12;
}

  for (int i = 0; i < 2016-1850; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        //getColumnValue(pos,9, gaken);
        //sum+=strtod(gaken,NULL);
        sum+=strtod(inquire(pos,9),NULL);
        pos+=1;
	}
    avg_stringtwo[i]= sum/12;
}

  int len = sizeof(avg_string)/sizeof(avg_string[0]);
  
  FILE *q11 = fopen("gnu/q11.txt", "w");
  for (int n = 0; n < len; n++)
  {
    fprintf(q11,"%d %lf %lf\n", startyr+n, avg_string[n], avg_stringtwo[n]);
    //printf("%d %lf\n",startyr+n,avg_string[n]); // test line 
  }

fclose(q11);




<<<<<<< HEAD

}

void question1256(void){
    //Question 1
  
  double sum =0;
  double avg_string[2016-1760];
  int pos = datenumber(1760,0);
  char taken[25];
  for (int i = 0; i < 2016-1760; i++)
  {
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        //getColumnValue(pos,1, taken);
        //sum+=strtod(taken,NULL);
        sum+=strtod(inquire(pos,1),NULL);
        pos+=1;
	  }
  avg_string[i]= sum/12;
    
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
    
}
}

/**
* Main
 */
int main(void) {
  //Question 1
  /*
double sum =0;
double avg_string[2016-1760];
int pos = datenumber(1760,0);
char taken[25];
for (int i = 0; i < 2016-1760; i++)
{
    sum = 0;

    for(int n = 0; n < 12; n++)
    { 
        getColumnValue(pos,1, taken);
        sum+=strtod(taken,NULL);
        pos+=1;
	  }
  avg_string[i]= sum/12;
    
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
*/
  //question9();
  //question10();
  //question11();
  return 0;
}

