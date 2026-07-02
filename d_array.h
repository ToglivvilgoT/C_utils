#pragma once

#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
  int   *items;
  size_t capacity, size;
} iVec;

typedef struct {
  long long *items;
  size_t     capacity, size;
} llVec;

typedef struct {
  float *items;
  size_t capacity, size;
} fVec;

typedef struct {
  double *items;
  size_t  capacity, size;
} dVec;

typedef struct {
  char const **items;
  size_t       capacity, size;
} strVec;

#define clear(xs) xs.size = 0;

#define empty(xs)                                                              \
  ({                                                                           \
    bool retval;                                                               \
    retval = !(xs.size);                                                       \
    retval;                                                                    \
  })

#define append(xs, x)                                                          \
  do {                                                                         \
    if (xs.size >= xs.capacity)                                                \
    {                                                                          \
      if (xs.capacity == 0)                                                    \
        xs.capacity = 256;                                                     \
      else                                                                     \
        xs.capacity *= 2;                                                      \
      xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items));           \
    }                                                                          \
    xs.items[xs.size++] = x;                                                   \
  } while (0);

#define vec_remove(xs, i)                                                      \
  do {                                                                         \
    if (i >= xs.size) break;                                                   \
    size_t nr_of_elems = xs.size - i - 1;                                      \
    memmove(&xs.items[i], &xs.items[i + 1], nr_of_elems * sizeof(*xs.items));  \
    xs.size--;                                                                 \
  } while (0);

#define pop(xs)                                                                \
  ({                                                                           \
    __auto_type retval = (*xs.items);                                          \
    retval             = xs.items[xs.size - 1];                                \
    xs.size--;                                                                 \
    retval;                                                                    \
  })

#define insert(xs, x, i)                                                       \
  do {                                                                         \
    if (xs.size == xs.capacity)                                                \
    {                                                                          \
      if (xs.capacity == 0)                                                    \
        xs.capacity = 256;                                                     \
      else                                                                     \
        xs.capacity *= 2;                                                      \
      xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items));           \
    }                                                                          \
    size_t nr_of_elems = xs.size - i;                                          \
    memmove(&xs.items[i + 1], &xs.items[i], nr_of_elems * sizeof(*xs.items));  \
    xs.items[i] = x;                                                           \
    xs.size++;                                                                 \
  } while (0);

#define sort(xs, comp)                                                         \
  do {                                                                         \
    qsort(xs.items, xs.size, sizeof(*xs.items), comp);                         \
  } while (0);

#define contains(xs, x, comp)                                                  \
  ({                                                                           \
    bool retval = false;                                                       \
    for (int i = 0; i < xs.size; ++i)                                          \
    {                                                                          \
      if (!comp(&xs.items[i], &x))                                             \
      {                                                                        \
        retval = true;                                                         \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    retval;                                                                    \
  })

#define copy(xs)                                                               \
  ({                                                                           \
    __auto_type xs_copy = (xs);                                                \
    xs_copy.capacity    = xs.capacity;                                         \
    xs_copy.size        = xs.size;                                             \
    xs_copy.items       = malloc(xs.capacity * sizeof(*xs.items));             \
    memcpy(xs_copy.items, xs.items, xs.size * sizeof(*xs.items));              \
    xs_copy;                                                                   \
  })

#define reduce(xs, func, init_val)                                             \
  ({                                                                           \
    __auto_type retval = init_val;                                             \
    for (int i = 0; i < xs.size; ++i) { retval = func(retval, xs.items[i]); }  \
    retval;                                                                    \
  })

#define filter(xs, func)                                                       \
  ({                                                                           \
    __auto_type xs_copy = copy(xs);                                            \
    clear(xs_copy);                                                            \
    for (int i = 0; i < xs.size; ++i)                                          \
    {                                                                          \
      if (func(xs.items[i])) append(xs_copy, xs.items[i]);                     \
    }                                                                          \
    xs_copy;                                                                   \
  })

#define for_each(xs, func, ctx)                                                \
  do {                                                                         \
    for (int i = 0; i < xs.size; ++i) { func(xs.items[i], ctx); }              \
  } while (0);

#define map(xs, func, ctx)                                                     \
  do {                                                                         \
    for (int i = 0; i < xs.size; ++i) { func(&xs.items[i], ctx); }             \
  } while (0);


int comp_int(void const *ptr1, void const *ptr2);
int comp_ll(void const *ptr1, void const *ptr2);
int comp_float(void const *ptr1, void const *ptr2);
int comp_double(void const *ptr1, void const *ptr2);
int comp_str(void const *ptr1, void const *ptr2);
