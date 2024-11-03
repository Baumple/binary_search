#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "book.c"

typedef int (*CompareFunc)(void*, void*);

// My cheap-ass arraylist :)
// - `void* arr` points to the location of the list
// - `uint32_t len` is the number of elements in the list
// - `size_t el_size` is the number of bytes each element takes up
struct Array {
  void* arr;
  uint32_t len;
  size_t el_size;
} typedef Array;

// initalizes an Array struct with zero elements
void init_array(Array* arr, size_t el_size) {
  arr->arr = malloc(0 * el_size);
  arr->len = 0;
  arr->el_size = el_size;
}

// Frees the memory located at the Array.arr pointer
void free_array(Array* arr) {
  free(arr->arr);
}

// Adds an element to the list
void add_array(Array* arr, void* el) {
  uint32_t len = arr->len;
  size_t el_size = arr->el_size;

  size_t original_size = len * el_size;
  size_t new_size = (len + 1) * el_size;

  void* new_arr = malloc(new_size);

  // copy all values from the original array to the new one
  memcpy(new_arr, arr->arr, original_size);
  memcpy(new_arr + original_size, el, arr->el_size);
  arr->arr = new_arr;
  arr->len += 1;
}

// Returns a pointer to the given element at the index in the array
// WARN: WILL NOT CHECK FOR OUT OF BOUNDS!!
void* get_array(Array* arr, size_t index) {
  return (void*) (arr->arr + (arr->el_size * index));
}

void sort_array(Array* arr, CompareFunc comparison, int start, int end) {
  if ((end - start) < 2) {
    return;
  }

  int pivot = start + ((end - start) / 2);
  int index = arr->len - 1;
  while (index >= 0) {
    void* current_pivot_ptr = get_array(arr, pivot);
    void* current_value_ptr = get_array(arr, index);

    if (comparison(current_pivot_ptr, current_value_ptr)  < 0) {
      // swap pivot with smaller value
      // allocate a temp variable
      void* temp = malloc(arr->el_size);
      memcpy(temp, current_value_ptr, arr->el_size);
      memcpy(current_value_ptr, current_pivot_ptr, arr->el_size);
      memcpy(current_pivot_ptr, temp, arr->el_size);

      pivot = index;
    }
    index--;
  }

  sort_array(arr, comparison, start, pivot);
  sort_array(arr, comparison, pivot + 1, end);
}

static int do_search_array(
    // the array to search in
    Array* haystack,                 
    // needle to search for
    void* needle,                    
    // function to compare with 
    CompareFunc comparison,
    // start of range to search
    int start,
    // end of range to search
    int end
  ) {
  if ((end - start) < 1) {
    return -1;
  }

  int middle = start + (end - start) / 2;
  void* value = get_array(haystack, middle);

  int comp_res = comparison(value, needle);

  if (comp_res == 0) {
    return middle;

  } else if (comp_res < 0) {
    return do_search_array(
        haystack,
        needle,
        comparison,
        middle + 1,
        end
    );

  } else {
    return do_search_array(
        haystack,
        needle,
        comparison,
        start,
        middle
    );

  }
}

// Searches the given Arraylist.
// - `Array* haystack` a pointer pointing to the Arraylist
// - `void* needle` The needle to search for
// - `CompareFunc comparison` The comparison function to use:
//   NOTE:
//   '0' means values are equal, negative means first value is "lower" than
//   second and vice versa.
int search_array(
    // the array to search in
    Array* haystack,                 
    // needle to search for
    void* needle,                    
    // function to compare with
    CompareFunc comparison
  ) {
  return do_search_array(
      haystack,
      needle,
      comparison,
      0,
      haystack->len
  );
}

// Executes a function pointer for each element
// in the list.
void each_array(Array* arr, void (*fn)(void*)) {
  uint32_t len = arr->len;
  size_t el_size = arr->el_size;

  for (int i = 0; i < len; i++) {
    void* el = arr->arr + (i * el_size);
    fn(el);
  }
}

