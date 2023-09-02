#ifndef BOOK
#define BOOK

#include "queue.h"

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
    Queue* reservations;

} Book;

Book* CreateBook();
Book* StrToBook(char* str);
void FreeBook(Book* book);
void PrintBook(Book* book);
void PrintState(Book* book);
void PrintReservations(Book* book);
void SetBookState(Book* book, const char* str);


#endif // BOOK