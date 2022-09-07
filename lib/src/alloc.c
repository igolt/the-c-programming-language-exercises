#include "alloc.h"
#include "iolib.h"

#include <assert.h>
#include <unistd.h>

static Header base;
static Header *freep = NULL;

static size_t alloc_units = 0;
static size_t free_units = 0;

#define _IS_BETWEEN(p, lower, upper) ((p) > (lower) && (p) < (upper))
#define _IS_ADJACENT(lower, upper) ((lower) + (lower)->size == (upper))
#define _COMBINE(lower, upper)                                                 \
  do {                                                                         \
    (lower)->size += (upper)->size;                                            \
    (lower)->next = (upper)->next;                                             \
  } while (0)

/* implements free() */
/* return the node previous to the freed block */
static Header *
_memfree(Header *newh)
{
  extern Header *freep;
  extern size_t alloc_units;
  extern size_t free_units;
  Header *prev, *it;

  /* validate the block */
  if (newh->size == 0 || newh->size + free_units > alloc_units) {
    eputs("memfree: invalid memory block");
    return NULL;
  }

  free_units += newh->size;

  prev = freep;
  it = prev->next;
  /* search will stop in the following situations:
   * - if p < p->next
   *   . stop if newh is between p and p->next
   * - if p >= p->next
   *   . stop if newh > p or if newh < p->next */
  while (!_IS_BETWEEN(newh, it, it->next)) {
    if (it >= it->next && (newh > it || newh < it->next))
      break;
    prev = it;
    it = it->next;
  }

  if (_IS_ADJACENT(newh, it->next)) {
    _COMBINE(newh, it->next);
  } else
    newh->next = it->next;
  if (_IS_ADJACENT(it, newh)) {
    _COMBINE(it, newh);
    freep = prev;
  } else {
    it->next = newh;
    freep = it;
  }
  return freep;
}

#define MIN_UNITS 1024

#define SBRK_ERR ((void *) -1)

/* Exercise 8-8 */
static size_t
bfree(void *ptr, size_t n)
{
  Header *h;

  n = n / sizeof(Header);

  if (n < 2)
    return 0;

  h = (Header *) ptr;

  h->size = n;
  alloc_units += n;

  _memfree(h);
  return n;
}

/* on success: returns the node previous to the allocated block */
/* on failured: returns NULL */
static Header *
_morecore(size_t units)
{
  extern size_t alloc_units;
  extern size_t free_units;
  Header *header;
  void *ptr;
  void *sbrk(long);

  if (units < MIN_UNITS)
    units = MIN_UNITS;

  if ((ptr = sbrk(units * sizeof(Header))) == SBRK_ERR)
    return NULL;

  header       = (Header *) ptr;
  header->size = units;

  alloc_units += units;

  return _memfree(header);
}

#define MiB_TO_BYTES(v) ((size_t) (v) << 20)

#define MAX_BYTES MiB_TO_BYTES(1)

#define _bytes_to_units(n) (((n) -1) / sizeof(Header) + 1)

void *
alloc(size_t n)
{
  extern Header *freep;
  extern Header base;
  Header *prev, *it;

  /* Initialize the list if it's not initialized */
  if (freep == NULL) {
    base.size = 0;
    freep = base.next = &base;
  }

  /* Exercise 8-7 */
  if (n > MAX_BYTES || n == 0) {
    eputs("alloc: invalid bytes number");
    return NULL;
  }

  /* space for data + header in header units */
  n = _bytes_to_units(n) + 1;

  prev = freep;
  it = prev->next;
  while (1) {
    if (it->size >= n) {
      if (it->size == n) {
        prev->next = it->next;
      } else {
        it->size -= n;
        it += it->size;
        it->size = n;
      }

      free_units -= n;
      freep = prev;
      return (void *) (it + 1);
    }
    if (it == freep)
      if ((it = _morecore(n)) == NULL)
        return NULL;

    prev = it;
    it = it->next;
  }
}

void
memfree(void *ptr)
{
  _memfree(((Header *) ptr) - 1);
}
