#include "app.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "book.h"
#include "list.h"

#define NO_BOOK(x) if (x == NULL){ printf("[error] No existe libro que cumpla los parametros.\n"); return; }

const int maxTokenSize = 50;
const int maxTokens = 6;

// Uso interno
char* GetFile(const char* filename);
bool KeyWord(const char* command, const char* option1, int option2);

void App(List* L, bool* end)
{
    // Guarda memoria para la STR principal
    char* str = calloc(maxTokenSize * maxTokens + 1, sizeof(char));
    if (scanf(" %[^\n]", str) != 1)
    {
        free(str);
        *end = false;
        return;
    }

    size_t size = strlen(str);
    str[size] = ' ';

    // Limpia el buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char* tokens[6];
    size_t lastpos = 0;
    int tokenCount = 0;

    // Separa la STR principal en, maximo 6 tokens que
    // seran lo parametos de cada funcion de la interfaz
    for(int i = 0; i < size + 1; i++)
    {
        char c = str[i];

        if (c != ' ' && c != '\n')
            continue;

        size_t strsize = i - lastpos;

        char* token = calloc(maxTokenSize + 1, sizeof(char));
        for (size_t j = 0; j < strsize; j++)
        {
            token[j] = str[j + lastpos];
        }

        tokens[tokenCount] = token;

        lastpos = i + 1;
        tokenCount++;
    }
    
/*
    Cada función de la interfaz tiene asociado
    una palabra y un numero (en pos de la comodidad), si en tokens[0]
    esta cualqueira de los dos es función sera
    la que se ejecutara. Las funciones tomaran como
    parametros el resto de tokens.
    
    (Solo RegisterBook2() toma 5, el resto no toman más de 3).

*/

    if (KeyWord(tokens[0], "registrar_libro", 1))
    {
        if(tokenCount == 2)
            RegisterBook1(L, tokens[1]);

        if(tokenCount == 6)
            RegisterBook2(L, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
    }

    if (KeyWord(tokens[0], "mostrar_datos_libro", 2))
    {

        ShowBookData(L, tokens[1], tokens[2]);
    }

    if (KeyWord(tokens[0], "mostar_todos_los_libros", 3))
         ShowAllBooks(L);


    if(KeyWord(tokens[0], "reservar_libro", 4))
    {

        ReserveBook(L, tokens[1], tokens[2], tokens[3]);
    }

    if(KeyWord(tokens[0], "cancelar_reserva", 5))
    {
        CancelReservation(L, tokens[1], tokens[2], tokens[3]);

    }

    if(KeyWord(tokens[0], "retirar_libro", 6))
    {
        TakeBook(L, tokens[1], tokens[2], tokens[3]);

    }

    if(KeyWord(tokens[0], "devolver_libro", 7))
    {
        TakeBackBook(L, tokens[1], tokens[2], tokens[3]);

    }

    if(KeyWord(tokens[0], "mostrar_prestados", 8))
        ShowTakenBooks(L);



    if(KeyWord(tokens[0], "importar_csv", 9))
    {
        ImportfromCsv(L, tokens[1]);

    }

    if(KeyWord(tokens[0], "exportar_csv", 10))
    {
        ExportToCsv(L, tokens[1]);

    }

    if(KeyWord(tokens[0], "salir", 0))
        *end = true;

    for (int i = 0; i < tokenCount; i++)
        free(tokens[i]);

    free(str);
}

// Añade un libro a la lista
void RegisterBook1(List* L, char* str)
{
    Book* book = StrToBook(str);
    pushBack(L, book);
}

void RegisterBook2(List* L, char* title, char* author, char* genre, char* isbn, char* ubication)
{
    char** strList[5] = {&title, &author, &genre, &isbn, &ubication};
    for (int i = 0; i < 5; i++)
    {
        if(strlen(*strList[i]) > 50)
            printf("[Error] STR con más de 50 caracteres; se ignorara el libro\n");

    }

    Book* book = CreateBook();

    book->title = title;
    book->author = author;
    book->genre = genre;
    book->isbn = strtol(isbn, NULL, 10);
    book->ubication = strtol(isbn, NULL, 16);

    pushBack(L, book);
}

void ShowBookData(List* L, char* title, char* author)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    PrintBook(book);
}

// Muestra por pantalla todos los libros
void ShowAllBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        PrintBook(book);
        book = nextList(L);
    }
}

void ReserveBook(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    push(book->reservations, name);
    printf("%s. Reservado.", title);
}

void CancelReservation(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    queueNode* current = book->reservations->front;
    while (current != NULL)
    {
        if(strcmp(current->data, name) == 0)
        {
            // TODO: terminar
        }

        current = current->next;
    }
}

void TakeBook(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    if((strcmp(top(book->reservations), name) == 0 && book->state == Reserved) || book->state == Available)
    {
        book->state = Taken;
        printf("Libro Prestado\n");
        if (book->state == Reserved)
            pop(book->reservations);
    }
    else
    {
        printf("[error] Usted no puede retirar el libro.\n");
    }
}

void TakeBackBook(List* L, char* title, char* author, char* name)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    if (book->state != Taken)
        printf("[error] El libro no esta tomado\n");

    if(book->reservations->front == NULL)
        book->state = Available;
    else
        book->state = Reserved;
}

void ShowTakenBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        if(book->state == Taken)
            PrintBook(book);
        book = nextList(L);
    }
}

// Exporta una lista como CSV
void ExportToCsv(List* L, const char* filename)
{
    // Crea el archivo
    FILE* file = fopen(filename, "w");
    if (file == NULL)
        printf("[error] el archivo no existe\n");

    // Pasa los datos de la lista
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        PrintBookToFile(book, file);
        book = nextList(L);
    } 

    fclose(file);
}

void* CreateLibrary(const char* filename)
{
    List* library = createList();
    ImportfromCsv(library, filename);

    return library;
}

// Libera toda la memoria de la lista
void ClearAll(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        FreeBook(book);
        book = nextList(L);
    }
    
    cleanList(L);
    free(L);
}

// Convierte un archivo csv a una lista
void ImportfromCsv(List* L, const char* filename)
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
            // Ignora la primera fila del archivo
            first = false;
        }

        free(str);
        lastpos = i + 1;
    }
    free(file);
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

bool KeyWord(const char* command, const char* option1, int option2)
{
    char numStr[3];
    return (strcmp(command, option1) == 0 || strcmp(command, itoa(option2, numStr, 10)) == 0);
}