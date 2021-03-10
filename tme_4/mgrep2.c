#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAXFILS 2


int main(int argc, char *argv[]){
    //to check store the status of the childs 
    int nbChild = 0;
    //start at 2 cause 0 = func name, 1 = word to search 
    for (int i=2; i<argc; i++){
        if (nbChild++ >= MAXFILS){
            printf("j'attend un fils\n");
            wait(NULL);
            nbChild--;
        }
        if (fork() == 0) {
            execlp("grep","grep","--color", argv[1], argv[i],NULL);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}



