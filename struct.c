#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <stdlib.h>



#define LENGTH = 3200; 

typedef struct globaltemperatures
{
    /* data */
    int year;
    int month;
    int day;
    double LandAverageTemperature;
    double LandAverageTemperatureUncertainty;
    double LandMaxTemperature;
    double LandMaxTemperatureUncertainty;
    double LandMinTemperature;
    double LandMinTemperatureUncertainty;
    double LandAndOceanAverageTemperature;
    double LandAndOceanAverageTemperatureUncertainty;

}gt;


int main(){
    chdir("/Users/miikka/Desktop/CPS/");
    FILE *file = fopen("GlobalTemperatures.csv", "r");

    if (file == NULL){
        printf("empty file");
        return 1;
    }

    gt data[3200];  
    //char temp[20];
    char buffer[1000];
    double buffer_two[1000];

    int integer_buffer = 0;
    double double_buffer = 0;
    

    while (!feof(file)){
        for (int i = 0; i < 3200; i++){
            fgets(buffer, sizeof(buffer), file);
            integer_buffer = atoi(strtok(buffer, "-"));
            data[i].year = integer_buffer;

            fgets(NULL, sizeof(buffer), file);
            integer_buffer = atoi(strtok(buffer, "-"));
            data[i].month = integer_buffer;

            fgets(NULL, sizeof(buffer), file);
            integer_buffer = atoi(strtok(buffer, "-"));
            data[i].day = integer_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandAverageTemperature = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandAverageTemperatureUncertainty = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandMaxTemperature = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandMaxTemperatureUncertainty = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandMinTemperature = double_buffer;
            
            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandMaxTemperatureUncertainty = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandAndOceanAverageTemperature = double_buffer;

            fgets(NULL, sizeof(buffer_two), file);
            double_buffer = atof(strtok(buffer, ","));
            data[i].LandAndOceanAverageTemperatureUncertainty = double_buffer;
        
        }
    }

    printf("%lf", data[1].LandMaxTemperature);



/*
     do
     {
        read = fscanf(file,
                    "%12[^,], %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf ",
                    data[records].date,
                    &data[records].LandAverageTemperature,
                    &data[records].LandAverageTemperatureUncertainty,
                    &data[records].LandMaxTemperature,
                    &data[records].LandMaxTemperatureUncertainty,
                    &data[records].LandMinTemperature,
                    &data[records].LandMinTemperatureUncertainty,
                    &data[records].LandAndOceanAverageTemperature,
                    &data[records].LandAndOceanAverageTemperatureUncertainty
                    );
        if (read == 10){
            records ++;
        }
        if (read != 9 && !feof(file)){
            printf("error reading file\n");
            return 1;
        }
        if (ferror(file)){
            printf("error reading file\n");
            return 1;
        }

     } while (!feof(file));
     
    fclose(file);

    for (int i = 0; i < records; i++){
        printf("%s, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n ",
                    data[i].date,
                    data[i].LandAverageTemperature,
                    data[i].LandAverageTemperatureUncertainty,
                    data[i].LandMaxTemperature,
                    data[i].LandMaxTemperatureUncertainty,
                    data[i].LandMinTemperature,
                    data[i].LandMinTemperatureUncertainty,
                    data[i].LandAndOceanAverageTemperature,
                    data[i].LandAndOceanAverageTemperatureUncertainty);
    }
    printf(
        "\n"
        */
    




}