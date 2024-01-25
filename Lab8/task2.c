#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int pid=fork();
    int var=0;
    if(pid<0){
        printf("Error Occured\n");
    }
    else if(pid==0){
        var+=200042121;
        printf("Child Print %d\n",var);
    }
    else{
        var+=121;
        printf("Parent Print %d\n",var);
    }
}
