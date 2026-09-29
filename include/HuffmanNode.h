
#pragma once

#include <stdlib.h>

typedef struct HuffmanNode {
    char data;
    unsigned int frequency;

    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

HuffmanNode* HuffmanNode_create(char data, unsigned int frequency);
void HuffmanNode_destroy(HuffmanNode* huffmanNode);

void HuffmanNode_destroyAll(HuffmanNode* root);

char HuffmanNode_data(HuffmanNode* huffmanNode);
unsigned int HuffmanNode_frequency(HuffmanNode* huffmanNode);

int HuffmanNode_cmp(HuffmanNode* a, HuffmanNode* b);
