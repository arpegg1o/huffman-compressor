
#include "../include/ArrayList.h"

size_t ArrayList_size(ArrayList *array_list) {
    return array_list->size;
}

void ArrayList_add(ArrayList *array_list, E *e) {
    if (array_list->size == array_list->capacity) {
        size_t new_capacity = array_list->capacity * RESIZE_FACTOR;

        E** new_arr = (E**)realloc(array_list->arr, new_capacity * sizeof(*new_arr));
        if (new_arr == NULL) {
            return;
        }

        array_list->arr = new_arr;
        array_list->capacity = new_capacity;
    }

    array_list->arr[array_list->size++] = e;
}

E* ArrayList_get(ArrayList *array_list, size_t index) {
    if (index >= array_list->size) {
        return NULL;
    }

    return array_list->arr[index];
}

void ArrayList_set(ArrayList *array_list, size_t index, E *e) {
    if (index < 0 || index >= array_list->size) {
        return;
    }

    array_list->arr[index] = e;
}

void ArrayList_remove(ArrayList *array_list) {
    if (array_list->size == 0) {
        return;
    }

    array_list->arr[--array_list->size] = NULL;

    if (array_list->capacity > STRATING_CAPACITY && array_list->size == array_list->capacity / RESIZE_FACTOR) {
        size_t new_capacity = array_list->capacity / RESIZE_FACTOR;

        E** new_arr = (E**)realloc(array_list->arr, new_capacity * sizeof(*new_arr));
        if (new_arr == NULL) {
            return;
        }

        array_list->arr = new_arr;
        array_list->capacity = new_capacity;
    }
}

ArrayList* ArrayList_create() {
    ArrayList* arrayList = (ArrayList*)malloc(sizeof(ArrayList));
    if (arrayList == NULL) {
        return NULL;
    }

    arrayList->arr = (E**)malloc(STRATING_CAPACITY * sizeof(E*));
    if (arrayList->arr == NULL) {
        ArrayList_destroy(arrayList);
        return NULL;
    }

    arrayList->size = 0;
    arrayList->capacity = STRATING_CAPACITY;

    return arrayList;

}

void ArrayList_destroy(ArrayList* array_list) {
    if (array_list != NULL) {
        free(array_list->arr);
    }

    free(array_list);
}
