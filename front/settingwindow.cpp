#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QSettings>
#include "app.h"
#include <iostream>
#include <QColorDialog>
SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_setBackgroundColorButton_clicked()
{
    QSettings* settings = App::theApp()->getSettings();
    QColor color = QColorDialog::getColor(settings->value("background-color","black").toString());
    if (color.isValid()){
        settings->setValue("background-color",color.name());
    }
    //std::cout << color.name().toStdString() << "\n";
}

