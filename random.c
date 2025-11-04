#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int min = 0;
    int max = 100;
    int randomNumberInRange = (rand() % (max-min +1) + min);
    printf("min: %d max: %d Random Number: %d\n", min, max, randomNumberInRange);
    return 0;
}