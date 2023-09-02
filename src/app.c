#include "app.h"
#include "book.h"

#include <stdlib.h>

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

// Añade un libro a la lista
void RegisterBook(List* L, char* str)
{
    Book* book = StrToBook(str);
    pushBack(L, book);
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