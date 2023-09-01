#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef enum State
{
    Taken,
    Available,
    Reserved
} State;

typedef struct Book
{
    char* title;
    char* author;
    char* genre;
    int isbn;
    int ubication;
    State state;

    // TODO: cambiar por una Cola
    void* reservation1;
    void* reservation2;
} Book;

char* GetFile(const char* filename);
void CsvToList(List* L, const char* filename);
Book* StrToBook(char* str);
void PrintBook(Book* book);


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

Book* StrToBook(char* str)
{
    Book* book = malloc(sizeof(book));

    char** strList[3] = {&book->title, &book->author, &book->genre};

    char* element = strtok(str, ",");
    for (int i = 0; i < 3; i++)
    {
        *strList[i] = element;
        element = strtok(NULL, ",");
    }
    
    int* intList[3] = {&book->isbn, &book->ubication, (int*)&book->state};
    int baseList[3] = {10, 16, 10};

    for (int i = 0; i < 3; i++)
    {
        *intList[i] = strtol(element, NULL, baseList[i]);
        element = strtok(NULL, ",");
    }

    // TODO: Añadir Cola

    return book;
}

void FreeBook(Book* book)
{
    char** strList[3] = {&book->title, &book->author, &book->genre};

    for (int i = 0; i < 3; i++)
        free(strList[i]);
}

void PrintBook(Book* book)
{
    printf("%s, %s, %s, %i, %x, %i,\n", book->title, book->author, book->genre, book->isbn, book->ubication, book->state);
}