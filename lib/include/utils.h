#ifndef IGOLT_UTILS
#define IGOLT_UTILS

int isblank(int);

#define SWAP(type, a, b)                                                       \
  do {                                                                         \
    type *__a_ptr = &(a);                                                      \
    type *__b_ptr = &(b);                                                      \
    type __tmp    = (*__a_ptr);                                                \
                                                                               \
    (*__a_ptr) = (*__b_ptr);                                                   \
    (*__b_ptr) = __tmp;                                                        \
  } while (0)

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif /* IGOLT_UTILS */
