#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>

int id;

void* fun(){
  char old[50];
  char* a;
  while(1){
    sleep(1);
    a = (char*)shmat(id, NULL, 0);
    if (a == NULL){
      return NULL;
    }else
      if(strcmp(a,old)!=0){
	printf("%s",a);
	strcpy(old,a);
      }
  }
}

int main(int argc, char** argv){
  if(argc<3||strlen(argv[1])>10){
    return 1;
  }
  int x = atoi(argv[2]);
  id=shmget(x, 50*sizeof(char), 0666);
  if(id == -1){
   return 0;
  }
  pthread_t ww;
  pthread_create(&ww, NULL, fun, NULL);
  char* a;
  a = (char*)shmat(id, NULL, 0);
  if(a == NULL){
    return 0;
  }
  char s[50];
  int ll=strlen(argv[1]);
  strcpy(s,argv[1]);
  s[ll]=' ';
  while(1){
    fgets(s+ll+1, 50-(ll+1), stdin);
    strcpy(a,s);
  }
}
