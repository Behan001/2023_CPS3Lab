#include "mbed.h"
#include "LM75B.h"
#include "C12832.h"
#include "LocalFileSystem.h"

#define LOG_INTERVAL_MINUTES 5

C12832 lcd(p5, p7, p6, p8, p11);
LM75B sensor(p28, p27);
LocalFileSystem local("local");

int main() {
    FILE *fp = fopen("/local/temp_log.txt", "w");
    if (fp == NULL) {
        error("Could not open file for writing\n");
    }

    float min_t = 100;
    float max_t = -100;
    float avg_t = 0.0;
    int num_samples = 0;
    time_t last_log_time = time(NULL);

    while (1) {
        float temp = sensor.read();
        fprintf(fp, "%.3f\n", temp);

        if (temp < min_t) {
            min_t = temp;
        }
        if (temp > max_t) {
            max_t = temp;
        }
        avg_t = ((avg_t * num_samples) + temp) / (num_samples + 1);
        num_samples++;

        time_t current_time = time(NULL);
        if ((current_time - last_log_time) >= (LOG_INTERVAL_MINUTES * 60)) { 
            fclose(fp); // Close file
            fp = fopen("/local/temp_log.txt", "r");
            if (fp == NULL) {
                error("Could not open file for reading\n");
            }

            float sum_t = 0.0;
            num_samples = 0;
            while (!feof(fp)) {
                float temp = 0.0;
                fscanf(fp, "%f\n", &temp);
                sum_t += temp;
                if (temp < min_t) {
                    min_t = temp;
                }
                if (temp > max_t) {
                    max_t = temp;
                }
                num_samples++;
            }
            avg_t = sum_t / num_samples;

            lcd.cls();
            lcd.locate(0, 3);
            lcd.printf("Min: %.3f\nMax: %.3f\nAvg: %.3f", min_t, max_t, avg_t);

            fclose(fp);
            fp = fopen("/local/temp_log.txt", "a");
            if (fp == NULL) {
                error("Could not open file for appending\n");
            }

            last_log_time = current_time;
        }

        wait(1.0);
    }
}

// #include "mbed.h"
// #include <cmath>
// #include <cstdio>
// #include "LM75B.h"
// #include "C12832.h"

// C12832 lcd(p5, p7, p6, p8, p11);
// LM75B sensor(p28, p27);
// LocalFileSystem local("local");

// float Temp_v[10] = {18.9, 17.3, 18.4, 19.3, 22.1, 21.4, 19.5, 19.8, 20.1, 20.6};


// int main() {
//     FILE *fp = fopen("/local/temp_log.txt", "w");
//     if (fp == NULL) {
//         error("Could not open file for writing\n");

//     float min_t = 100;
//     float max_t = -100;
//     float avg_t = 0.0;
//     int num_samples = 0;
//     time_t last_log_time = time(NULL);

//     for(int i=0; i<10; i++){
//         if (Temp_v[i] < min_t)
//         min_t = Temp_v[i];
//     }
//     for(int i=0; i<10; i++){
//         if (Temp_v[i] > max_t)
//         max_t = Temp_v[i];    
//     }
//         printf("%f is max and %f is min",max_t, min_t);
//     printf("\r\n");
//         lcd.printf("%f is max and %f is min",max_t, min_t);
// }
