#ifndef CSV_H
#define CSV_H

#include "list.h"

void CsvToList(List* L, const char* filename);
void ListToCsv(List* L, const char* filename);

#endif