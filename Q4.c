#include <stdio.h>
#include <stdlib.h>


#ifndef MD5_H
#define MD5_H

#include <sys/types.h>
#ifdef __amigaos4__
#include <machine/endian.h>
#endif


typedef unsigned int uint32;

typedef struct MD5Context {
  uint32 buf[4];
  uint32 bits[2];
  unsigned char in[64];
} MD5_CTX;

extern void MD5Init(struct MD5Context *ctx);
extern void MD5Update(struct MD5Context *ctx, unsigned char *buf,
                      unsigned int len);
extern void MD5Final(unsigned char digest[16], struct MD5Context *ctx);
extern void MD5Transform(uint32 buf[4], uint32 in[16]);
extern char *MD5File(const char *, char *);
extern char *MD5FileChunk(const char *, char *, off_t, off_t);

#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#define close  _close
#define fstat  _fstat
#define lseek  _lseek
#define read  _read
#define stat  _stat
#else
#include <unistd.h>
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH  16



static char *MD5End(MD5_CTX *ctx, char *buf)
{
  int i;
  unsigned char digest[LENGTH];
  static const char hex[] = "0123456789abcdef";

  if (!buf)
    buf = malloc(2 * LENGTH + 1);
  if (!buf)
    return 0;
  MD5Final(digest, ctx);
  for (i = 0; i < LENGTH; i++) {
    buf[i + i] = hex[digest[i] >> 4];
    buf[i + i + 1] = hex[digest[i] & 0x0f];
  }
  buf[i + i] = '\0';
  return buf;
}

char *MD5File(const char *filename, char *buf)
{
  return (MD5FileChunk(filename, buf, 0, 0));
}

char *MD5FileChunk(const char *filename, char *buf, off_t ofs, off_t len)
{
  unsigned char buffer[BUFSIZ];
  MD5_CTX ctx;
  struct stat stbuf;
  int f, i, e;
  off_t n;

  MD5Init(&ctx);
#ifdef _WIN32
  f = _open(filename, O_RDONLY | O_BINARY);
#else
  f = open(filename, O_RDONLY);
#endif
  if (f < 0)
    return 0;
  if (fstat(f, &stbuf) < 0)
    return 0;
  if (ofs > stbuf.st_size)
    ofs = stbuf.st_size;
  if ((len == 0) || (len > stbuf.st_size - ofs))
    len = stbuf.st_size - ofs;
  if (lseek(f, ofs, SEEK_SET) < 0)
    return 0;
  n = len;
  i = 0;
  while (n > 0) {
    if (n > sizeof(buffer))
      i = read(f, buffer, sizeof(buffer));
    else
      i = read(f, buffer, n);
    if (i < 0)
      break;
    MD5Update(&ctx, buffer, i);
    n -= i;
  }
  e = errno;
  close(f);
  errno = e;
  if (i < 0)
    return 0;
  return (MD5End(&ctx, buf));
}
int main( int argc , char *arg[])
{
char data[512];
char *ob=malloc(sizeof(char));
 ob= MD5File(argv[1], data)
printf(" code md5 est %S", data);
   return 0;
}
