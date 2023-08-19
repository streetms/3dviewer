//
// Created by konstantin on 02.08.23.
//

#include "3D.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

static matrix_t create_translation_matrix(double dx, double dy,double dz){
    matrix_t res = s21_create_matrix();
    res.matrix[0][0] = 1;
    res.matrix[1][1] = 1;
    res.matrix[2][2] = 1;
    res.matrix[3][3] = 1;
    res.matrix[0][3] = dx;
    res.matrix[1][3] = dy;
    res.matrix[2][3] = dz;
    return res;
}
static matrix_t create_rotation_matrix(double X,double Y, double Z){
    matrix_t res = s21_create_matrix();
    matrix_t resX = s21_create_matrix();
    matrix_t resY = s21_create_matrix();
    matrix_t resZ = s21_create_matrix();

    resX.matrix[0][0] = 1;
    resX.matrix[1][1] = cos(X);
    resX.matrix[1][2] = -sin(X);
    resX.matrix[2][1] = sin(X);
    resX.matrix[2][2] = cos(X);
    resX.matrix[3][3] = 1;

    resY.matrix[0][0] = cos(Y);
    resY.matrix[0][2] = sin(Y);
    resY.matrix[1][1] = 1;
    resY.matrix[2][0] = -sin(Y);
    resY.matrix[2][2] = cos(Y);
    resY.matrix[3][3] = 1;

    resZ.matrix[0][0] = cos(Z);
    resZ.matrix[0][1] = -sin(Z);
    resZ.matrix[1][1] = cos(Z);
    resZ.matrix[1][0] = sin(Z);
    resZ.matrix[2][2] = 1;
    resZ.matrix[3][3] = 1;
//    resX.matrix[0][0] = cos(X);
//    resX.matrix[0][1] = sin(X);
//    resX.matrix[1][1] = cos(X);
//    resX.matrix[1][0] = -sin(X);
//    resX.matrix[2][2] = 1;
//    resY.
    matrix_t tmp = s21_create_matrix();
    s21_mult_matrix(&resX,&resY,&tmp);
    s21_mult_matrix(&tmp,&resZ,&res);
//    res.matrix[0][0] = cos(Y)*cos(Z);
//    res.matrix[0][1] = -sin(Z)*cos(Y);
//    res.matrix[0][2] = sin(Y);
//    res.matrix[1][0] = sin(X)*sin(Y)*cos(Z)+sin(Z)*cos(X);
//    res.matrix[1][1] = -sin(X)*sin(Y)*sin(Z)+cos(X)*cos(Z);
//    res.matrix[1][2] = -sin(X)*cos(Y);
//    res.matrix[2][0] = sin(X)*sin(Z)-sin(Y)*cos(X)*cos(Z);
//    res.matrix[2][1] = sin(X)*cos(Z)+sin(Y)*sin(Z)*cos(X);
//    res.matrix[2][2] = cos(X)*cos(Y);
    return res;
}
static matrix_t create_scaling_matrix(double X,double Y,double Z){
    matrix_t res = s21_create_matrix();
    res.matrix[0][0] = X;
    res.matrix[1][1] = Y;
    res.matrix[2][2] = Z;
    res.matrix[3][3] = 1;
    return res;
}
static void destroy_facet(facet_t* facet){
    free(facet->vertexesId.data);
    facet->vertexesId.data = NULL;
    facet->vertexesId.size = 0;
    facet->vertexesId.capacity = 0;
}
static void facet_destroy(void* facet){
    destroy_facet(facet);
}

static void facet_copy(void* dest, void* src,size_t sizeOfElement){
    (void)(sizeOfElement);
    facet_t* _dest = dest;
    facet_t* _src = src;
    memcpy(_dest,src,sizeOfElement);
    _dest->vertexesId.data = malloc(_src->vertexesId.size*sizeof (int));
    memcpy(_dest->vertexesId.data,_src->vertexesId.data,_src->vertexesId.size*sizeof (int));
}
static dynamicArray create_vector(size_t sizeOfElement, void(*copy)(void* dest, void* src, size_t sizeOfElement), void(*destroy)(void* el)){
    dynamicArray v;
    v.sizeOfElement = sizeOfElement;
    v.capacity = 0;
    v.data = NULL;
    v.size = 0;
    v.copy = copy;
    v.destroy = destroy;
    return v;
}

figure3D_t createFigure(){
    figure3D_t figure;
    figure.vertexes.size = 0;// = malloc(sizeof (Vector));
    figure.facetArray = create_vector(sizeof (facet_t), facet_copy, facet_destroy);
    figure.facetArray.size = 0;
    figure.center.x = 0;
    figure.center.y = 0;
    figure.center.z = 0;
    figure.angle.x = 0;
    figure.angle.y = 0;
    figure.angle.z = 0;
    figure.scale.x = 1;
    figure.scale.y = 1;
    figure.scale.z = 1;
    return figure;
}


void destroy_figure(figure3D_t* figure){
    if (figure->facetArray.size != 0){
        figure->center.x = 0;
        figure->center.y = 0;
        figure->center.z = 1;
        for (size_t i = 0;i < figure->facetArray.size;i++){
            facet_t* f = get_pointer_by_index(figure->facetArray,i);
            destroy_facet(f);
            f = NULL;
        }
        free(figure->facetArray.data);
        figure->facetArray.data = NULL;
        figure->facetArray.size = 0;
        figure->facetArray.capacity = 0;
    }

}




