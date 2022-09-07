/*
 * Exercise 8-4. The standard library function
 *    int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for
 * the other functions of the library.
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#define EOF       (-1)
#define BUFSIZ    4096
#define FOPEN_MAX 20

typedef struct _iobuf {
  char *base;
  char *end;
  char *ptr;
  char flags;
  int fd;
} FILE;

enum {
  _READ  = 001,
  _WRITE = 002,
  _UNBUF = 004,
  _EOF   = 010,
  _ERR   = 020
};

enum { STDIN_FD = 0, STDOUT_FD, STDERR_FD };

#define _FILE_new(fd, flags) { NULL, NULL, NULL, (flags), (fd) }

static FILE _iob[FOPEN_MAX] = {
  _FILE_new(STDIN_FD, _READ),
  _FILE_new(STDOUT_FD, _WRITE),
  _FILE_new(STDERR_FD, _WRITE | _UNBUF)
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define _is_unbuffered(fp) (((fp)->flags & _UNBUF))
#define _is_buffered(fp)   (!_is_unbuffered(fp))

#define _is_ostream(fp)    ((fp)->flags & _WRITE)
#define _is_istream(fp)    ((fp)->flags & _READ)

#define _is_osbuffered(fp) (((fp)->flags & (_WRITE | _UNBUF)) == _WRITE)
#define _is_isbuffered(fp) (((fp)->flags & (_READ | _UNBUF)) == _READ)

#define _WBUF_IS_FULL(fp)  ((fp)->ptr == (fp)->end)

#define getc(fp) ((_RBUF_IS_EMPTY(fp)) ? _fillbuf(fp) : _bufpop(fp))

#define putc(c, fp) ((_WBUF_IS_FULL(fp)) ? _flushbuf(c, fp) : _bufpush(c, fp))

#define getchar()  getc(stdin)
#define putchar(c) putc((c), stdout)

#define ferror(fp) ((fp)->flags & _ERR)
#define feof(fp)   ((fp)->flags & _EOF)

static int
_fread(FILE *fp, char *buf, int n)
{
  int n_read;

  if ((n_read = read(fp->fd, buf, n)) <= 0) {
    fp->flags |= (n_read == 0) ? _EOF : _ERR;
    return 0;
  }
  return n_read;
}

#define _bufalloc(fp) ((fp)->base = (char *) malloc(BUFSIZ))

#define _bufpop(fp) ((unsigned char) *(fp)->ptr++)

#define _RBUF_IS_EMPTY(fp) ((fp)->ptr == (fp)->end)

static int
_fillbuf(FILE *fp)
{
  if (!_is_istream(fp) || feof(fp) || ferror(fp))
    return EOF;

  if (_is_unbuffered(fp)) {
    unsigned char tmpbuf;

    return (_fread(fp, (char *) &tmpbuf, 1) == 1) ? tmpbuf : EOF;
  }

  if (fp->base == NULL)
    if (_bufalloc(fp) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->end = fp->base + _fread(fp, fp->base, BUFSIZ);
  return (_RBUF_IS_EMPTY(fp)) ? EOF : _bufpop(fp);
}

static int
_fwrite(FILE *fp, const char *ptr, int n)
{
  int n_written;

  if (ferror(fp))
    return 0;

  if ((n_written = write(fp->fd, ptr, n)) != n)
    fp->flags |= _ERR;
  return n_written;
}

static int
_flush_ostream(FILE *fp)
{
  int n      = (fp->ptr - fp->base);
  int rvalue = 0;

  if (n && _fwrite(fp, (char *) fp->base, n) != n)
    rvalue = EOF;
  fp->ptr = fp->base;
  return rvalue;
}

#define _IOB_END (_iob + FOPEN_MAX)

static int
_flush_all_os(void)
{
  FILE *fp;
  int rvalue;

  rvalue = 0;
  for (fp = _iob; fp < _IOB_END; ++fp)
    if (_is_osbuffered(fp))
      if (_flush_ostream(fp))
        rvalue = EOF;
  return rvalue;
}

#define _DISCARD_RBUF(fp)                                                      \
  ((void) ((fp)->ptr = (fp)->base, (fp)->end = fp->base))

static int
fflush(FILE *fp)
{
  if (fp == NULL)
    return _flush_all_os();
  else if (_is_buffered(fp)) {
    if (_is_ostream(fp))
      return _flush_ostream(fp);
    _DISCARD_RBUF(fp);
  }
  return 0;
}

#define _bufpush(c, fp) ((unsigned char) (*(fp)->ptr++ = (c)))

static int
_flushbuf(int c, FILE *fp)
{
  if (!_is_ostream(fp) || ferror(fp))
    return EOF;

  if (_is_unbuffered(fp)) {
    char tmpbuf = c;

    return (_fwrite(fp, &tmpbuf, 1) == 1) ? c : EOF;
  }

  if (fp->base == NULL) {
    if (_bufalloc(fp) == NULL)
      return EOF;
    fp->ptr = fp->base;
    fp->end = fp->base + BUFSIZ;
  } else if (fflush(fp))
    return EOF;
  return _bufpush(c, fp);
}

#define _FOUND_FREE_SLOT(fp) (((fp)->flags & (_WRITE | _READ)) == 0)

#define _IS_MODE_VALID(_m) (*(_m) == 'r' || *(_m) == 'w' || *(_m) == 'a')

#define _open_read(fname)  open(fname, O_RDONLY, 0)
#define _open_write(fname) open(fname, O_WRONLY, 0)

#define PERMS 0666

static FILE *
fopen(const char *filename, const char *mode)
{
  FILE *fp;
  int fd;

  if (!_IS_MODE_VALID(mode))
    return NULL;

  /* search for free slot */
  for (fp = _iob; fp < _IOB_END; ++fp)
    if (_FOUND_FREE_SLOT(fp))
      break;
  if (fp == _IOB_END)
    return NULL;

  /* open file */
  if (*mode == 'w')
    fd = _open_write(filename);
  else if (*mode == 'r')
    fd = _open_read(filename);
  else {
    if ((fd = _open_write(filename)) == -1)
      fd = creat(filename, PERMS);
    lseek(fd, 0L, SEEK_END); /* SEEK_END defined on unistd.h */
  }

  if (fd == -1)
    return NULL;

  /* init FILE */
  fp->base  = NULL;
  fp->end   = NULL;
  fp->ptr   = NULL;
  fp->flags = (*mode == 'r') ? _READ : _WRITE;
  fp->fd    = fd;
  return fp;
}

