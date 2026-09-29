
#pragma once

#include <stdlib.h>

typedef struct HuffmanCode {
    uint8_t *bits;
    size_t length;
} HuffmanCode;

HuffmanCode* HuffmanCode_create();

void HuffmanCode_destroy(HuffmanCode* huffmanCode);

size_t HuffmanCode_length(HuffmanCode* huffmanCode);

void HuffmanCode_add(HuffmanCode* huffmanCode, unsigned int bit);

unsigned int HuffmanCode_get(HuffmanCode* huffmanCode, size_t index);

HuffmanCode* HuffmanCode_clone(HuffmanCode* huffmanCode);
