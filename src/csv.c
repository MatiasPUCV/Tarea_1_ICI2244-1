#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "book.h"

char* GetFile(const char* filename);

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

        if(c != '\n' && c != EOF)
            continue;
        
        if (strsize == -1)
            continue;

        char* str = calloc(strsize + 2, sizeof(char));
        for (size_t j = 0; j < strsize + 1; j++)
        {
            str[j] = file[j + lastpos];
        }
        if (str[strsize] != ',')
            str[strsize + 1] = ',';

        if(!first)
        {
            Book* book = StrToBook(str);
            if (book != NULL)
            {
                PrintBook(book);
                pushFront(L, book);
            }
        }
        else
        {
            first = false;
        }

        free(str);
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
    size_t size = ftell(file) + 1;
    fseek(file, 0, SEEK_SET);
    char* contents = malloc(sizeof(char)*size);

    contents[size] = '\n';

    fread(contents, 1, size, file);
    fclose(file);

    return contents;
}