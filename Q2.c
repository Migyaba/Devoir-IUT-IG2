#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();
    if (pid<0)
    {
        printf("\n Erreur fork \n");
        return 1;
    }
    if (pid=1)
    {
        printf(" Je suis le fils %d \n, mon père \n", getppid());
    }
    else
    {
        printf(" Je suis le père %d \n, mon fils \n", getppid());
    }
    return 0;
}
