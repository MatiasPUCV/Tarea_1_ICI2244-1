#include <stdio.h>
#include <stdlib.h>

#include "app.h"
#include "list.h"
#include "book.h"
#include "csv.h"

int main()
{
    List* library = createList();
    CsvToList(library, "biblioteca.csv");

    char test[] = "Título,Autor,Género,ISBN,Ubicación,Estado,Reservas";
    RegisterBook(library, test);

    ShowAllBooks(library);
    ClearAll(library);
}


