
#include "../include/HuffmanDictionary.h"

long FILE_size(FILE *file) {
    long currentPos = ftell(file);

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fseek(file, currentPos, SEEK_SET);

    return size;
}

int main(int argc, char* argv[]) {
    FILE* input = fopen("data/big.txt", "rb");
    if (input == NULL) {
        exit(EXIT_FAILURE);
    }

    FrequencyTable* frequencyTable = FrequencyTable_fromFile(input);
    if (frequencyTable == NULL) {
        fclose(input);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 256; i++) {
        printf("%c: %d\n", i, FrequencyTable_get(frequencyTable, i));
    }

    MinHeap* minHeap = MinHeap_fromFrequencyTable(frequencyTable);
    if (minHeap == NULL) {
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    HuffmanTree* huffmanTree = HuffmanTree_fromMinHeap(minHeap);
    if (huffmanTree == NULL) {
        FrequencyTable_destroy(frequencyTable);
        MinHeap_destroy(minHeap);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    HuffmanDictionary* huffmanDictionary = HuffmanDictionary_fromHuffmanTree(huffmanTree);
    if (huffmanDictionary == NULL) {
        FrequencyTable_destroy(frequencyTable);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen("data/output.bin", "wb");
    if (output == NULL) {
        FrequencyTable_destroy(frequencyTable);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        HuffmanDictionary_destroy(huffmanDictionary);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    size_t elementsWritten = fwrite(FrequencyTable_getArr(frequencyTable), sizeof(unsigned int), 256, output);
    if (elementsWritten != 256) {
        fclose(output);
        HuffmanDictionary_destroy(huffmanDictionary);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    long size = FILE_size(input);
    elementsWritten = fwrite(&size, sizeof(long), 1, output);
    if (elementsWritten != 1) {
        fclose(output);
        HuffmanDictionary_destroy(huffmanDictionary);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    rewind(input);
    unsigned char* buffer = (unsigned char*)malloc(CHUNK_SIZE * sizeof(char));
    if (buffer == NULL) {
        fclose(output);
        HuffmanDictionary_destroy(huffmanDictionary);
        HuffmanTree_destroy(huffmanTree);
        MinHeap_destroy(minHeap);
        FrequencyTable_destroy(frequencyTable);
        fclose(input);
        exit(EXIT_FAILURE);
    }

    unsigned char cur = 0;
    size_t curLength = 0;

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, CHUNK_SIZE, input)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
                for (size_t j = 0; j < HuffmanCode_length(HuffmanDictionary_get(huffmanDictionary, buffer[i])); j++) {
                    cur |= HuffmanCode_get(HuffmanDictionary_get(huffmanDictionary, buffer[i]), j) << curLength;
                    curLength++;

                    if (curLength == 8) {
                        elementsWritten = fwrite(&cur, sizeof(unsigned char), 1 ,output);
                        if (elementsWritten != 1) {
                            free(buffer);
                            fclose(output);
                            HuffmanDictionary_destroy(huffmanDictionary);
                            HuffmanTree_destroy(huffmanTree);
                            MinHeap_destroy(minHeap);
                            FrequencyTable_destroy(frequencyTable);
                            fclose(input);
                            exit(EXIT_FAILURE);
                        }

                        cur = 0;
                        curLength = 0;
                    }
            }
        }
    }

    if (curLength != 0) {
        while (curLength < 8) {
            cur |= 0 << curLength;
            curLength++;
        }

        elementsWritten = fwrite(&cur, sizeof(unsigned char), 1 ,output);
        if (elementsWritten != 1) {
            free(buffer);
            fclose(output);
            HuffmanDictionary_destroy(huffmanDictionary);
            HuffmanTree_destroy(huffmanTree);
            MinHeap_destroy(minHeap);
            FrequencyTable_destroy(frequencyTable);
            fclose(input);
            exit(EXIT_FAILURE);
        }
    }

    free(buffer);
    fclose(output);
    HuffmanDictionary_destroy(huffmanDictionary);
    HuffmanTree_destroy(huffmanTree);
    MinHeap_destroy(minHeap);
    FrequencyTable_destroy(frequencyTable);
    fclose(input);
    exit(EXIT_SUCCESS);
}
