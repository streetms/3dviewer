//
// Created by konstantin on 12.08.23.
//

#include "vector.h"
#include <stdlib.h>
#include <string.h>

void push_back(dynamicArray* vector, void* item) {
    if (vector->size == vector->capacity) {
        if (vector->capacity == 0) {
            vector->capacity = 1;
        }
        void* tmp = malloc(vector->capacity*2*vector->sizeOfElement);
        memcpy(tmp, vector->data, vector->size * vector->sizeOfElement);
        free(vector->data);
        vector->data = tmp;
        vector->capacity*=2;
    }
    if (vector->copy != NULL) {
        vector->copy(get_pointer_by_index(*vector, vector->size), item, vector->sizeOfElement);
    } else{
        memcpy(get_pointer_by_index(*vector,vector->size),item,vector->sizeOfElement);
    }
    vector->size++;
}
void destroy_vector(dynamicArray* v){
    if (v->destroy != NULL){
        for (size_t i = 0; i < v->size; i++){
            v->destroy(get_pointer_by_index(*v,i));
        }
    }
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void* get_pointer_by_index(dynamicArray vector, size_t i){
    return vector.data+i*vector.sizeOfElement;
}