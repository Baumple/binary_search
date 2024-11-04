#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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

#define N 100000
void init_turbo_array(Array* arr) {
  // basically a custom `init_array` function. We set the list size to be N,
  // allocate the according memory and set the element size, then overwrite the
  // allocated memory.
  arr->arr = malloc(sizeof(Book) * N);
  arr->el_size = sizeof(Book);
  arr->len = N;

  for (int i = 0; i < N; i++) {
    Book* book = (Book *) get_array(arr, i);
    book->title = "Title";
    book->author = "Author";
    book->isbn = 10000000 + rand();
  }
}

// Test where its very unlikely that 123456789 is in the array
void turbo_array_test1() {
  printf("Turbo Array Test 1\n");
  Array arr;
  init_turbo_array(&arr);

  printf("Finished allocating list\n");
  sort_array(&arr, compare_book_isbn);
  printf("Finished sorting list\n");

  uint64_t search_value = 123456789;
  int depth = 0;
  int res = search_array(&arr, (void*) &search_value, compare_book_isbn_ui, &depth);

  printf("Search result: %d\n", res);
  printf("Iterations taken: %d\n", depth);

  printf("\n");
}

// Test where 123456789 is guaranteed to be in the array
void turbo_array_test2() {
  printf("Turbo Array Test 2\n");
  Array arr;

  init_turbo_array(&arr);
  printf("Finished allocating list\n");

  // set first value to be the search value so that we can be sure it is in the array
  Book* book = (Book *)get_array(&arr, 0);
  book->title = "Flag";
  book->author = "Flag";
  book->isbn = 123456789;

  sort_array(&arr, compare_book_isbn);
  printf("Finished sorting list\n");

  uint64_t search_value = 123456789;
  int depth = 0;
  int res = search_array(&arr, (void*) &search_value, compare_book_isbn_ui, &depth);

  Book matching = * (Book *) get_array(&arr, res);
  assert(matching.isbn == 123456789);

  printf("Search result: %d\n", res);
  printf("Iterations taken: %d\n", depth);
  printf("\n");
}

int main(int argc, char *argv[])
{
  srand(time(NULL));

  if (argc > 1) {
    turbo_array_test1();
    turbo_array_test2();
  }

  // Array arr;
  // init_array(&arr, sizeof(Book));
  // Book value1 = {
  //   .author = "First author",
  //   .title = "First title", 
  //   .isbn = rand(), 
  // };
  // Book value2 =  {
  //   .author = "Some author",
  //   .title = "Some title",
  //   .isbn = 420,
  // };
  // Book value3 = {
  //   .author = "Thomas Jefferson",
  //   .title = "Lustiges Taschenbuch Band 99",
  //   .isbn = rand(),
  // };
  // Book value4 = {
  //   .author = "Charles Martinee",
  //   .title = "Game of Thrones",
  //   .isbn = rand(),
  // };

  // add_array(&arr, &value1);
  // add_array(&arr, &value2);
  // add_array(&arr, &value3);
  // add_array(&arr, &value4);

  // int res;
  // char input[50];

  // printf("Search by title (1), author(2) or isbn(3): ");
  // fgets(input, sizeof(input), stdin);
  // int answer = atoi(input);

  // switch (answer) {
  //   case SearchTitle:
  //     sort_array(&arr, compare_book_title);
  //     // sort array for binary search
  //     each_array(&arr, print_book_voidptr);
  //     // read title into memory
  //     read_input(input);
  //     // search array for input
  //     res = search_array(&arr, (void*) input, compare_book_title_s);
  //     if (res < 0) {
  //       printf("Could not find given input in the book list. Maybe try another search type.\n");
  //     } else {
  //       printf("Your book resides at index %d!\n", res);
  //     }
  //     break;
  //   case SearchAuthor:
  //     sort_array(&arr, compare_book_author);
  //     each_array(&arr, print_book_voidptr);

  //     read_input(input);
  //     printf("input = '%s'\n", input);
  //     res = search_array(&arr, (void*) input, compare_book_author_s);

  //     if (res < 0) {
  //       printf("Could not find given input in the book list. Maybe try another search type.\n");
  //     } else {
  //       printf("Your book resides at index %d!\n", res);
  //     }
  //     break;
  //   case SearchISBN:
  //     sort_array(&arr, compare_book_isbn);
  //     each_array(&arr, print_book_voidptr);

  //     read_input(input);
  //     uint64_t input_num = atoi(input);
  //     res = search_array(&arr, (void*) &input_num, compare_book_isbn_ui);

  //     if (res < 0) {
  //       printf("Could not find given input in the book list. Maybe try another search type.\n");
  //     } else {
  //       printf("Your book resides at index %d!\n", res);
  //     }
  //     break;
  //   default:
  //     printf("Not an option!\n");
  // }

  // free_array(&arr);

  return EXIT_SUCCESS;
}
