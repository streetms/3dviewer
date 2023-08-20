#ifndef CANVAS_H
#define CANVAS_H

#include <QFrame>
#include <QPalette>
#include "../back/3D.h"
class Canvas : public QFrame
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void setFigure(figure3D_t* figure);
    void paintEvent(QPaintEvent *event) override;
    void setBackgroudColorName(QString colorName);
private:
    figure3D_t* _figure;
    QString _colorName;
    //QString styleSheet;
};

#endif // CANVAS_H