static void read_vertex(const char* line, dynamicArray* vertexes){
    vertex_t vertex;
    char type [16];
    sscanf(line,"%s %lf %lf %lf",type,&vertex.x,&vertex.y,&vertex.z);
    push_back(vertexes,&vertex);
}
static void read_normal(const char* line, dynamicArray* normals){
    char type[16];
    vertex_t normal;
    sscanf(line,"%s %lf %lf %lf",type,&normal.x,&normal.y,&normal.z);
    push_back(normals,&normal);
}
static void read_facet(char* line, dynamicArray* facetArray, dynamicArray* normals){
    (void)(normals);
    facet_t facet;
    facet.vertexesId = create_vector(sizeof(int), NULL, NULL);
    dynamicArray points = create_vector(sizeof(int), NULL, NULL);
    int n;
    int point;
    int texture;
    char* token = strtok(line+2," ");
    while (token != NULL){
        if (strstr(token,"//") != NULL) {
            sscanf(token, "%d//%d", &point, &n);
        } else{
            sscanf(token,"%d/%d/%d",&point,&texture,&n);
        }
        push_back(&points,&point);
        token = strtok(NULL," ");
    }

    //memcpy(&facet.normal, get_pointer_by_index(*normals,n-1),normals->sizeOfElement);
    for (size_t j =0; j < points.size;j++) {
        int* p = points.data;
        int index = p[j]-1;
        push_back(&facet.vertexesId, &index);
    }
    push_back(facetArray,&facet);
    //destroy_facet(&facet);
    destroy_vector(&points);
}
figure3D_t read_obg_file(const char* filename, bool* ok)
{
    figure3D_t figure = createFigure();
    *ok = true;
    FILE* file = fopen(filename,"r");
    char* dot_position = strchr(filename,'.');

    if (file == NULL || dot_position == NULL || strcmp(dot_position,".obj") != 0) {
        *ok = false;
        destroy_figure(&figure);
        return figure;
    }
    char line[256] = {};
    figure.vertexes = create_vector(sizeof (vertex_t), NULL, NULL);
    dynamicArray normals = create_vector(sizeof (vertex_t), NULL, NULL);
    while (fgets(line,256,file)) {
        char type[16];
        sscanf(line,"%s",type);

        if (strcmp(type,"v") == 0) {
            read_vertex(line,&figure.vertexes);
        }
        else if (strcmp(type,"vn") == 0) {
            read_normal(line,&normals);
        }
        else if (strcmp("f",type) == 0) {
            read_facet(line,&figure.facetArray,&normals);
        }
    }
    destroy_vector(&normals);
    fclose(file);
    return figure;
}

static matrix_t matrix_from_vector(vertex_t vertex){
    matrix_t res = s21_create_matrix();
    res.columns = 1;
    res.rows = 4;
    res.matrix[0][0] = vertex.x;
    res.matrix[1][0] = vertex.y;
    res.matrix[2][0] = vertex.z;
    res.matrix[3][0] = 1;
    return res;
}
static vertex_t vector_from_matrix(matrix_t matrix){
    vertex_t v;
    v.x = matrix.matrix[0][0];
    v.y = matrix.matrix[1][0];
    v.z = matrix.matrix[2][0];
    return v;
}

static void apply_operation(vertex_t *v, matrix_t operator){
    matrix_t tmp = matrix_from_vector(*v);
    matrix_t res = s21_create_matrix();
    s21_mult_matrix(&operator, &tmp, &res);
    *v = vector_from_matrix(res);
}
void translate_figure(figure3D_t *figure, double dx, double dy,double dz){
    if (figure->facetArray.size != 0) {
        triple center = figure->center;
        matrix_t translationMatrix = create_translation_matrix(dx-center.x,dy-center.y,dz-center.z);
        vertex_t* vertexes = figure->vertexes.data;

        for (size_t i = 0; i < figure->vertexes.size;i++){
            apply_operation(&vertexes[i],translationMatrix);
        }
        apply_operation(&figure->center, translationMatrix);
    }
}
void transform(figure3D_t* figure,matrix_t operator){
    matrix_t translateMatrix = create_translation_matrix(-figure->center.x, -figure->center.y,-figure->center.z);
    matrix_t inverseMatrix = create_translation_matrix(figure->center.x, figure->center.y,figure->center.z);
    vertex_t *vertexes = figure->vertexes.data;
    for (size_t i = 0; i < figure->vertexes.size; i++) {
        apply_operation(&vertexes[i], translateMatrix);
        apply_operation(&vertexes[i], operator);
        apply_operation(&vertexes[i],inverseMatrix);
    }
}
void scale_figure(figure3D_t *figure, double factorX, double factorY, double factorZ){
    if (figure->facetArray.size != 0) {
        vector_t startScale = figure->scale;
        matrix_t scalingMatrix = create_scaling_matrix(factorX/startScale.x, factorY/startScale.y,factorZ/startScale.z);
        transform(figure,scalingMatrix);
        figure->scale.x = factorX;
        figure->scale.y = factorY;
        figure->scale.z = factorZ;
    }
}
void rotate_figure(figure3D_t *figure, double X, double Y, double Z){
    if (figure->facetArray.size != 0) {
        vector_t startAngle = figure->angle;
        matrix_t rotationMatrix = create_rotation_matrix(X-startAngle.x,Y-startAngle.y,Z-startAngle.z);
        transform(figure,rotationMatrix);
        figure->angle.x = X;
        figure->angle.y = Y;
        figure->angle.z = Z;
        //apply_operation(&figure->center,rotationMatrix);
    }
}

