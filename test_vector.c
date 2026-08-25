// test_vector.c

#include "vector.h"
#include <stdbool.h>
#include <stdio.h>


INITIALIZE_VECTOR_TEMPLATE(int)


static int compare_ints(void const *a, void const *b)
{
  int x = *(int const *)a;
  int y = *(int const *)b;

  if (x < y) return -1;
  if (x > y) return 1;
  return 0;
}


static bool is_even(int x) { return x % 2 == 0; }


static int sum(int a, int b) { return a + b; }


static void multiply_by_two(int *x, void *ctx)
{
  (void)ctx;
  *x *= 2;
}


static void print_int(int x, void *ctx)
{
  (void)ctx;
  printf("%d ", x);
}

int main(void)
{
  intVec vec = {0};


  printf("=== append ===\n");

  int_append(&vec, 5);
  int_append(&vec, 3);
  int_append(&vec, 8);
  int_append(&vec, 1);

  printf("size: %zu\n", vec.size);

  for (size_t i = 0; i < vec.size; i++) printf("%d ", vec.data[i]);

  printf("\n\n");


  printf("=== insert ===\n");

  int_insert(&vec, 10, 2);

  for (size_t i = 0; i < vec.size; i++) printf("%d ", vec.data[i]);

  printf("\n\n");


  printf("=== remove ===\n");

  int_remove(&vec, 1);

  for (size_t i = 0; i < vec.size; i++) printf("%d ", vec.data[i]);

  printf("\n\n");


  printf("=== contains ===\n");

  printf("Contains 10: %s\n",
         int_contains(&vec, 10, compare_ints) ? "yes" : "no");

  printf("Contains 100: %s\n",
         int_contains(&vec, 100, compare_ints) ? "yes" : "no");

  printf("\n");


  printf("=== sort ===\n");

  int_sort(&vec, compare_ints);

  for (size_t i = 0; i < vec.size; i++) printf("%d ", vec.data[i]);

  printf("\n\n");


  printf("=== pop ===\n");

  int last = int_pop(&vec);

  printf("Popped: %d\n", last);

  printf("New size: %zu\n\n", vec.size);


  printf("=== copy ===\n");

  intVec copy = int_copy(&vec);

  int_append(&copy, 100);

  printf("Original size: %zu\n", vec.size);
  printf("Copy size: %zu\n\n", copy.size);


  printf("=== reduce ===\n");

  int total = int_reduce(&vec, sum, 0);

  printf("Sum: %d\n\n", total);


  printf("=== filter ===\n");

  intVec evens = int_copy(&vec);
  int_filter(&evens, is_even);

  for (size_t i = 0; i < evens.size; i++) printf("%d ", evens.data[i]);

  printf("\n\n");


  printf("=== map ===\n");

  int_map(&vec, multiply_by_two, NULL);

  for (size_t i = 0; i < vec.size; i++) printf("%d ", vec.data[i]);

  printf("\n\n");


  printf("=== for_each ===\n");

  int_for_each(&vec, print_int, NULL);

  printf("\n\n");


  printf("=== empty ===\n");

  printf("vec empty: %s\n", int_empty(&vec) ? "yes" : "no");


  printf("\n=== cleanup ===\n");

  int_free(&vec);
  int_free(&copy);
  int_free(&evens);

  printf("done\n");

  return 0;
}
