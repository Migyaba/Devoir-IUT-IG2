#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <md5.h>

int main(int argc, char *argv[])
  {
    if(argc<2){
      printf("Entrer un argurments");
      exit(0);
    }
    char buf[50];
    unsigned char *MD5;
    MD5= MD5File(argv[1], buf);
    printf("%s ",MD5);
    return 0;
  }
