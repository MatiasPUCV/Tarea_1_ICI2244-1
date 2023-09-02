#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "book.h"
#include "csv.h"

int main()
{
    List* library = createList();
    CsvToList(library, "biblioteca.csv");

    free(library);    
}


