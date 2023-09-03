#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>

#include "queue.h"
#include "list.h"

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
    long isbn;
    int ubication;
    State state;
    Queue* reservations;

} Book;

Book* CreateBook();
Book* StrToBook(char* str);
Book* CheckForBook(List* L, char* title, char* author);

void FreeBook(Book* book);

void PrintBook(Book* book);
void PrintToStreamState(Book* book, FILE* stream);
void PrintReservations(Book* book);
void PrintToFileBook(Book* book, FILE* file);

void SetBookState(Book* book, const char* str);


#endif // BOOK_H