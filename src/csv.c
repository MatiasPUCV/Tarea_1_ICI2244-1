#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "book.h"

char* GetFile(const char* filename);

// Convierte un archivo csv a una lista
void CsvToList(List* L, const char* filename)
{
    // Consigue la infomación del archivo
    char* file = GetFile(filename);
    if(file == NULL)
        return;

    // iniciealiza variables
    size_t size = strlen(file);
    size_t lastpos = 0;
    bool first = true;

    for(size_t i = 0; i < size; i++)
    {
        char c = file[i];

        // Solo continua si se encontor un '\n' o no hay un tamaño invalido
        if(c != '\n')
            continue;

        size_t strsize = i - lastpos - 1;
        
        if (strsize == -1)
            continue;

        // Crea y puebla una str que contendara una fila del csv
        char* str = calloc(strsize + 2, sizeof(char));
        for (size_t j = 0; j < strsize + 1; j++)
        {
            str[j] = file[j + lastpos];
        }
        // Añade un ',' al final para facilitar la lectura de la fila
        if (str[strsize] != ',')
            str[strsize + 1] = ',';

        if(!first)
        {
            // Pasa la fila a un libro y lo guarda en la lista
            Book* book = StrToBook(str);
            if (book != NULL)
                pushFront(L, book);
        }
        else
        {
            // ignora la primera fila del archivo
            first = false;
        }

        free(str);
        lastpos = i + 1;
    }
}

// Exporta una lista como csv
void ListToCsv(List* L, const char* filename)
{
    // Crea el archivo
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        // ERROR
    }

    // Pasa los datos de la lista
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        PrintToFileBook(book, file);
        book = nextList(L);
    } 

    fclose(file);
}

// Lee todo un archivo y lo devuelve en forma de str
char* GetFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("El Archivo no existe\n");
        return NULL;
    }

    // Consigue el tamaño del archivo
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file) + 2;
    fseek(file, 0, SEEK_SET);

    // Guarda memoria para la str
    char* contents = calloc(size, sizeof(char));

    // Lee el archivo
    fread(contents, 1, size, file);

    // añade un salto de linea para hacer la lectuta más facil
    contents[size - 2] = '\n';

    fclose(file);

    return contents;
}