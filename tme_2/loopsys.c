#include <unistd.h>

int main(){
    for(int i=0; i<50000000; i++) getpid();
    return 0;
}

