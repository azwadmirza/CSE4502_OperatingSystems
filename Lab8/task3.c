#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int a=0,b=1,n=a+b,i,j;
    pid_t pid;
    printf("Enter Number: ");
    scanf("%d",&j);
    if(j<0){
        printf("Error: Number cannot be negative");
    }
    else{
        pid=fork();
        if(pid==0){
            if(j>2){
                j-=2;
                printf("%d %d ",a,b);
                for(int i=0;i<j;i++){
                    n=a+b;
                    printf("%d ",n);
                    a=b;
                    b=n;
                }
            }
            else{
                printf(" %d %d ",a,b);
            }
        }
        else{
            wait(NULL);
        }
    }
    return 0;
}