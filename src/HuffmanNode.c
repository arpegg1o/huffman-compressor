
#include "../include/HuffmanNode.h"

HuffmanNode* HuffmanNode_create(char data, unsigned int frequency) {
    HuffmanNode* huffmanNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    if (huffmanNode == NULL) {
        return NULL;
    }

    huffmanNode->data = data;
    huffmanNode->frequency = frequency;
    huffmanNode->left = NULL;
    huffmanNode->right = NULL;

    return huffmanNode;
}

 void HuffmanNode_destroy(HuffmanNode* huffmanNode) {
    free(huffmanNode);
}

void HuffmanNode_destroyAll(HuffmanNode* root) {
    if (root == NULL) {
        return;
    }

    HuffmanNode_destroyAll(root->left);
    HuffmanNode_destroyAll(root->right);
    free(root);
}

char HuffmanNode_data(HuffmanNode* huffmanNode) {
    return huffmanNode->data;
}
unsigned int HuffmanNode_frequency(HuffmanNode* huffmanNode) {
    return huffmanNode->frequency;
}

int HuffmanNode_cmp(HuffmanNode* a, HuffmanNode* b) {
    return (a->frequency > b->frequency) - (a->frequency < b->frequency);
}
