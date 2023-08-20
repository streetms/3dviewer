#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <clocale>
#include <QTime>
#include <thread>
#include <chrono>

#define M_PI 3.14159

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setlocale(LC_ALL,"C");

    ui->setupUi(this);
    figure.facetArray.size = 0;
    ui->canvas->setFigure(&figure);
    ui->canvas->setStyleSheet(("border: 2px solid white; border-radius: 2px; padding: 2px;"));
    ui->translateXSpinBox->setMinimum(0);
    ui->translateYSpinBox->setMinimum(0);
    ui->translateXSpinBox->setMaximum(ui->canvas->size().width());
    ui->translateYSpinBox->setMaximum(ui->canvas->size().height());
    ui->translateXSlider->setMinimum(0);
    ui->translateYSlider->setMinimum(0);
    ui->translateXSlider->setMaximum(ui->canvas->size().width());
    ui->translateYSlider->setMaximum(ui->canvas->size().height());
}

MainWindow::~MainWindow()
{
    destroy_figure(&figure);
    delete ui;
}


double MainWindow::to_radian(double degree)
{
    return degree*2*M_PI/360;
}

void MainWindow::openFile()
{
    bool ok;
    QString path = QFileDialog::getOpenFileName(0,"выбор файла", "", "");
    if (!path.isEmpty()){
        destroy_figure(&figure);
        figure = read_obg_file(path.toStdString().data(),&ok);
        if (not ok){
            QMessageBox::critical(this,"ошибка","не удалось открыть файл");
        } else{
            ui->fileName->setText("Имя файла: "+ QFileInfo(path).fileName());
            ui->numberOfVertexes->setText("Количество вершин: "+ QString::number(figure.vertexes.size));
            ui->numberOfFacet->setText("Количество граней: "+ QString::number(figure.facetArray.size));
            ui->canvas->repaint();
            ui->translateXSpinBox->setValue(ui->canvas->size().width()/2);
            ui->translateYSpinBox->setValue(ui->canvas->size().height()/2);
            translate_figure(&figure,ui->canvas->size().width()/2,ui->canvas->size().height()/2,0);
            ui->doubleSpinBox->setValue(1);
        }
    }
}


void MainWindow::on_rotateXSpinBox_textChanged(const QString &arg1)
{
    int angle = arg1.toInt();
    rotate_figure(&figure,to_radian(angle),figure.angle.y,figure.angle.z);
    ui->canvas->repaint();
    setValue(ui->rotateXSlider,angle);
}

void MainWindow::on_rotateYSpinBox_textChanged(const QString &arg1)
{
    int angle = arg1.toInt();
    rotate_figure(&figure,figure.angle.x,to_radian(angle),figure.angle.z);
    ui->canvas->repaint();
    setValue(ui->rotateYSlider,angle);
}

void MainWindow::on_rotateZSpinBox_textChanged(const QString &arg1)
{
    int angle = arg1.toInt();
    rotate_figure(&figure,figure.angle.x,figure.angle.y,to_radian(angle));
    ui->canvas->repaint();
    setValue(ui->rotateZSlider,angle);
}
void MainWindow::on_rotateZSlider_valueChanged(int value)
{
    rotate_figure(&figure,figure.angle.x,figure.angle.y,to_radian(value));
    ui->canvas->repaint();
    setValue(ui->rotateZSpinBox,value);
}

void MainWindow::on_rotateYSlider_valueChanged(int value)
{
    rotate_figure(&figure,figure.angle.x,to_radian(value),figure.angle.z);
    ui->canvas->repaint();
    setValue(ui->rotateYSpinBox,value);
}


void MainWindow::on_rotateXSlider_valueChanged(int value)
{
    rotate_figure(&figure,to_radian(value),figure.angle.y,figure.angle.z);
    ui->canvas->repaint();
    ui->rotateXSpinBox->setValue(value);
}


void MainWindow::on_openFile_clicked()
{
    openFile();
}



void MainWindow::on_doubleSpinBox_valueChanged(double scale)
{
    if (scale != 0 && scale != 1){
        scale_figure(&figure,scale,scale,scale);
        ui->canvas->repaint();
    }
}


void MainWindow::on_translateXSpinBox_valueChanged(int value)
{
    translate_figure(&figure,value,figure.center.y,figure.center.z);
    ui->canvas->repaint();
    setValue(ui->translateXSlider,value);
}


void MainWindow::on_translateXSlider_valueChanged(int value)
{
    translate_figure(&figure,value,figure.center.y,figure.center.z);
    ui->canvas->repaint();
    setValue(ui->translateXSpinBox,value);
}


void MainWindow::on_translateYSlider_valueChanged(int value)
{
    translate_figure(&figure,figure.center.x,value,figure.center.z);
    ui->canvas->repaint();
    setValue(ui->translateYSpinBox,value);
}


void MainWindow::on_translateYSpinBox_valueChanged(int value)
{
    translate_figure(&figure,figure.center.x,value,figure.center.z);
    ui->canvas->repaint();
    setValue(ui->translateYSlider,value);
}


void MainWindow::on_openFileAction_triggered()
{
    openFile();
}


void MainWindow::on_action_triggered()
{
    QString s = QFileDialog::getSaveFileName();

    if (figure.facetArray.size != 0){
        QPixmap pixmap(ui->canvas->size());
        pixmap.fill(Qt::black);
        QPainter p;
        QPen pen(Qt::white);
        p.begin(&pixmap);
        p.setPen(pen);
        facet_t* facets = (facet_t*)figure.facetArray.data;
        QVector<QPointF> points;
        vertex_t* vertexes = (vertex_t*)figure.vertexes.data;
        for (size_t i = 0; i < figure.facetArray.size;i++){
            int* v = (int*)(facets[i].vertexesId.data);
            for (size_t j = 0; j < facets[i].vertexesId.size;j++){
                points.push_back({vertexes[v[j]].x,vertexes[v[j]].y});
            }
            p.drawConvexPolygon(points);
            points.clear();
        }
        p.end();
        if (not pixmap.save(s)){
             QMessageBox::critical(this,"ошибка","не удалось создать файл");
        }
    }
}

