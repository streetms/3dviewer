//
// Created by konstantin on 02.08.23.
//

#ifndef INC_3DVIEWER_UTILITY_H
#define INC_3DVIEWER_UTILITY_H
#include <stdbool.h>
#include <stddef.h>
#include "../back/matrix/s21_matrix.h"
#include "vector.h"

typedef struct Vertex{
    double x,y,z;
} vertex_t;

typedef vertex_t vector_t;
typedef vertex_t triple;
typedef struct Facet{
    dynamicArray vertexesId;
    vertex_t normal;
} facet_t;
typedef struct Figure{
    dynamicArray facetArray;
    dynamicArray vertexes;
    vertex_t center;
    triple angle;
    triple scale;
} figure3D_t;


#ifdef __cplusplus
extern "C" {
#endif


void destroy_figure(figure3D_t *figure);
void translate_figure(figure3D_t *figure, double dx, double dy,double dz);
void scale_figure(figure3D_t *figure, double factorX, double factorY,double factorZ);
void rotate_figure(figure3D_t *figure, double X,double Y,double Z);
figure3D_t read_obg_file(const char *filename, bool *ok);
#ifdef __cplusplus
}

#endif
#endif //INC_3DVIEWER_UTILITY_H
