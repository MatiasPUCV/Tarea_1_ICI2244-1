#include "book.h"

#include <stdlib.h>
#include <string.h>

#include "queue.h"

void AddElementToBook(Book* book, char* element, int num);

// Convierte una STR con la información de un libro
// separado por comas en la structura.
//
//  Ejemplo de los datos a recibir:
//      "Orgullo y Prejuicio,Austen,Romance,22334455,A5,Prestado,Estudiante5";
//
Book* StrToBook(char* str)
{
    size_t size = strlen(str);
    size_t lastpos = 0;
    int elementCount = 0;

    Book* book = CreateBook();

    for(size_t i = 0; i < size; i++)
    {
        char c = str[i];
        size_t strsize = i - lastpos - 1;

        if(c == ',' || c == '\n')
        {
            if(strsize > 50)
            {
                printf("ERROR: str con más de 50 caracteres; se ignorara el libro\n");
                return NULL;
            }

            char* element = calloc(51, sizeof(char));
            for (size_t j = 0; j < strsize + 1; j++)
            {
                element[j] = str[j + lastpos];
            }

            AddElementToBook(book, element, elementCount);

            lastpos = i + 1;
            elementCount++;

        }
    }
    return book;
}

void AddElementToBook(Book* book, char* element, int num)
{
    switch (num)
    {
    case 0:
        book->title = element;
        break;
    case 1:
        book->author = element;
        break;
    case 2:
        book->genre = element;
        break;
    case 3:
        book->isbn = strtol(element, NULL, 10);
        break;
    case 4:
        book->ubication = strtol(element, NULL, 16);
        break;
    case 5:
        SetBookState(book, element);
        break;
    
    default:
    push(book->reservations, element);
        break;
    }
}

void SetBookState(Book* book, const char* str)
{
    if (strcmp(str, "Disponible") == 0)
        book->state = Available;
    else if (strcmp(str, "Reservado") == 0)
        book->state = Reserved;
    else if (strcmp(str, "Prestado") == 0)
        book->state = Taken;
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

Book* CreateBook()
{
    Book* book = malloc(sizeof(Book));

    book->title = NULL;
    book->author = NULL;
    book->genre = NULL;
    book->isbn = -1;
    book->ubication = -1;
    book->state = Available;
    book->reservations = createQueue();

    return book;
}

void PrintToFileBook(Book* book, FILE* file)
{
    fprintf(file, "%s,%s,%s,%i,%x,", book->title, book->author, book->genre, book->isbn, book->ubication);

    switch (book->state)
    {
    case Available:
        fprintf(file, "Disponible,");
        break;

    case Taken:
        fprintf(file, "Prestado,");
        break;

    case Reserved:
        fprintf(file, "Reservado,");
        break;
    }

    queueNode* current = book->reservations->front;
    while (current != NULL)
    {
        fprintf(file, "%s", current->data);
        current = current->next;
        if (current != NULL)
            fprintf(file, ",");
    }

    fprintf(file, "\n");
}

void PrintBook(Book* book)
{
    printf("%s,  %s,  %s,  %i,  %x, ", book->title, book->author, book->genre, book->isbn, book->ubication);
    PrintState(book);
    printf(", ");
    PrintReservations(book);
    printf("\n");
}

void PrintState(Book* book)
{
    switch (book->state)
    {
    case Available:
        printf("Disponible");
        break;

    case Taken:
        printf("Prestado");
        break;

    case Reserved:
        printf("Reservado");
        break;
    }
}

void PrintReservations(Book* book)
{
    queueNode* current = book->reservations->front;
    while (current != NULL)
    {
        printf("%s, ", current->data);
        current = current->next;
    }
}