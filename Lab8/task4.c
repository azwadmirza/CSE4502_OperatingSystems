#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>


int main(int argc, char *argv[]){
    pid_t pid=fork();
    if(pid<0){
        printf("Error occured");
    }
    else if(pid==0){
        printf("Hi I am a child process\n");
    }
    else{
        wait(NULL);
        if(argc==0){
            printf("No execution instruction given");
        }
        else{
            printf("Executing : ");
            for(int i=1;i<argc;i++){
                printf("%s ",argv[i]);
            }
            execvp(argv[0],&argv[1]);
        }
    }
}