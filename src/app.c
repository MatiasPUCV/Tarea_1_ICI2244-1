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

void RegisterBook(List* L, char* str)
{
    Book* book = StrToBook(str);
    pushBack(L, book);
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