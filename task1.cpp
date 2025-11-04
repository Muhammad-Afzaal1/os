// In this programme (Parent Child Communication vai Pipes)

//      Prent receives an array from command line.
//      Parent Sent the array to child.
//      Child compute sum and minimum and send them to parent.
//      Parent printss the sum and minimum.

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        perror("Please provide integer array.\n");
        return 1;
    }
    pid_t pid;
    int parent_to_sum[2], sum_to_parent[2], parent_to_minimum[2], minimum_to_parent[2];

    if(pipe(parent_to_sum) == -1){
        perror("Unable to establish pipe parent_to_sum\n");
        return 1;
    }
    if(pipe(sum_to_parent) == -1){
        perror("Unable to establish pipe: sum_to_parent\n");
        return 1;
    }
    if(pipe(parent_to_minimum) == -1){
        perror("Unable to establish pipe parent_to_minimum.\n");
        return 1;
    }
    if(pipe(minimum_to_parent) == -1){
        perror("Unable to establish pipe: minimum_to_parent.\n");
    }

    pid = fork();

    if (pid == 0){
        close(parent_to_sum[1]);
        close(sum_to_parent[0]);
        close(minimum_to_parent[0]);
        close(parent_to_minimum[1]);
        int sum = 0; 
        int arr[argc-1];
        read(parent_to_sum[0], arr, sizeof(arr));
        printf("Child received array for Sum\n");
        for(int i = 0; i < argc-2; i++){
            sum = sum + arr[i];
        }
        write(sum_to_parent[1], &sum, __SIZEOF_INT__);
        printf("Child sent sum to Parent.\n");

        read(parent_to_minimum[0], arr, sizeof(arr));
        printf("Child received array for minimum.\n");
        int minimum = INT_MAX;
        for(int i =0; i<argc-2; i++){
            if(arr[i] < minimum){
                minimum = arr[i];
            }
        }
        write(minimum_to_parent[1], &minimum, sizeof(minimum));
        printf("Child sent minimum %d to Parent\n", minimum);
        close(parent_to_sum[0]);
        close(sum_to_parent[1]);
        close(parent_to_minimum[0]);
        close(minimum_to_parent[1]);
    }
    else{
        close(parent_to_sum[0]);
        close(sum_to_parent[1]);
        close(parent_to_minimum[0]);
        close(minimum_to_parent[1]);
        int arr[argc-1];
        for (int i =1; i<argc-1; i++){
            arr[i-1] = atoi(argv[i]);
        }
        printf("Parent sending array for sum.\n");
        write(parent_to_sum[1], arr, sizeof(arr));
        printf("Parent sending array for minimum.\n");
        write(parent_to_minimum[1], arr, sizeof(arr));
        int sum = 0;
        
        read(sum_to_parent[0], &sum, __SIZEOF_INT__);
        printf("The sum is: %d\n", sum);
        int minimum;
        read(minimum_to_parent[0], &minimum, sizeof(minimum));
        printf("The minimum is: %d\n", minimum);
        close(parent_to_sum[1]);
        close(sum_to_parent[0]);
        close(parent_to_minimum[1]);
        close(minimum_to_parent[0]);
    }

    return 0;
}   