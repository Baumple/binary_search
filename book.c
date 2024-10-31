#ifndef FILE_H
#define FILE_H
struct Book {
  char* title;
  char* isbn;
  char* author;
} typedef Book;

int compare_book_author(void* p1, void* p2) {
  Book book = * (Book *) p1;
  char* author = (char*) p2;
  return strcmp(book.author, author);
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
