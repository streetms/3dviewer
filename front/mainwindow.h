#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QMouseEvent>
#include <mutex>
#include "../back/3D.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:    //void drawFigure();
    figure3D_t figure;
    Ui::MainWindow *ui;
    double to_radian(double degree);
    template <typename Item,typename T>
    void setValue(Item* item, T value){
        item->blockSignals(true);
        item->setValue(value);
        item->blockSignals(false);
    }
private slots:
    void on_openFile_clicked();

    void on_rotateXSpinBox_textChanged(const QString &arg1);
    void on_rotateYSpinBox_textChanged(const QString &arg1);
    void on_rotateZSpinBox_textChanged(const QString &arg1);

    void on_rotateZSlider_valueChanged(int value);
    void on_rotateYSlider_valueChanged(int value);
    void on_rotateXSlider_valueChanged(int value);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_translateXSpinBox_valueChanged(int arg1);

    void on_translateXSlider_valueChanged(int value);

    void on_translateYSlider_valueChanged(int value);

    void on_translateYSpinBox_valueChanged(int arg1);

signals:
    void updateFigure();
};
#endif // MAINWINDOW_H
