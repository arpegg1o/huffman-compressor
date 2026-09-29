
#include "../include/FrequencyTable.h"

unsigned int FrequencyTable_get(FrequencyTable* frequencyTable, size_t index) {
    if (index < 0 || index > 256) {
        return 0;
    }

    return frequencyTable->arr[index];
}

unsigned int* FrequencyTable_getArr(FrequencyTable* frequencyTable) {
    return frequencyTable->arr;
}

FrequencyTable* FrequencyTable_create() {
    FrequencyTable* frequencyTable = (FrequencyTable*)malloc(sizeof(FrequencyTable));
    if (frequencyTable == NULL) {
        return NULL;
    }

    frequencyTable->arr = (unsigned int*)malloc(256 * sizeof(int));
    if (frequencyTable->arr == NULL) {
        FrequencyTable_destroy(frequencyTable);
        return NULL;
    }

    for (int i = 0; i < 256; i++) {
        frequencyTable->arr[i] = 0;
    }

    return frequencyTable;
}

FrequencyTable* FrequencyTable_fromFile(FILE* file) {
    FrequencyTable* frequencyTable = FrequencyTable_create();

    unsigned char* buffer = (unsigned char*)malloc(CHUNK_SIZE * sizeof(char));
    if (buffer == NULL) {
        FrequencyTable_destroy(frequencyTable);
        return NULL;
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            frequencyTable->arr[buffer[i]]++;
        }
    }

    free(buffer);
    return frequencyTable;
}

FrequencyTable* FrequencyTable_fromHeader(FILE* file) {
    FrequencyTable* frequencyTable = FrequencyTable_create();

    unsigned int* buffer = (unsigned int*)malloc(256 * sizeof(unsigned int));
    if (buffer == NULL) {
        FrequencyTable_destroy(frequencyTable);
        return NULL;
    }

    size_t elementsRead;
    elementsRead = fread(buffer, sizeof(unsigned int), 256, file);
    if (elementsRead != 256) {
        free(buffer);
        FrequencyTable_destroy(frequencyTable);
        return NULL;
    }

    for (int i = 0; i < 256; i++) {
        frequencyTable->arr[i] = buffer[i];
    }

    free(buffer);
    return frequencyTable;
}

void FrequencyTable_destroy(FrequencyTable* frequencyTable) {
    if (frequencyTable != NULL) {
        free(frequencyTable->arr);
    }

    free(frequencyTable);
}
