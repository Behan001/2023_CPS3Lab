#include "mbed.h"
#include <cmath>
#include <cstdio>

float Temp_v[10] = {18.9, 17.3, 18.4, 19.3, 22.1, 21.4, 19.5, 19.8, 20.1, 20.6};


int main() {
    float min_t = 0;
    float max_t = 0;
    for(int i=0; i<10; i++)
        printf("%f,", Temp_v[i]);
    printf("\r\n");
}