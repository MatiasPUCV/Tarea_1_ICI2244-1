#ifndef APP_H
#define APP_H

#include "list.h"

void RegisterBook(List* L, char* str);
void ShowBookData(List* L, char* title, char* author);
void ShowAllBooks(List* L);

void ClearAll(List* L);

#endif // APP_H