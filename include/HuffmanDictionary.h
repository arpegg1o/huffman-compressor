
#pragma once

#include "../include/HuffmanTree.h"
#include "../include/HuffmanCode.h"

typedef struct HuffmanDictionary {
    HuffmanCode** arr;
} HuffmanDictionary;

HuffmanDictionary* HuffmanDictionary_create();
HuffmanDictionary* HuffmanDictionary_fromHuffmanTree(HuffmanTree* huffmanTree);
void HuffmanDictionary_destroy(HuffmanDictionary* huffmanDictionary);

void HuffmanDictionary_fromHuffmanTreeHelper(HuffmanDictionary* huffmanDictionary, HuffmanNode* root, HuffmanCode* huffmanCode);

void HuffmanDictionary_add(HuffmanDictionary* huffmanDictionary, size_t index, HuffmanCode* huffmanCode);

HuffmanCode* HuffmanDictionary_get(HuffmanDictionary* huffmanDictionary, size_t index);
