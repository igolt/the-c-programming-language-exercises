/*
 * Exercise 8-5. Modify the fsize program to print the other information
 * contained in the inode entry.
 */
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <syscall.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <cbook/iolib.h>

#define MAX_PATH 1024
#define NAME_MAX 14

typedef struct {
  long ino; /* inode number */
  char name[NAME_MAX + 1]; /* name + '\0' terminator */
} Dirent;

#define streq(s1, s2) (strcmp((s1), (s2)) == 0)

static void fsize(const char *);

int
main(int argc, char *argv[])
{
  if (argc == 1)
    fsize(".");
  else
    while (--argc)
      fsize(*++argv);
  return 0;
}

static void dirwalk(const char *, void (*)(const char *));

static void
fsize(const char *name)
{
  struct stat stbuf;

  if (stat(name, &stbuf) == -1) {
    eprintf("fsize: can't access %s\n", name);
    return;
  }

  if (S_ISDIR(stbuf.st_mode))
    dirwalk(name, fsize);
  printf("%8ld %s\n", stbuf.st_size, name);
}

static void
dirwalk(const char *dir, void (*cb)(const char *))
{
  char name[MAX_PATH];
  Dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    eprintf("dirwalk: can't open %s\n", dir);
    return;
  }

  while ((dp = read_dir(dfd)) != NULL) {
    if (streq(dp->name, ".") || streq(dp->name, ".."))
      continue;

    if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
      eprintf("dirwalk: name %s %s too long\n", dir, dp->name);
    else {
      sprintf(name, "%s/%s", dir, dp->name);
      (*cb)(name);
    }
  }
  closedir(dfd);
}
