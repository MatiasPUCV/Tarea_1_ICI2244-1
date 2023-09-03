#ifndef APP_H
#define APP_H

#include "list.h"

void RegisterBook(List* L, char* str);
void ShowBookData(List* L, char* title, char* author);
void ShowAllBooks(List* L);
void ReserveBook(List* L, char* title, char* author, char* name);
void CancelReservation(List* L, char* title, char* author, char* name);
void TakeBook(List* L, char* title, char* author, char* name);
void ShowTakenBooks(List* L);
void ExportToCsv(List* L, const char* filename);

void* CreateLibrabry(const char* filename);
void ClearAll(List* L);

#endif // APP_H