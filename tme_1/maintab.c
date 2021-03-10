#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "tab.h"

void printMem(){
    struct rusage t;
      getrusage(RUSAGE_SELF, &t);
      printf("memory usage : %ld\n\n", t.ru_maxrss);
}

int main(){
    srand(time(NULL));
    
    int tab_local[NMAX];
    int *min = malloc(sizeof(int));
    initTab(tab_local, NMAX);
    printTab(tab_local, NMAX);
    sumTab(tab_local, NMAX);
    minSumTab(min, tab_local, NMAX);
    printMem();

    int *tab = malloc(NMAX * sizeof(int));
    initTab(tab, NMAX);
    printTab(tab, NMAX);
    sumTab(tab, NMAX);
    minSumTab(min, tab, NMAX);
    printMem();
}