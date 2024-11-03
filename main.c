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

int compare_test(void* a, void* b) {
  return 1;
}

int main(int argc, char *argv[])
{
  Array arr;
  init_array(&arr, sizeof(Book));

  Book value1 = {
    .title = "AAAA", 
    .isbn = "asdjjuz", 
    .author = "AAAA"
  };
  Book value2 =  {
    .title = "Arrasdsa",
    .isbn = "Arrasdsa",
    .author = "CCCC"
  };
  Book value3 = {
    .title = "Title2",
    .isbn = "aijsdlajs",
    .author = "BBBB"
  };

  add_array(&arr, &value1);
  add_array(&arr, &value2);
  add_array(&arr, &value3);

  printf("PRE SORT: \n");
  each_array(&arr, print_book_voidptr);

  sort_array(&arr, compare_book_author, 0, arr.len);
  printf("##############################################\n");

  printf("POST SORT: \n");
  each_array(&arr, print_book_voidptr);

  free_array(&arr);

  return EXIT_SUCCESS;
}
