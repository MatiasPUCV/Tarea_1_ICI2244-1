#ifndef BOOK
#define BOOK

typedef enum State
{
    Taken,
    Available,
    Reserved
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

Book* StrToBook(char* str);

void FreeBook(Book* book);
void PrintBook(Book* book);

#endif // BOOK