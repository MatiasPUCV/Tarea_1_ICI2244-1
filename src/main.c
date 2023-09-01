#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

char* GetFile(const char* filename);
void CsvToList(List* L, const char* filename);

typedef enum State
{
    Taken,
    Available,
    Reserved
} State;

typedef struct Book
{
    char* author;
    char* genre;
    unsigned int isbn;
    State state;

    // TODO: cambiar por una Cola
    void* reservation1;
    void* reservation2;
} Book;


int main()
{
    List* Library = createList();
    CsvToList(Library, "biblioteca.csv");

    
}

void CsvToList(List* L, const char* filename)
{
    char* file = GetFile(filename);
    size_t size = strlen(file);
    size_t lastpos = 0;
    bool first = true;

    for(size_t i = 0; i < size; i++)
    {
        char c = file[i];

        if(c != '\n')
            continue;
        
        size_t strsize = i - lastpos - 1;

        if (strsize == -1)
            continue;

        char* str = calloc(strsize, sizeof(char));

        for (size_t j = 0; j < strsize; j++)
        {
            str[j] = file[j + lastpos];
        }

        if(first)
            first = false;
        else
            // Convertir a 'Book'

        lastpos = i + 1;
        free(str);
    }
}

char* GetFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("El Archivo no existe\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* contents = malloc(sizeof(char)*size);

    fread(contents, 1, size, file);
    fclose(file);

    return contents;
}