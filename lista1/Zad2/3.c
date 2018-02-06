#include <stdio.h>
#include <unistd.h>
#include <signal.h>





int main(){
int bank = 0;

void catchF(int signo) {
    bank ++;
printf("%d", bank);
	
}

  int i;
	int ret;
	pid_t pid = 10;
 for(i=0; i<10000000; i++){
	signal(SIGUSR1, catchF);
	
  }
	printf("%d", bank);

	return 0;
}
