#ifndef FILE_H
#define FILE_H
struct Book {
  char* title;
  char* isbn;
  char* author;
} typedef Book;

int compare_book_author(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book*) p2;
  return strcmp(b1.author, b2.author);
}

void print_book_voidptr(void* book) {
  Book value = * (Book*) book;
  printf("Book { \n");
  printf("  author = '%s'\n", value.author);
  printf("  title  = '%s'\n", value.title);
  printf("  isbn   = '%s'\n", value.isbn);
  printf("}\n");
}

#endif /* end of include guard: FILE_H */
