/*
 * Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
 */
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define EOF       (-1)
#define BUFSIZ    4096
#define FOPEN_MAX 20

typedef struct _iobuf {
  char *base;
  char *end;
  char *ptr;
  unsigned char flags;
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
    char tmpbuf;

    return (_fread(fp, &tmpbuf, 1) == 1) ? (unsigned char) tmpbuf : EOF;
  }

  if (fp->base == NULL)
    if (_bufalloc(fp) == NULL)
      return EOF;

  fp->ptr = fp->base;
  fp->end = fp->base + _fread(fp, fp->base, BUFSIZ);

  return _RBUF_IS_EMPTY(fp) ? EOF : _bufpop(fp);
}

static int
_fwrite(FILE *fp, char *ptr, int n)
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

  if (n && _fwrite(fp, fp->base, n) != n)
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

#define _IS_MODE_VALID(m) (*(m) == 'r' || *(m) == 'w' || *(m) == 'a')

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
  return close(fp->fd) ? EOF : rvalue;
}

enum { EXIT_FILE_FAIL = 1, EXIT_WRITE_ERR };

#define COPY_TO_STDOUT(fp)                                                     \
  do {                                                                         \
    int c;                                                                     \
                                                                               \
    while ((c = getc(fp)) != EOF)                                              \
      putchar(c);                                                              \
  } while (0)

int
main(int argc, const char *const argv[])
{
  if (argc == 1)
    COPY_TO_STDOUT(stdin);
  else {
    FILE *fp;

    while (--argc) {
      if ((fp = fopen(*++argv, "r")) == NULL)
        return EXIT_FILE_FAIL;

      COPY_TO_STDOUT(fp);
      fclose(fp);
    }
  }
  fflush(stdout);
  return 0;
}
