
#pragma once

#include "ArrayList.h"
#include "../include/FrequencyTable.h"

typedef struct MinHeap {
    ArrayList* arrayList;
    int (*cmp)(E*, E*);
} MinHeap;

size_t parent(size_t i);
size_t left(size_t i);
size_t right(size_t i);

void heapify_up(MinHeap *minHeap, size_t index);
void heapify_down(MinHeap *minHeap, size_t index);

size_t MinHeap_size(MinHeap* minHeap);

E* MinHeap_get(MinHeap* minHeap, size_t index);
void MinHeap_set(MinHeap* minHeap, size_t index, E* e);

void MinHeap_push(MinHeap *minHeap, E* e);
E* MinHeap_pop(MinHeap *minHeap);
E* MinHeap_peek(MinHeap *minHeap);

MinHeap* MinHeap_create();
void MinHeap_destroy(MinHeap *minHeap);

MinHeap* MinHeap_fromFrequencyTable(FrequencyTable* frequencyTable);
