#include "app.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "book.h"
#include "list.h"
#include "util.h"

#define NO_BOOK(x) if (x == NULL){ printf("[error] No existe libro que cumpla los parametros.\n"); return; }

const int maxTokenSize = 50;
const int maxTokens = 6;

// Uso interno
char* GetFile(const char* filename);
bool KeyWord(const char* command, const char* option1, int option2);
bool ErrorParametros(int count, int num);

void App(List* L, bool* end)
{
    // Guarda memoria para la STR principal
    char* str = calloc(maxTokenSize * maxTokens + 1, sizeof(char));
    if (scanf("%[^\n]", str) != 1)
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

    bool spaceAllowed = true;
    bool longToken = false;

    // Separa la STR principal en, maximo 6 tokens que
    // seran lo parametos de cada funcion de la interfaz
    for(int i = 0; i < size + 1; i++)
    {
        char c = str[i];

        if (c == '\"')
        {
            spaceAllowed = !spaceAllowed;

            if (spaceAllowed)
                longToken = true;
        }

        if (!(c == ' ' && spaceAllowed) && c != '\n')
            continue;

        size_t strsize = i - lastpos;
        if (longToken)
        {
            char* token = calloc(maxTokenSize - 1, sizeof(char));
            for (size_t j = 0; j < strsize - 2; j++)
                token[j] = str[j + lastpos + 1];
    
            longToken = false;
            tokens[tokenCount] = token;
        }
        else
        {
            char* token = calloc(maxTokenSize + 1, sizeof(char));
            for (size_t j = 0; j < strsize; j++)
                token[j] = str[j + lastpos];
                
            tokens[tokenCount] = token;
        }

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


    //
    //  Ejecuta una función asosciada a una comando
    //  tambien tienen que coinsidir en la cantidad de parametros
    //
    if (KeyWord(tokens[0], "registrar_libro", 1))
    {
        if(tokenCount == 2)
            RegisterBook1(L, tokens[1]);
        else if(tokenCount == 6)
            RegisterBook2(L, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
        else
            printf("[error] Muy pocos argumentos.\n");
    }
    else if (KeyWord(tokens[0], "mostrar_datos_libro", 2))
    {
        if(ErrorParametros(tokenCount, 3))
            return;

        ShowBookData(L, tokens[1], tokens[2]);
    }
    else if (KeyWord(tokens[0], "mostar_todos_los_libros", 3))
    {
        if(ErrorParametros(tokenCount, 1))
            return;

        ShowAllBooks(L);
    }
    else if(KeyWord(tokens[0], "reservar_libro", 4))
    {
        if(ErrorParametros(tokenCount, 4))
            return;

        ReserveBook(L, tokens[1], tokens[2], tokens[3]);
    }
    else if(KeyWord(tokens[0], "cancelar_reserva", 5))
    {
        if(ErrorParametros(tokenCount, 4))
            return;

        CancelReservation(L, tokens[1], tokens[2], tokens[3]);
    }
    else if(KeyWord(tokens[0], "retirar_libro", 6))
    {
        if(ErrorParametros(tokenCount, 4))
            return;

        TakeBook(L, tokens[1], tokens[2], tokens[3]);
    }
    else if(KeyWord(tokens[0], "devolver_libro", 7))
    {
        if(ErrorParametros(tokenCount, 3))
            return;

        TakeBackBook(L, tokens[1], tokens[2]);
    }
    else if(KeyWord(tokens[0], "mostrar_prestados", 8))
    {
        if(ErrorParametros(tokenCount, 1))
            return;

        ShowTakenBooks(L);
    }
    else if(KeyWord(tokens[0], "importar_csv", 9))
    {
        if(ErrorParametros(tokenCount, 2))
            return;

        ImportfromCsv(L, tokens[1]);
    }
    else if(KeyWord(tokens[0], "exportar_csv", 10))
    {
        if(ErrorParametros(tokenCount, 2))
            return;

        ExportToCsv(L, tokens[1]);
    }
    else if(KeyWord(tokens[0], "salir", 0))
    {
        if(ErrorParametros(tokenCount, 1))
            return;

        *end = true;
    }
    else
    {
        printf("[error] Comando desconocido: \"%s\".\n", tokens[0]);
    }

    for (int i = 0; i < tokenCount; i++)
        free(tokens[i]);

    free(str);
}

// Añade un libro a la lista
void RegisterBook1(List* L, char* str)
{
    Book* book = StrToBook(str);
    pushBack(L, book);

    printf("Libro %s registrado.", book->author);
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
    printf("Libro %s registrado.", book->author);
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

    if (L->current == NULL)
        printf("[error] No hay libros.\n");

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

    List* list = QueueToList(book->reservations);

    char* data = firstList(L);
    while (L->current != NULL)
    {
        if (strcmp(data, name) == 0)
        {
            popCurrent(list);

            printf("Reserva cancelada\n")

            book->reservations = ListToQueue(list);
            free(list);
            return;
        }

        data = nextList(L);
    }

    printf("[error]: %s no tiene reservado %s.", name, title);

    book->reservations = ListToQueue(list);
    free(list);
}

// Cambia el estado de un libro a prestado, si el estudiante esta
// primero en la cola de reservas o esta disponible, y lo elimina de la cola
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

// Cambia el estado de un libro prestado a disponible
// si es que no hay un cola de reservas, en tal caso cambia a reservado
void TakeBackBook(List* L, char* title, char* author)
{
    Book* book = CheckForBook(L, title, author);
    NO_BOOK(book);

    if (book->state != Taken)
    {
        printf("[error] El libro no esta tomado\n");
        return
    }

    if(book->reservations->front == NULL)
        book->state = Available;
    else
        book->state = Reserved;

    printf("Libro devuelto\n");
}

// Muestra por consola todos los libros prestados
void ShowTakenBooks(List* L)
{
    Book* book = firstList(L);
    while (L->current != NULL)
    {
        if (book->state == Taken)
        {
            PrintBook(book);
        }
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

    printf("Archivo exportado\n");

    fclose(file);
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

    printf("Archivo importado\n");

    free(file);
}

void* CreateLibrary(const char* filename)
{
    List* library = createList();
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

bool ErrorParametros(int count, int num)
{
    if(count > num)
        printf("[error] Demasiados argumentos.\n");
    else if(count < num)
        printf("[error] Muy pocos argumentos.\n");
    else
        return false;

    return true;
}