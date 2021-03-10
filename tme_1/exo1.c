#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int max = atoi(argv[1]);
    int i;
    for (i=1; i<argc; i++){
        if (atoi(argv[i])>max) max = atoi(argv[i]);
    }
    printf("le max est %d\n", max);
    return 0;
}