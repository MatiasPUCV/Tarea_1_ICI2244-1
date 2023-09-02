#include "app.h"
#include "book.h"

#include <stdlib.h>

void ShowAllBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        PrintBook(book);
        book = nextList(L);
    }
}

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