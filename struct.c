#include<stdio.h>
#include<string.h>
#include<unistd.h>


#define LENGTH = 3200; 

typedef struct globaltemperatures
{
    /* data */
    char date[12];
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
    int read = 0;
    int records = 0;

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
        if (read == 9){
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
    );




}