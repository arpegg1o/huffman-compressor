
#pragma once

#include "MinHeap.h"

typedef struct HuffmanTree {
    HuffmanNode* root;
} HuffmanTree;

HuffmanTree* HuffmanTree_create();
HuffmanTree* HuffmanTree_fromHuffmanNode(HuffmanNode* root);
HuffmanTree* HuffmanTree_fromMinHeap(MinHeap* minHeap);
void HuffmanTree_destroy(HuffmanTree* huffmanTree);

HuffmanNode* HuffmanTree_root(HuffmanTree* huffmanTree);
