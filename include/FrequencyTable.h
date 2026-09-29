
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 4096

typedef struct FrequencyTable {
    unsigned int* arr;
} FrequencyTable;


unsigned int FrequencyTable_get(FrequencyTable* frequencyTable, size_t index);
unsigned int* FrequencyTable_getArr(FrequencyTable* frequencyTable);
FrequencyTable* FrequencyTable_create();
FrequencyTable* FrequencyTable_fromFile(FILE* file);
FrequencyTable* FrequencyTable_fromHeader(FILE* file);
void FrequencyTable_destroy(FrequencyTable* frequencyTable);
