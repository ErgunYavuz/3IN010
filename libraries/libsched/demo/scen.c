#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sched.h>

#define LONGTIME 8E8
void ProcLong(int *);
void ProcCourt(int *);

// Exemple de processus long (une simple bouble),
// Chaque processus long cr�e a son tour 4 processus courts
//
void ProcLong(int *pid) {
  long i;
  static int cpt = 0;

  for (i=0;i<LONGTIME;i++) {
    if (i%(long)(LONGTIME/4) == 0)  {
      int *tcpt = (int *) malloc(sizeof(int));
      *tcpt = cpt;
      CreateProc((function_t)ProcCourt,(void *)tcpt, 10);
      cpt++;
    }
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Long %d - %ld\n",*pid, i);
  }
  printf("############ FIN LONG %d\n\n", *pid );
}


// Processus court
void ProcCourt(int *pid) {
  long i;

  for (i=0;i<LONGTIME/10;i++)
    if (i%(long)(LONGTIME/100) == 0)
      printf("Proc. Court %d - %ld\n",*pid, i);
  printf("############ FIN COURT %d\n\n", *pid );
}




// Exemples de primitive d'election definie par l'utilisateur
// Remarques : les primitives d'election sont appel�es directement
//             depuis la librairie. Elles ne sont app�l�es que si au
//             moins un processus est � l'etat pret (RUN)
//             Ces primitives manipulent la table globale des processus
//             d�finie dans sched.h


// Election al�atoire
int RandomElect(void) {
  int i;

  printf("RANDOM Election !\n");

  do {
    i = (int) ((float)MAXPROC*rand()/(RAND_MAX+1.0));
  } while (Tproc[i].flag != RUN);

  return i;
}


// Election de SJF "Shortest Job Fisrt"
/*int SJFElect(void) {
  int p=0;
  printf("SJF Election !\n");
  //Choisir le processus p  - A ecrire en TP
  for (int i=0; i<MAXPROC; i++){
    if ((Tproc[i].flag == RUN)  && (Tproc[i].duration <= Tproc[p].duration))
      p=i;
  }
  return p;	
}*/

// Election de SJF "Shortest Job Fisrt"
int SJFElect(void) {
  int p;
  double min = 1E5;
  printf("min = %lf\n", min);
  printf("SJF Election !\n");
  /* Choisir le processus p  - A ecrire en TP */
  for(int i=0; i < MAXPROC; i++){
    if (( Tproc[i].flag == RUN) && (Tproc[i].duration < min)){
  	p = i;
	  min = Tproc[i].duration;
    }
  }
  return p;	
}


// Approximation SJF
int ApproxSJF2(void) {
  int p;
  double ncpumin = 1E8;
  printf("ApproxSJF Election !\n");
  // Choisir le processus p  - A ecrire en TP
  for (int i=0; i<MAXPROC; i++){
    if ((Tproc[i].flag == RUN)  && (Tproc[i].ncpu < ncpumin)){
      p=i;
      ncpumin = Tproc[i].ncpu;
    }
  }
  return p;	
}

// Approximation SJF
int ApproxSJF(void) {
  int p;

  /* Choisir le processus p - A ecrire en TP */
  int tmp = GetElecProc();
  if(tmp != -1){
    Tproc[tmp].prio -= Tproc[tmp].ncpu; 
    if(Tproc[tmp].prio < MINPRIO)
      Tproc[tmp].prio = MINPRIO;
  }
  double min = 8E3;

  /* Choisir le processus p  - A ecrire en TP */
  for(int i=0; i < MAXPROC; i++){
    if ( Tproc[i].flag == RUN){
      if (Tproc[i].prio < min ){
	p = i;
	min = Tproc[i].prio;
      }
    }
  }
  return p;
}



int main (int argc, char *argv[]) {
  int i;
  int *j;  

  
  // Cr�er les processus long
  for  (i = 0; i < 2; i++) {
    j = (int *) malloc(sizeof(int));
    *j= i;
    CreateProc((function_t)ProcLong,(void *)j, 80);
  }

  // Definir une nouvelle primitive d'election avec un quantum de 1 seconde
  SchedParam(NEW, 1, ApproxSJF2);

  // Lancer l'ordonnanceur en mode non "verbeux"
  sched(0);     

  // Imprimer les statistiques
  PrintStat();

  return EXIT_SUCCESS;

}
