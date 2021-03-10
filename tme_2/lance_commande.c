#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>


void lance_commande(char * commande){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    double timewas = current_time.tv_sec+current_time.tv_usec*0.000001;
    if(system(commande)!=0){
        printf("\nERROR: command %s has failed\n", commande);
        exit(1);
    }
    gettimeofday(&current_time, NULL);
    double timeis = current_time.tv_sec+current_time.tv_usec*0.000001;
    printf("execution time of %s is %lf seconds\n", commande, timeis-timewas);

}


void lance_commande2(char * commande){
    struct tms t_Start;
    struct tms t_End;
    times(&t_Start);
    if(system(commande)!=0){
        printf("\ncommand %s has failed\n", commande);
        exit(1);
    }
    times(&t_End);
    double utime = t_End.tms_utime-t_Start.tms_utime;
    double stime = t_End.tms_stime-t_Start.tms_stime;
    double cutime = t_End.tms_cutime-t_Start.tms_cutime;
    double cstime = t_End.tms_cstime-t_Start.tms_cstime;
    printf("Statistiques de %s :\n", commande);
    printf("Temps total : %lfs\n", (utime+stime+cutime+cstime)/sysconf(_SC_CLK_TCK));
    printf("Temps utilisateur : %lfs\n", utime/sysconf(_SC_CLK_TCK));
    printf("Temps systeme : %lfs\n", stime/sysconf(_SC_CLK_TCK));
    printf("Temps utilisateur fils : %lfs\n", cutime/sysconf(_SC_CLK_TCK));
    printf("Temps systeme fils : %lfs\n\n", cstime/sysconf(_SC_CLK_TCK));
}


int main(int argc, char* argv[]){
    for (int i=1; i<argc; i++){
        lance_commande2(argv[i]);
    }
    return 0;
}