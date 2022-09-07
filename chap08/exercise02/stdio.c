/*
 * Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explict bit
 * operations. Compare code size and execution speed.
 */
#include <assert.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

#define EOF      (-1)
#define BUFSIZ   4096
#define OPEN_MAX 20
#define PERMS    0666

#define SEEK_END 2

typedef unsigned char uchar;

typedef struct _iobuf {
  int  cnt;
  char *ptr;
  char *base;
  struct {
    unsigned read: 1;
    unsigned write: 1;
    unsigned err: 1;
    unsigned eof: 1;
    unsigned unbuf: 1;
  } flag;
  int  fd;
} FILE;

FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p)   ((p)->flag.eof)
#define ferror(p) ((p)->flag.err)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (uchar) *(p)->ptr++ : _fillbuf(p))

#define putc(c, p)                                                             \
  (--(p)->cnt >= 0 ? (uchar) (*(p)->ptr++ = (c)) : _flushbuf((x), (p)))

#define getchar()  getc(stdin)
#define putchar(c) putc((c), stdout)

FILE *
fopen(const char *name, const char *mode)
{
  int fd;
  FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; ++fp)
    if (fp->flag.read == 0 && fp->flag.write == 0)
      break;
  if (fp == _iob + OPEN_MAX)
    return NULL;

  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0, SEEK_END);
  } else
    fd = open(name, O_RDONLY, 0);

  if (fd == -1)
    return NULL;

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  if (*mode == 'r')
    fp->flag.read = 1;
  else
    fp->flag.write = 1;
  return fp;
}

int
_fillbuf(FILE *fp)
{
  int bufsize;

  if (fp->flag.err || fp->flag.eof || fp->flag.read == 0)
    return EOF;

  bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
  if (fp->base == NULL)
    if ((fp->base = (char *) malloc(bufsize)) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->base, bufsize);

  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->flag.eof = 1;
    } else {
      fp->flag.err = 1;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (uchar) *fp->ptr++;
}


static void
test_invalid_mode(void)
{
  FILE *fp;

  fp = fopen("stdio.c", "u");

  assert(fp == NULL);
}

int printf(const char *, ...);

static void
test_cat(void)
{
  FILE *fp;
  int c;

  fp = fopen("stdio.c", "r");
  assert(fp != NULL);

  while ((c = getc(fp)) != EOF)
    printf("%c", (char) c);
}

int
main(void)
{
  test_invalid_mode();
  test_cat();
  return 0;
}
