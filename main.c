#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "array_list.c"
#include "book.c"

void print_array(int* arr, int start, int len) {
  printf("[ ");
  for (int i = start; i < len; i++) {
    if (i == (len - 1)) {
      printf("%d", arr[i]);
    } else {
      printf("%d, ", arr[i]);
    }
  }
  printf(" ]\n");
}

/// returns -1 if it could not find the element
int binary_search(int* haystack, int needle, int start, int end) {
  if ((end - start) < 1) {
    return -1;
  }

  int middle = start + ((end - start) / 2);
  int value = haystack[middle];

  if (value == needle) {
    return middle;
  } else if (needle > value) {
    return binary_search(haystack, needle, middle + 1 , end);
  } else if (needle < value) {
    return binary_search(haystack, needle, start, middle);
  } else {
    return -1;
  }
}

int main(int argc, char *argv[])
{
  Array arr;
  init_array(&arr, sizeof(Book));

  Book value =  {
    .title = "Title1",
    .isbn = "Deeznuts1",
    .author = "Hello1"
  };
  Book value1 = {
    .title = "Title2",
    .isbn = "Deeznuts2",
    .author = "Hello2"
  };
  Book value2 = {
    .title = "Title3", 
    .isbn = "Deeznuts3", 
    .author = "Hello3"
  };

  add_array(&arr, &value);
  add_array(&arr, &value1);
  add_array(&arr, &value2);

  void* author = (void*) "Hello2";

  int res = search_array(&arr, author, &compare_book_author);
  printf("res = %d\n", res);
  free_array(&arr);

  return EXIT_SUCCESS;
}
