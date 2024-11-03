#ifndef FILE_H
#define FILE_H
struct Book {
  char* title;
  char* author;
  uint64_t isbn;
} typedef Book;

int compare_book_author(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book *) p2;
  return strcmp(b1.author, b2.author);
}

int compare_book_title(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book *) p2;
  return strcmp(b1.title, b2.title);
}

int compare_book_isbn(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book *) p2;
  return (int) (b2.isbn - b1.isbn);
}

int compare_book_title_s(void* p1, void* title) {
  Book b1 = * (Book *) p1;
  char* title_s = (char *) title;
  return strcmp(b1.title, title_s);
}

int compare_book_author_s(void* p1, void* author) {
  Book b1 = * (Book *) p1;
  char* author_s = (char *) author;
  return strcmp(b1.author, author_s);
}

int compare_book_isbn_ui(void* p1, void* isbn) {
  Book b1 = * (Book *) p1;
  uint64_t isbn_ui = * (uint64_t *) isbn;
  return (int) (isbn_ui- b1.isbn);
}


void print_book_voidptr(void* book) {
  Book value = * (Book*) book;
  printf("Book { \n");
  printf("  author = '%s'\n", value.author);
  printf("  title  = '%s'\n", value.title);
  printf("  isbn   = '%lu'\n", value.isbn);
  printf("}\n");
}

#endif /* end of include guard: FILE_H */
