#include "mainwindow.h"
#include <iostream>
#include <thread>
#include <QApplication>
#include "../back/3D.h"
int main(int argc, char *argv[])
{
    //std::cout << std::this_thread::get_id() << "\n";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
