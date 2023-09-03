#include "app.h"
#include "book.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NO_BOOK(x) if (x == NULL){ printf("[error] No existe libro que cumpla los parametros.\n"); return; }

// Añade un libro a la lista
void RegisterBook(List* L, char* str)
{
    Book* book = StrToBook(str);
    pushBack(L, book);
}

void ShowBookData(List* L, char* title, char* author)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    PrintBook(book);
}

// Muestra por pantalla todos los libros
void ShowAllBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        PrintBook(book);
        book = nextList(L);
    }
}

void ReserveBook(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    push(book->reservations, name);
    printf("%s. Reservado.", title);
}

void CancelReservation(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    queueNode* current = book->reservations->front;
    while (current != NULL)
    {
        if(strcmp(current->data, name) == 0)
        {
            // TODO: terminar
        }

        current = current->next;
    }
}

void TakeBook(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    if((strcmp(top(book->reservations), name) == 0 && book->state == Reserved) || book->state == Available)
    {
        book->state = Taken;
        printf("Libro Prestado\n");
        if (book->state == Reserved)
            pop(book->reservations);
    }
    else
    {
        printf("[error] Usted no puede retirar el libro.\n");
    }
}

void ShowTakenBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        if(book->state == Taken)
            PrintBook(book);
        book = nextList(L);
    }
}

// Libera toda la memoria de la lista
void ClearAll(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        FreeBook(book);
        book = nextList(L);
    }
    
    cleanList(L);
    free(L);
}