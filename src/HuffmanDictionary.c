
#include "../include/HuffmanDictionary.h"


HuffmanDictionary* HuffmanDictionary_create() {
    HuffmanDictionary* huffmanDictionary = (HuffmanDictionary*)malloc(sizeof(HuffmanDictionary));
    if (huffmanDictionary == NULL) {
        return NULL;
    }

    huffmanDictionary->arr = malloc(256 * sizeof(HuffmanCode*));
    if (huffmanDictionary->arr == NULL) {
        HuffmanDictionary_destroy(huffmanDictionary);
    }

    for (int i = 0; i < 256; i++) {
        huffmanDictionary->arr[i] = HuffmanCode_create();
        if (huffmanDictionary->arr[i] == NULL) {
            HuffmanDictionary_destroy(huffmanDictionary);
            return NULL;
        }
    }

    return huffmanDictionary;
}

HuffmanDictionary* HuffmanDictionary_fromHuffmanTree(HuffmanTree* huffmanTree) {
    if (huffmanTree == NULL) {
        return NULL;
    }

   HuffmanDictionary* huffmanDictionary = HuffmanDictionary_create();
   if (huffmanDictionary == NULL) {
       return NULL;
   }

   HuffmanCode* huffmanCode = HuffmanCode_create();
   HuffmanDictionary_fromHuffmanTreeHelper(huffmanDictionary, huffmanTree->root, huffmanCode);

   return huffmanDictionary;
}

void HuffmanDictionary_fromHuffmanTreeHelper(HuffmanDictionary* huffmanDictionary, HuffmanNode* root, HuffmanCode* huffmanCode) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        HuffmanDictionary_add(huffmanDictionary, root->data, huffmanCode);
        return;
    }

    HuffmanCode* leftHuffmanCode = HuffmanCode_clone(huffmanCode);
    HuffmanCode* rightHuffmanCode = HuffmanCode_clone(huffmanCode);

    HuffmanCode_destroy(huffmanCode);

    HuffmanCode_add(leftHuffmanCode, 0);
    HuffmanCode_add(rightHuffmanCode, 1);

    HuffmanDictionary_fromHuffmanTreeHelper(huffmanDictionary, root->left, leftHuffmanCode);
    HuffmanDictionary_fromHuffmanTreeHelper(huffmanDictionary, root->right, rightHuffmanCode);

}

void HuffmanDictionary_destroy(HuffmanDictionary* huffmanDictionary) {
    if (huffmanDictionary != NULL) {
        for (int i = 0; i < 256; i++) {
            HuffmanCode_destroy(HuffmanDictionary_get(huffmanDictionary, i));
        }
    }

    free(huffmanDictionary);
}

void HuffmanDictionary_add(HuffmanDictionary* huffmanDictionary, size_t index, HuffmanCode* huffmanCode) {
    if (index < 0 || index >= 256) {
        return;
    }

    huffmanDictionary->arr[index] = huffmanCode;
}

HuffmanCode* HuffmanDictionary_get(HuffmanDictionary* huffmanDictionary, size_t index) {
    if (index < 0 || index >= 256) {
        return NULL;
    }

    return huffmanDictionary->arr[index];
}
