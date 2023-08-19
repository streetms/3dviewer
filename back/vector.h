//
// Created by konstantin on 12.08.23.
//

#ifndef INC_3DVIEWER_VECTOR_H
#define INC_3DVIEWER_VECTOR_H
typedef unsigned long size_t;
typedef struct vector{
    void* data;
    size_t size;
    size_t capacity;
    size_t sizeOfElement;
    void(*copy)(void* dest, void* src,size_t sizeOfElement);
    void(*destroy)(void* el);
}dynamicArray;

void* get_pointer_by_index(dynamicArray vector, size_t i);
void push_back(dynamicArray* vector, void* item);
void destroy_vector(dynamicArray* v);
#endif //INC_3DVIEWER_VECTOR_H
