#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cbook/iolib.h>
#include <cbook/alloc.h>

static void *
mycalloc(size_t n, size_t size)
{
  void *ptr = alloc(n *= size);

  return (ptr) ? memset(ptr, 0, n) : NULL;
}

enum { EXIT_INVAL_ARGC = 1, EXIT_CALLOC_ERR };

int
main(int argc, const char *const argv[])
{
  const char *const progname = *argv;
  size_t nbytes;
  char *ptr;
  char *it;

  if (argc != 2) {
    eprintf("Usage: %s NBYTES\n", progname);
    return EXIT_INVAL_ARGC;
  }

  nbytes = strtoul(argv[1], NULL, 10);
  if ((ptr = (char *) mycalloc(nbytes, 1)) == NULL) {
    eprintf("%s: calloc error: could not allocate memory\n", progname);
    return EXIT_CALLOC_ERR;
  }

  for (it = ptr; nbytes; --nbytes, ++it)
    assert(*it == 0);
  puts("Sucess!");
  memfree(ptr);
  return EXIT_SUCCESS;
}
