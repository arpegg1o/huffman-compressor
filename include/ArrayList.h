
#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "HuffmanNode.h"

typedef HuffmanNode E;

#define RESIZE_FACTOR 2
#define STRATING_CAPACITY 1

typedef struct ArrayList {
    size_t size;
    size_t capacity;

    E** arr;
} ArrayList;

size_t ArrayList_size(ArrayList *array_list);

void ArrayList_add(ArrayList* array_list, E* e);
void ArrayList_remove(ArrayList* array_list);

E* ArrayList_get(ArrayList* array_list, size_t index);
void ArrayList_set(ArrayList* array_list, size_t index, E* e);


ArrayList* ArrayList_create();
void ArrayList_destroy(ArrayList* array_list);
