#include <stdio.h>
#include <pthread.h>



int main(){

void *wew(){
    printf("watek wewnetrzny\n");
}

void *zew(){
 	pthread_t ww;
	printf("watek zewnetrzny wywoluje ");
 	pthread_create(&ww, NULL, wew,NULL);

} 
  pthread_t zw;
  pthread_create(&zw,NULL,zew,NULL);
  pthread_join(zw,NULL);
}
