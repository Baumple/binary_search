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

// Compare a book title to another book. Their ordering is decided through
// their title.
int compare_book_title(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book *) p2;
  return strcmp(b1.title, b2.title);
}

int compare_book_isbn(void* p1, void* p2) {
  Book b1 = * (Book *) p1;
  Book b2 = * (Book *) p2;

  if (b1.isbn < b2.isbn) {
    return -1;
  } else if (b1.isbn == b2.isbn) {
    return 0;
  } else {
    return 1;
  }
}

// compare a book title to a given string
int compare_book_title_s(void* p1, void* title) {
  Book b1 = * (Book *) p1;
  char* title_s = (char *) title;
  return strcmp(b1.title, title_s);
}

// compare a book author to a given string
int compare_book_author_s(void* p1, void* author) {
  Book b1 = * (Book *) p1;
  char* author_s = (char *) author;
  return strcmp(b1.author, author_s);
}

// compare a book isbn to a given uint64_t
int compare_book_isbn_ui(void* p1, void* isbn) {
  Book b1 = * (Book *) p1;
  uint64_t isbn_ui = * (uint64_t *) isbn;

  if (b1.isbn < isbn_ui) {
    return -1;
  } else if (b1.isbn == isbn_ui) {
    return 0;
  } else {
    return 1;
  }
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
