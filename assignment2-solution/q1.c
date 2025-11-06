#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    int c2s[2], s2c[2];
    pid_t pid;
    if(pipe(c2s)== -1){
        printf("There is error in pipe creation from c2s.\n");
        return 1;
    }
    if(pipe(s2c) == -1){
        printf("There is error in pipe creation from s2c.\n");
        return 1;
    }

    pid = fork();

    if(pid == 0){
        close(c2s[0]);
        close(s2c[1]);

        char command[] = "Get * from users";
        printf("Sending command\n\t %s to Server\n", command);
        write(c2s[1], command, sizeof(command));

        char response[100];
        read(s2c[0], response, sizeof(response));
        printf("Server response: \n\t");
        printf("%s\n", response);

        close(c2s[1]);
        close(s2c[0]);
    }
    else{
        close(c2s[1]);
        close(s2c[0]);

        char command [100];
        read(c2s[0], command, sizeof(command));
        printf("Server received client request.\n");
        char response[] = "Ali Ahmad Usman Imran Ishtiaq";
        write(s2c[1], response, sizeof(response));

        close(c2s[0]);
        close(s2c[1]);
    }
    return 0;
}