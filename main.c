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

enum {
  SearchTitle = 1,
  SearchAuthor = 2,
  SearchISBN = 3
};

int main(int argc, char *argv[])
{
  // setup random seed, constant for testing purposes
  srand(1);
  Array arr;
  init_array(&arr, sizeof(Book));
  Book value1 = {
    .title = "B", 
    .isbn = rand(), 
    .author = "A"
  };
  Book value2 =  {
    .title = "A",
    .isbn = rand(),
    .author = "C"
  };
  Book value3 = {
    .title = "C",
    .isbn = rand(),
    .author = "B"
  };

  add_array(&arr, &value1);
  add_array(&arr, &value2);
  add_array(&arr, &value3);

  each_array(&arr, print_book_voidptr);
  sort_array(&arr, compare_book_title);
  printf("==================================\n");
  each_array(&arr, print_book_voidptr);

  return 0;
  int answer;
  printf("Search by title (1), author(2) or isbn(3)?\n");
  scanf("%d", &answer);

  switch (answer) {
    case SearchTitle:

      // read title into memory
      char title[50];
      printf("Enter title (50 chars):\n");
      scanf("%s", title);
      title[strcspn(title, "\n")] = 0;

      // search array for title
      int res = search_array(&arr, (void*) title, compare_book_title_s);
      printf("%d\n", res);
      break;
    case SearchAuthor:
      sort_array(&arr, compare_book_author);
      break;
    case SearchISBN:
      sort_array(&arr, compare_book_isbn);
      break;
    default:
      printf("Bruh, not an option!\n");
  }

  free_array(&arr);

  return EXIT_SUCCESS;
}
