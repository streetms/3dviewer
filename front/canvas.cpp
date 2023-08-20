#include "canvas.h"
#include <iostream>
#include <QPainter>
#include <QPalette>
#include "app.h"
Canvas::Canvas(QWidget *parent)
    : QFrame{parent}
{
    this->setAutoFillBackground(true);
    _colorName = App::theApp()->getSettings()->value("background-color","black").toString();

}

void Canvas::setFigure(figure3D_t* figure){
    _figure = figure;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    this->setStyleSheet("border: 2px solid white; border-radius: 2px; padding:"
                        " 2px; background-color:" + _colorName);
    if (_figure->facetArray.size != 0){
        QPainter p;
        p.begin(this);
        facet_t* facets = (facet_t*)_figure->facetArray.data;
        QVector<QPointF> points;
        vertex_t* vertexes = (vertex_t*)_figure->vertexes.data;
        for (size_t i = 0; i < _figure->facetArray.size;i++){
            int* v = (int*)(facets[i].vertexesId.data);
            for (size_t j = 0; j < facets[i].vertexesId.size;j++){
                points.push_back({vertexes[v[j]].x,vertexes[v[j]].y});
            }
            p.drawConvexPolygon(points);
            points.clear();
        }
        p.end();
    }

}

void Canvas::setBackgroudColorName(QString colorName)
{
    _colorName = colorName;
}
