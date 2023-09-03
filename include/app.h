#ifndef APP_H
#define APP_H

#include <stdbool.h>

#include "list.h"

void App(List* L, bool* end);

void RegisterBook1(List* L, char* str);
void RegisterBook2(List* L, char* title, char* author, char* genre, char* isbn, char* ubication);
void ShowBookData(List* L, char* title, char* author);
void ShowAllBooks(List* L);
void ReserveBook(List* L, char* title, char* author, char* name);
void CancelReservation(List* L, char* title, char* author, char* name);
void TakeBook(List* L, char* title, char* author, char* name);
void TakeBackBook(List* L, char* title, char* author, char* name);
void ShowTakenBooks(List* L);
void ImportfromCsv(List* L, const char* filename);;
void ExportToCsv(List* L, const char* filename);

void* CreateLibrary(const char* filename);
void ClearAll(List* L);

#endif // APP_H