
#include "../include/MinHeap.h"

size_t parent(size_t i) {
   return (i - 1) / 2;
}

size_t left(size_t i) {
   return (2 * i) + 1;
}

size_t right(size_t i) {
   return (2 * i) + 2;
}

size_t MinHeap_size(MinHeap* minHeap) {
    return minHeap->arrayList->size;
}

E* MinHeap_get(MinHeap* minHeap, size_t index) {
    return ArrayList_get(minHeap->arrayList, index);
}

void MinHeap_set(MinHeap* minHeap, size_t index, E* e) {
    ArrayList_set(minHeap->arrayList, index, e);
}

void heapify_up(MinHeap *minHeap, size_t index) {
    while (1) {
        size_t parent_index = parent(index);

        E *node = MinHeap_get(minHeap, index);
        E *parent_node = MinHeap_get(minHeap, parent_index);

        if (index == 0 || minHeap->cmp(node, parent_node) >= 0) {
            break;
        }

        MinHeap_set(minHeap, index, parent_node);
        MinHeap_set(minHeap, parent_index, node);

        index = parent_index;
    }
}

void heapify_down(MinHeap *minHeap, size_t index) {
    while (1) {
        size_t left_index = left(index);
        size_t right_index = right(index);

        E* node = MinHeap_get(minHeap, index);
        E* left_node = MinHeap_get(minHeap, left_index);
        E* right_node = MinHeap_get(minHeap, right_index);

        E* smallest_node = node;
        if (left_node != NULL && minHeap->cmp(left_node, smallest_node) < 0) {
            smallest_node = left_node;
        }
        if (right_node != NULL && minHeap->cmp(right_node, smallest_node) < 0) {
            smallest_node = right_node;
        }

        if (smallest_node == node) {
            break;
        } else if (smallest_node == left_node) {
            MinHeap_set(minHeap, index, left_node);
            MinHeap_set(minHeap, left_index, node);

            index = left_index;
        } else {
            MinHeap_set(minHeap, index, right_node);
            MinHeap_set(minHeap, right_index, node);

            index = right_index;
        }
    }

}

void MinHeap_push(MinHeap *minHeap, E* e) {
    ArrayList_add(minHeap->arrayList, e);
    heapify_up(minHeap, MinHeap_size(minHeap) - 1);
}

E* MinHeap_pop(MinHeap *minHeap) {
    if (MinHeap_size(minHeap) == 0) {
        return NULL;
    }

    E* min = MinHeap_peek(minHeap);

    MinHeap_set(minHeap, 0, MinHeap_get(minHeap, MinHeap_size(minHeap) - 1));
    ArrayList_remove(minHeap->arrayList);
    heapify_down(minHeap, 0);

    return min;
}

E* MinHeap_peek(MinHeap *minHeap) {
    return MinHeap_get(minHeap, 0);
}

MinHeap* MinHeap_create() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (minHeap == NULL) {
        return NULL;
    }

    minHeap->arrayList = ArrayList_create();
    if (minHeap->arrayList == NULL) {
        MinHeap_destroy(minHeap);
        return NULL;
    }

    minHeap->cmp = HuffmanNode_cmp;
    return minHeap;
}

void MinHeap_destroy(MinHeap *minHeap) {
    if (minHeap != NULL) {
        ArrayList_destroy(minHeap->arrayList);
    }

    free(minHeap);
}

MinHeap* MinHeap_fromFrequencyTable(FrequencyTable* frequencyTable) {
    MinHeap* minHeap = MinHeap_create();
    if (minHeap == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < 256; i++) {
        unsigned int frequency = FrequencyTable_get(frequencyTable, i);
        if (frequency != 0) {
            HuffmanNode* huffmanNode = HuffmanNode_create((char)i, frequency);
            MinHeap_push(minHeap, huffmanNode);
        }
    }

    return minHeap;
}
