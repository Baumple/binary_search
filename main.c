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

enum {
  SearchTitle = 1,
  SearchAuthor = 2,
  SearchISBN = 3
};

// reads stdin and writes the input into the given buffer
void read_input(char buffer[static 50]) {
    printf("Enter input (50 chars):\n");

    if (fgets(buffer, 50, stdin) == NULL) {
      printf("Could not read stdin\n");
      exit(EXIT_FAILURE);
    }

    buffer[strcspn(buffer, "\n")] = 0; // remove trailing newline
}

int main(int argc, char *argv[])
{
  srand(1);
  Array arr;
  init_array(&arr, sizeof(Book));
  Book value1 = {
    .author = "A",
    .title = "B", 
    .isbn = rand(), 
  };
  Book value2 =  {
    .author = "C",
    .title = "A",
    .isbn = 420,
  };
  Book value3 = {
    .author = "B",
    .title = "C",
    .isbn = rand(),
  };

  add_array(&arr, &value1);
  add_array(&arr, &value2);
  add_array(&arr, &value3);

  int res;
  char input[50];

  printf("Search by title (1), author(2) or isbn(3)?\n");
  
  fgets(input, sizeof(input), stdin);
  int answer = atoi(input);

  switch (answer) {
    case SearchTitle:
      sort_array(&arr, compare_book_title);
      // sort array for binary search
      each_array(&arr, print_book_voidptr);
      // read title into memory
      read_input(input);
      // search array for input
      res = search_array(&arr, (void*) input, compare_book_title_s);
      if (res < 0) {
        printf("Could not find given input in the book list. Maybe try another search type.\n");
      } else {
        printf("Your book resides at index %d!\n", res);
      }
      break;
    case SearchAuthor:
      sort_array(&arr, compare_book_author);
      each_array(&arr, print_book_voidptr);

      read_input(input);
      res = search_array(&arr, (void*) input, compare_book_author_s);

      if (res < 0) {
        printf("Could not find given input in the book list. Maybe try another search type.\n");
      } else {
        printf("Your book resides at index %d!\n", res);
      }

      break;
    case SearchISBN:
      sort_array(&arr, compare_book_isbn);
      each_array(&arr, print_book_voidptr);

      read_input(input);
      uint64_t input_num = atoi(input);
      res = search_array(&arr, (void*) &input_num, compare_book_isbn_ui);

      if (res < 0) {
        printf("Could not find given input in the book list. Maybe try another search type.\n");
      } else {
        printf("Your book resides at index %d!\n", res);
      }
      break;
    default:
      printf("Bruh, not an option!\n");
  }

  free_array(&arr);

  return EXIT_SUCCESS;
}
