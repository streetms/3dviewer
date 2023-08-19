#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QFrame>
#include "../back/3D.h"
class Canvas : public QFrame
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void setFigure(figure3D_t* figure);
    void paintEvent(QPaintEvent *event) override;
private:
    figure3D_t* _figure;
};

#endif // CANVAS_H