static int
fclose(FILE *fp)
{
  int rvalue;

  rvalue    = fflush(fp);
  fp->flags = 0;
  return (close(fp->fd)) ? EOF : rvalue;
}

static int
fseek(FILE *fp, long offset, int origin)
{
  if (_is_ostream(fp)) {
    if (_flush_ostream(fp))
      return -1;
    return (lseek(fp->fd, offset, origin) < 0) ? -1 : 0;
  } else if (_is_istream(fp)) {
    long bufpos, endpos, newpos;

    if (origin == SEEK_CUR)
      offset -= fp->end - fp->ptr;

    endpos = lseek(fp->fd, 0L, SEEK_CUR);
    newpos = lseek(fp->fd, offset, origin);
    bufpos = endpos - (fp->end - fp->base);

    if (newpos < 0)
      return -1;

    if (newpos >= bufpos && newpos < endpos)
      fp->ptr = fp->base + (newpos - bufpos);
    else
      _DISCARD_RBUF(fp);
  }
  return 0;
}

static int
fputs(const char *s, FILE *fp)
{
  int len;

  if (!_is_ostream(fp) || ferror(fp))
    return EOF;

  len = strlen(s);
  if (_is_unbuffered(fp))
    return (_fwrite(fp, s, len) != len) ? EOF : 1;

  while (len) {
    if (putc(*s++, fp) == EOF)
      return EOF;
    --len;
  }
  return 1;
}

enum { EXIT_FILE_FAIL = 1 };

#define F_NAME "test.txt"

#define N_READ 5

#define FOPEN(fp, mode)                                                        \
  do {                                                                         \
    if (((fp) = fopen(F_NAME, mode)) == NULL) {                                \
      fputs("Could not open file `" F_NAME "`\n", stderr);                     \
      return EXIT_FILE_FAIL;                                                   \
    }                                                                          \
  } while (0)

int
main(void)
{
  const char buf[] = "Lorem ipsum dolor sit amet";
  FILE *fp;
  unsigned n;

  FOPEN(fp, "w");
  fputs(buf, fp);
  fclose(fp);

  FOPEN(fp, "r");

  for (n = 0; getc(fp) != 'm'; ++n)
    continue;

  fseek(fp, 1, SEEK_CUR);

  assert(getc(fp) == buf[6]); /* buf[6] == 'i' */

  fclose(fp);
  return 0;
}
