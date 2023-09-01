#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "book.h"

char* GetFile(const char* filename);
void CsvToList(List* L, const char* filename);

int main()
{
    List* library = createList();
    CsvToList(library, "biblioteca.csv");

    free(library);    
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
        size_t strsize = i - lastpos - 1;

        if(c != '\n')
            continue;
        
        if (strsize == -1)
            continue;

        char* str = calloc(strsize + 1, sizeof(char));
        for (size_t j = 0; j < strsize; j++)
        {
            str[j] = file[j + lastpos];
        }
        str[strsize] = ',';

        if(!first)
        {
            Book* book = StrToBook(str);
            PrintBook(book);
        }
        else
        {
            first = false;
        }

        lastpos = i + 1;
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

