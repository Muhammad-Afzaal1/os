#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int random_number1 = rand();
    int random_number2 = rand();
    int num = rand();
    printf("Random number 1 : %d\n", random_number1);
    printf("Random number 2: %d\n", random_number2);
    return 0;
}