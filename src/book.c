#include "book.h"

#include <stdlib.h>
#include <string.h>

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

    // Recore toda la str hasta encontar un ',' o '\n'
    // en tal caso lo separa en un nueva str y lo añade
    // como elemento de un libro
    for(size_t i = 0; i < size; i++)
    {
        char c = str[i];
        size_t strsize = i - lastpos - 1;

        if(c != ',' && c != '\n')
            continue;

        // Revisa que ningun elemento
        // no tenga más de 50 caracteres
        if(strsize > 50)
        {
            printf("ERROR: str con más de 50 caracteres; se ignorara el libro\n");
            FreeBook(book);
            return NULL;
        }

        // crea la str que representa el elemento y lo puebla
        char* element = calloc(51, sizeof(char));
        for (size_t j = 0; j < strsize + 1; j++)
        {
            element[j] = str[j + lastpos];
        }

        // Añade el elmento al libro
        AddElementToBook(book, element, elementCount);

        lastpos = i + 1;
        elementCount++;
    }

    if (elementCount <= 5)
    {
        printf("ERROR: Datos insufiecientes para un Libro\n");
        FreeBook(book);
        return NULL;
    }

    return book;
}

void AddElementToBook(Book* book, char* element, int num)
{
    if (num < 3)
    {
        char** strList[3] = {&book->title, &book->author, &book->genre};
        *strList[num] = element;
        return;
    }

    if(num >= 3 && num <= 5)
    {
        long* intList[3] = {&book->isbn, (long*)&book->ubication, (long*)&book->state};
        const int baseList[3] = {10, 16, 10};

        *intList[num - 3] = strtol(element, NULL, baseList[num - 3]);
        free(element);
        return;
    }

    push(book->reservations, element);
}

// Pone el estado de un libro
void SetBookState(Book* book, const char* str)
{
    if (strcmp(str, "Disponible") == 0)
        book->state = Available;
    if (strcmp(str, "Reservado") == 0)
        book->state = Reserved;
    if (strcmp(str, "Prestado") == 0)
        book->state = Taken;
}

// Libera la memoria de las STR que contiene el libro
void FreeBook(Book* book)
{
    char** strList[3] = {&book->title, &book->author, &book->genre};
    for (int i = 0; i < 3; i++)
    {
        if(*strList[i] != NULL)
            free(*strList[i]);
    }

    if (book != NULL)
        free(book);
}

// Crea un libro
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

// Practicamente una copia de PrintBook()
// con cambios para adaptarse al formato csv.
void PrintToFileBook(Book* book, FILE* file)
{
    fprintf(file, "%s,%s,%s,%i,%x,", book->title, book->author, book->genre, book->isbn, book->ubication);

    PrintToStreamState(book, file);
    fprintf(file, ",");

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
    PrintToStreamState(book, stdout);
    PrintReservations(book);
    printf("\n");
}

// Imprie en un archivo o en consola el estado de un libro
void PrintToStreamState(Book* book, FILE* stream)
{
    switch (book->state)
    {
    case Available:
        fprintf(stream, "Disponible");
        break;
    case Taken:
        fprintf(stream, "Prestado");
        break;
    case Reserved:
        fprintf(stream, "Reservado");
        break;
    }
}

// Revisa si existe un libro en un lista si y lo devuelve, si no retorna NULL
Book* CheckForBook(List* L, char* title, char* author)
{
    Book* book = firstList(L);
    
    while (L->current != NULL)
    {
        if (strcmp(book->title, title) == 0 && strcmp(book->author, author) == 0)
            return book;

        book = nextList(L);
    }

    return NULL;
}

// Imprime las reservas de un libro
void PrintReservations(Book* book)
{   
    // Recorre la queue de las reservas
    queueNode* current = book->reservations->front;
    while (current != NULL)
    {
        printf(", %s", current->data);
        current = current->next;
    }
}