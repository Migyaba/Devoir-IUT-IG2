#include <sys/types.h>
#include <md5.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char c[MD5_DIGEST_LENGTH];
char *
     MD5File(const char *filename, char *buf);s

    int i;
    FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL)
{
        printf ("%s can't be opened.\n", filename);
        return 0;
}

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", c[i]);
    printf (" %s\n", filename);
    fclose (inFile);
    return 0;
}
{
  int fd1, fd2, rc;
  char buf;
  if(argc != 3)
{
  fprintf(stderr, "Syntaxe: %s f1 f2\n", argv[0]);
  exit(1);
}
    fd1 = open(argv[1], O_RDONLY);
  if(fd1 < 0)
{
  perror("open(fd1)");
  exit(1);
}
 fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
 if(fd2 < 0)
{
 perror("open(fd2)");
 exit(1);
}
 while(1)
{
  rc = read(fd1, &buf, 1);
if(rc < 0)
{
  perror("read");
  exit(1);
}
 if(rc == 0)
 break;
 rc = write(fd2, &buf, 1);
 if(rc < 0)
{
   perror("write");
   exit(1);
}
  if(rc != 1)
{
  fprintf(stderr, "écriture interrompue");
  exit(1);
}
}
  close(fd1);
  close(fd2);
return 0;
}
