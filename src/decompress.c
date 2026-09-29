
#include <stdio.h>
#include "../include/HuffmanTree.h"

int main(int argc, char *argv[]) {
    FILE* input = fopen("data/output.bin", "rb");
    if (input == NULL) {
        exit(EXIT_FAILURE);
    }

    FrequencyTable* frequencyTable = FrequencyTable_fromHeader(input);
    if (frequencyTable == NULL) {
        fclose(input);
        exit(EXIT_FAILURE);
    }

    long fileSize;
    fread(&fileSize, sizeof(long), 1, input);

    MinHeap* minHeap = MinHeap_fromFrequencyTable(frequencyTable);
    if (minHeap == NULL) {
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    HuffmanTree* huffmanTree = HuffmanTree_fromMinHeap(minHeap);
    if (huffmanTree == NULL) {
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen("data/output.txt", "wb");
    if (output == NULL) {
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    unsigned char* buffer = (unsigned char*)malloc(CHUNK_SIZE * sizeof(char));
    if (buffer == NULL) {
        fclose(output);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    HuffmanNode* root = HuffmanTree_root(huffmanTree);
    HuffmanNode* huffmanNode = root;

    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(unsigned char), CHUNK_SIZE, input)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            for (int j = 0; j < 8; j++) {
                if (huffmanNode->left == NULL && huffmanNode->right == NULL) {
                    size_t elementsWritten = fwrite(&huffmanNode->data, sizeof(unsigned char), 1, output);
                    if (elementsWritten != 1) {
                        free(buffer);
                        fclose(output);
                        HuffmanTree_destroy(huffmanTree);
                        MinHeap_destroy(minHeap);
                        FrequencyTable_destroy(frequencyTable);
                        fclose(input);
                        exit(EXIT_FAILURE);
                    }

                    fileSize--;
                    if (fileSize == 0) {
                        free(buffer);
                        fclose(output);
                        HuffmanTree_destroy(huffmanTree);
                        MinHeap_destroy(minHeap);
                        FrequencyTable_destroy(frequencyTable);
                        fclose(input);
                        exit(EXIT_SUCCESS);
                    }

                    huffmanNode = root;
                }

                if ((buffer[i] & (1 << j))) {
                    huffmanNode = huffmanNode->right;
                } else {
                    huffmanNode = huffmanNode->left;
                }
            }
        }
    }

    free(buffer);
    fclose(output);
    HuffmanTree_destroy(huffmanTree);
    MinHeap_destroy(minHeap);
    FrequencyTable_destroy(frequencyTable);
    fclose(input);
    exit(EXIT_FAILURE);
}
