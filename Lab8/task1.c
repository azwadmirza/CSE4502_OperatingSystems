#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
  pid_t pid1=fork();
  pid_t pid2=fork();
  pid_t pid3=fork();
  if(pid1==(pid_t)0 || pid2==(pid_t)0 || pid3==(pid_t)0){
    printf("process id: %d\n",getpid());
    printf("parent process id: %d\n",getppid());
  }
  else{
    for(int i=0;i<8;i++){
      wait(NULL);
    }
    printf("parent process id: %d\n",getpid());
  }
  
  return 0;
}
