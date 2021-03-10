#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void initTab(int *tab, int size){
    srand(time(NULL));
    for(int i = 0; i < size; i ++){
        tab[i] = rand()%10;
    }
}

void printTab(int *tab, int size){
    for(int i = 0; i < size; i ++){
       printf("%d ", tab[i]);
    }
    printf("\n");
}

int sumTab(int *tab, int size){
    int sum = 0;
    for(int i = 0; i < size; i ++){
       sum += tab[i];
    }
    return sum;
}

int minSumTab(int *min, int *tab, int size){
    *min = tab[0];
    for(int i = 1; i < size; i++){
        if(*min > tab[i])
            *min = tab[i];
    }
    printf("min is : %d\n", *min);
    return sumTab(tab, size);
}