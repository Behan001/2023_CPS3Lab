#include "mbed.h"
#include <cmath>
#include <cstdio>
#include "LM75B.h"
#include "C12832.h"

float Temp_v[10] = {18.9, 17.3, 18.4, 19.3, 22.1, 21.4, 19.5, 19.8, 20.1, 20.6};


int main() {
    float min_t = 100;
    float max_t = -100;

    for(int i=0; i<10; i++){
        if (Temp_v[i] < min_t)
        min_t = Temp_v[i];
    }
    for(int i=0; i<10; i++){
        if (Temp_v[i] > max_t)
        max_t = Temp_v[i];    
    }
        printf("%f is max and %f is min",max_t, min_t);
    printf("\r\n");
}
