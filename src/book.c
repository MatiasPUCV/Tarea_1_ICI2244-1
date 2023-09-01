#include "book.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convierte una STR con la información de un libro
// separado por comas en la structura.
//
//  Ejemplo de los datos a recibir:
//      "Orgullo y Prejuicio,Austen,Romance,22334455,A5,Prestado,Estudiante5";
//
Book* StrToBook(char* str)
{
    Book* book = malloc(sizeof(book));

    char** strList[3] = {&book->title, &book->author, &book->genre};

    char* element = strtok(str, ",");
    for (int i = 0; i < 3; i++)
    {
        *strList[i] = element;
        element = strtok(NULL, ",");

        // TODO: revisar que ninguna STR
        // sea de más de 50 caracteres
    }
    
    int* intList[3] = {&book->isbn, &book->ubication, (int*)&book->state};
    int baseList[3] = {10, 16, 10};

    for (int i = 0; i < 3; i++)
    {
        *intList[i] = strtol(element, NULL, baseList[i]);
        element = strtok(NULL, ",");
    }

    return book;
}

// Libera la memoria de las STR que contiene 'Book'
void FreeBook(Book* book)
{
    char** strList[3] = {&book->title, &book->author, &book->genre};
    for (int i = 0; i < 3; i++)
    {
        if(*strList[i] == NULL)
            free(*strList[i]);

    }

    if (book == NULL)
        free(book);
}

void PrintBook(Book* book)
{
    printf("%s, %s, %s, %i, %x, %i,\n", book->title, book->author, book->genre, book->isbn, book->ubication, book->state);

    // TODO: Añadir Cola
}