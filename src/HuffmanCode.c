
#include "../include/HuffmanCode.h"

HuffmanCode* HuffmanCode_create() {
    HuffmanCode* huffmanCode = (HuffmanCode*)malloc(sizeof(HuffmanCode));
    if (huffmanCode == NULL) {
        return NULL;
    }

    huffmanCode->bits = (uint8_t*)malloc(32 * sizeof(uint8_t));
    if (huffmanCode->bits == NULL) {
        HuffmanCode_destroy(huffmanCode);
        return NULL;
    }
    for (size_t i = 0; i < 32; i++) {
        huffmanCode->bits[i] = 0;
    }

    huffmanCode->length = 0;

    return huffmanCode;
}

void HuffmanCode_destroy(HuffmanCode* huffmanCode) {
    if (huffmanCode != NULL) {
        free(huffmanCode->bits);
    }

    free(huffmanCode);
}

size_t HuffmanCode_length(HuffmanCode* huffmanCode) {
    return huffmanCode->length;
}

void HuffmanCode_add(HuffmanCode* huffmanCode, unsigned int bit) {
    if (HuffmanCode_length(huffmanCode) == 256) {
        return;
    }

    huffmanCode->bits[huffmanCode->length / 8] |= (bit << (huffmanCode->length % 8));
    huffmanCode->length++;

}

unsigned int HuffmanCode_get(HuffmanCode* huffmanCode, size_t index) {
    if (index < 0 || index >= huffmanCode->length) {
        return 0;
    }

    return (huffmanCode->bits[index / 8] >> (index % 8)) & 1;
}

HuffmanCode* HuffmanCode_clone(HuffmanCode* huffmanCode) {
    HuffmanCode* clone = HuffmanCode_create();
    for (int i = 0; i < huffmanCode->length; i++) {
        HuffmanCode_add(clone, HuffmanCode_get(huffmanCode, i));
    }

    return clone;
}
