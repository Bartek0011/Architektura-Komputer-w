#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char** ar(char* args);
char *getLine();
void execute(char** argv);
void fun(int q){
	if(q==11)
	  exit(0);
}

char** ar(char* args){
  int i=0;
  int ww=1;
  while(args[i]!='\n'){
    if(args[i]==' ')
      ++ww;
      ++i;
  }
  char **argv;
  argv=(char**)malloc((ww+1)*sizeof(char *));
  int j;
  int m=0;
  for(j=0;j<i;j++){
    int nn=0;
    while(args[j]!=' '&&args[j]!='\n'){
      nn++;
      j++;
    }
    argv[m]=(char *)malloc(sizeof(char)*(nn+1));
    int k=j-nn;
    int l;
    for(l=0;l<nn;l++){
	argv[m][l]=args[k];
	k++;
    }
    argv[m][l]='\0';
    m++;
  }
  argv[ww]=NULL;
  free(args);
  args=NULL;
  return argv;
}

char *getLine(){
  char* ll=malloc(sizeof *ll *(50));
  fgets(ll, 49, stdin);
  ll[49]='\0';
  return ll;
}
void execute(char** argv){


  int pid;
  int l=0;
  int aa=0;
  while(argv[l]!=NULL)
    l++;
    l--;
  int i=0;
  int pp=0;
  for(i=0;i<l;++i)
     if(0==strcmp(argv[i],"|"))
       pp++;
  int pap=0;
  for(i=0;i<l;++i)
     if(0==strcmp(argv[i],">"))
       pap++;
  int p[2];
  int fd_in = 0;
  int cc=0;
  int precc=0;
  char* nn=NULL;
  
  while(pp>=0){
    precc=cc;
    if(pp==0){
      if(0==strcmp(argv[l],"&")){
	free(argv[l]);
	argv[l]=NULL;
	aa=1;
      }
    }else{
	while(0!=strcmp(argv[cc],"|")){
	  cc++;
	}
	
	  nn=argv[cc];
	  argv[cc]=NULL;
	  cc++;
    }
    pipe(p);
    int status;
    if ((pid = fork())<0){
      exit(1);
    }else
    if(pid==0){
      dup2(fd_in, 0);
      if (pp!=0){
				dup2(p[1], 1);
      }
      close(p[0]);
      execvp(argv[precc], argv+precc);
      exit(0);
      }
      else{
	if(!aa)
	  wait(&status);
	
	--pp;
	close(p[1]);
	fd_in = p[0];
	if(nn!=NULL){
	  argv[cc-1]=nn;
	  nn=NULL;
	}
      }
  }
  i=0;
  while(argv[i]!=NULL){
    free(argv[i]);
    argv[i]=NULL;
    ++i;
    }
  free(argv);
  argv=NULL;
}


int main(){
  int i;
  for(i=1;i<=64;++i)
    signal(i,fun);
  char *ll=NULL;
  char** c=NULL;
  free(ll);
  while(1){
    printf("lsh& ");
    ll=getLine();
    if(strcmp(ll,"exit\n")==0)
      break;
    if(strcmp(ll,"\n")==0){
      continue;
      free(ll);
      ll=NULL;
    }
    c=ar(ll);
    execute(c);
  }
}
