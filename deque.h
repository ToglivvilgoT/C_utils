#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIALIZE_DEQUE_TEMPLATE(TYPE)

#define DEQUE_CHUNK_SIZE 512

typedef int type;

typedef struct {
  size_t size, capacity;
  type  *map[DEQUE_CHUNK_SIZE];
} typeDeque;

static inline at(typeDeque *deque, size_t idx)
{
  if (idx > deque->size)
  {
    fprintf(stderr, "deque idx: %ld is out of range: %ld", idx, deque->size);
  }
}
