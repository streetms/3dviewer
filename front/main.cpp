#include "mainwindow.h"
#include <iostream>
#include <thread>
#include "app.h"
#include "../back/3D.h"
int main(int argc, char *argv[])
{
    App a(argc, argv,"streetms","3dViewer");
    MainWindow w;
    w.show();
    return a.exec();
}
