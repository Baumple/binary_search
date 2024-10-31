#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

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
  int arr[] = {1, 2, 3, 4, 5, 453, 3435, 9999};
  int array_len = sizeof(arr) / sizeof(int);

  printf("Current array:\n");
  print_array(arr, 0, array_len);

  printf("Enter a number to find in the array: ");
  int needle;
  scanf("%4d", &needle);

  struct timeval start, stop;
  gettimeofday(&start, NULL);
  int res = binary_search(arr, needle, 0, array_len);
  gettimeofday(&stop, NULL);
  printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

  if (res < 0) {
    printf("Value '%d' was not in the array!", needle);
  } else {
    printf("%d\n", res);
  }

  return EXIT_SUCCESS;
}
