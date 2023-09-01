#ifndef BOOK
#define BOOK

typedef enum State
{
    Taken = 0,
    Available = 1,
    Reserved = 2
} State;

typedef struct Book
{
    char* title;
    char* author;
    char* genre;
    int isbn;
    int ubication;
    State state;

    // TODO: cambiar por una Cola
    void* reservation1;
    void* reservation2;
} Book;

Book* CreateBook();
Book* StrToBook(char* str);
void FreeBook(Book* book);
void PrintBook(Book* book);
void SetBookState(Book* book, const char* str);


#endif // BOOK