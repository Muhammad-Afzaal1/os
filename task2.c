#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(){
    int rand_to_square[2], square_to_random[2], square_to_sum[2];
    pid_t pid;
    

    if(pipe(rand_to_square) == -1){
        printf("Error in establishing pipe rand_to_sqaure.\n");
        return 1;
    }
    if(pipe(square_to_random) == -1){
        printf("Error in establishing pipe square_to_random");
        return 1;
    }
    if(pipe(square_to_sum) == -1){
        printf("Error in establishing pipe square_to_sum.\n");
        return 1;
    }
    

    pid = fork();

    if (pid == 0){
        close(rand_to_square[1]);
        close(square_to_random[0]);
        close(square_to_sum[1]);
        int arr[5];
        read(rand_to_square[0], arr, sizeof(arr));
        printf("Random numbers received.\n");
        for(int i = 0; i<5; i++){
            arr[i] = arr[i] * arr[i];
        }
        printf("Sending Squared numbers to parent.\n");
        write(square_to_random[1], arr, sizeof(arr));

        printf("Reading squard numbers for sum.\n");
        read(square_to_sum[0], arr, sizeof(arr));
        int sum = 0;
        for(int i = 0; i < 5; i++){
            sum +=arr[i];
        }
        printf("The sum is: %d\n", sum);
        close(rand_to_square[0]);
        close(square_to_random[1]);
        close(square_to_sum[0]);
    }
    else{
        close(rand_to_square[0]);
        close(square_to_random[1]);
        close(square_to_sum[0]);
        int arr[5];
        const int MIN = 0;
        const int MAX = 100;
        srand(time(NULL));
        for (int i = 0; i < 5; i++){
            int num = ((rand() % (MAX - MIN + 1))+ MIN);
            arr[i] = num;
        }
        printf("Sending random numbers for square.\n");
        printf("Random Numbers: ");
        for(int i = 0; i<5; i++){
            printf(",%d", arr[i]);
        }
        printf("\n");
        write(rand_to_square[1], arr, sizeof(arr));
        read(square_to_random[0], arr, sizeof(arr));
        printf("Squared numbers are: ");
        for (int i = 0; i<5; i++){
            printf(",%d", arr[i]);
        }
        printf("\n");
        printf("Sending squared numbers for sum.\n");
        write(square_to_sum[1], arr, sizeof(arr));
        printf("\n");
        close(rand_to_square[1]);
        close(square_to_random[0]);
        close(square_to_sum[1]);
    }
}