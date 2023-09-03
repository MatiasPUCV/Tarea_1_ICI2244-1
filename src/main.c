#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "app.h"

int main()
{
    List* library = CreateLibrary("biblioteca.csv");

    bool end = false;

    while (!end)

        App(library, &end);

    ClearAll(library);
}


