#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int tab[2], ans;
  pid_t pid;
  /* demande de création du pipe au système*/
  ans= pipe(tab);
  if(ans< 0)
  {
    //Une erreur s'est produite lors de la création du pipe
    fprintf(stderr, "Erreur de création du pipe (%d)\n", errno);
    return 1;
  }
  pid = fork(); // demande de création du processus fils
  if(pid < 0)
  {
    /* Une erreur s'est produite lors de la création du processus fils*/
    fprintf(stderr, "Erreur de création du fils(%d)\n", errno);
    return 1;
  }
  if(pid == 0)
   {
    /*Nous sommes dans le fils*/
    close(tab[1]); // Le fils ferme l'extrémité d'écriture du pipe
    char buffer[20];
    while(read(tab[0], buffer, 20)!=0)
   {
    /* Le fils se met en attente de lecture des données du pipe*/
    printf("Fils(%s)\n", buffer);
    }
   }

  else
    {
    close(tab[0]); /* Le père ferme l'extrémité de lecture du pipe*/
    char buffer[20];
      strcpy(buffer,"message secret");
      write(tab[1], buffer, strlen(buffer)+1); /* le père écrit la chaine de caractère dans le pipe */
    }
    int status;
    int pid2 = wait(&status); // Le père attend la fin du fils.
}
