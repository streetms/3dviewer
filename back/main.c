#include <stdio.h>
#include "3D.h"
#include <time.h>

int main() {

    figure3D_t figure3D;
    bool ok;
    figure3D = read_obg_file("/home/konstantin/CLionProjects/3DViewer/figures/Skull.obj",&ok);

//    time_t start = clock();
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);
    scale_figure(&figure3D,5,5);

    destroy_figure(&figure3D);
//    time_t stop = clock();
//    printf("%g",(stop-start)/(double)CLOCKS_PER_SEC);

//    if (ok){
//        facet_t * facets = figure3D.facetArray->data;
//        for (size_t i = 0; i < figure3D.facetArray->size;i++){
//            for (size_t j = 0; j < facets[i].vertexes.size; j++){
//                vertex_t* vertex = get_pointer_by_index(facets[i].vertexes, j);
//                printf("(%.1lf;%.1lf;%.1lf) ",vertex->x,vertex->y,vertex->z);
//            }
//            printf("\n");
//        }
//        printf("-----------------------------------------------------------------------\n");
//        scale_figure(&figure3D,100,100);
//        translate_figure(&figure3D,200,200);
//        for (size_t i = 0; i < figure3D.facetArray->size;i++){
//            for (size_t j = 0; j < facets[i].vertexes.size; j++){
//                vertex_t* vertex = get_pointer_by_index(facets[i].vertexes, j);
//                printf("(%.1lf;%.1lf;%.1lf) ",vertex->x,vertex->y,vertex->z);
//            }
//            printf("\n");
//        }
//    } else{
//        printf("error");
//    }

    return 0;
}
