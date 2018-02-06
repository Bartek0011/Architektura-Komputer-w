#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>
int main(char argc,char **argv){
  int id;
  int x=atoi(argv[1]);
  id=shmget(x, 50*sizeof(char),IPC_CREAT|0666);

  char* a = (char*)shmat(id, NULL, 0);
  if(a == NULL){
    return 0;
  }
  strcpy(a,"server");
  printf("%d \n ",id);
  sleep(5000);
  if (shmctl ( id, IPC_RMID, NULL )==-1)
  return 0;
}