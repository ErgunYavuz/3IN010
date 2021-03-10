#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
/*
int main(){
    printf("hello im dad\n");
    if(fork()==0) {
        printf("hello im son\n");
    }
    wait(NULL);
    printf("this is the end\n");
    return 0;
}*/

int main(int argc, char *argv[]){
    //to check store the status of the childs 
    int status = 0;
    
    //start at 2 cause 0 = func name, 1 = word to search 
    for (int i=2; i<argc; i++){
        if (fork() == 0 ) {
            execlp("grep","grep","--color", argv[1], argv[i],NULL);
        }
    }
    while (wait(NULL) > 0);
    return 0;
}

/*
struct rusage usage;
struct timeval start, end;

int main (int argc, char *argv[]){
  int i = 0;
  pid_t *tab = (pid_t *)malloc((argc-2)*sizeof(pid_t));
  for(i = 2; i < argc; i++){
    if(fork() == 0){
      tab[i-2] = getpid();
      sleep(10);
      execl("/bin/grep", "grep", argv[1], argv[i], NULL);
      //execl("/bin/sleep     ","sleep(50)   ",NULL);
    }
  }
  for(i = 2; i < argc; i++){
    wait4(tab[i-2],NULL,0,&usage);
    printf("Ended at: %ld.%lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
  }
  return 0;
}*/