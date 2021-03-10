#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
    printf("hello im dad %d\n",getpid());
    sleep(10);
    if(fork() == 0) {
        printf("hello im son %d\n", getpid());
        if (fork()==0){
            printf("hello im grand son %d\n", getpid());
        }
    }
    wait(NULL);
    printf("this is the end\n");
    return 0;
}
