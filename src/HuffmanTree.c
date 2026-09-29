
#include "../include/HuffmanTree.h"

HuffmanTree* HuffmanTree_create() {
    HuffmanTree* huffmanTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    if (huffmanTree == NULL) {
        return NULL;
    }

    huffmanTree->root = NULL;
    return huffmanTree;
}

HuffmanTree* HuffmanTree_fromHuffmanNode(HuffmanNode* root) {
    HuffmanTree* huffmanTree = HuffmanTree_create();
    if (huffmanTree == NULL) {
        return NULL;
    }

    huffmanTree->root = root;
    return huffmanTree;
}

HuffmanTree* HuffmanTree_fromMinHeap(MinHeap* minHeap) {
    HuffmanNode* left_node;
    HuffmanNode* right_node;

    while (MinHeap_size(minHeap) > 1) {
        left_node = MinHeap_pop(minHeap);
        right_node = MinHeap_pop(minHeap);

        unsigned int left_frequency = HuffmanNode_frequency(left_node);
        unsigned int right_frequency = HuffmanNode_frequency(right_node);

        HuffmanNode* parent_node = HuffmanNode_create('\0', left_frequency + right_frequency);
        if (parent_node == NULL) {
            return NULL;
        }

        parent_node->left = left_node;
        parent_node->right = right_node;

        MinHeap_push(minHeap, parent_node);
    }

    HuffmanNode* root = MinHeap_pop(minHeap);
    HuffmanTree* huffmanTree = HuffmanTree_fromHuffmanNode(root);
    if (huffmanTree == NULL) {
        return NULL;
    }

    return huffmanTree;
}

void HuffmanTree_destroy(HuffmanTree* huffmanTree) {
    if (huffmanTree->root == NULL) {
        return;
    }

    HuffmanNode_destroyAll(huffmanTree->root);
    free(huffmanTree);
}

HuffmanNode* HuffmanTree_root(HuffmanTree* huffmanTree) {
    return huffmanTree->root;
}
