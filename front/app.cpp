#include "app.h"

App::App(int &argc, char **argv, const QString &organiztaionName, const QString &applicationName) :
    QApplication(argc,argv)
{
    settings = new QSettings(organiztaionName,applicationName);

}

App::~App()
{
    delete settings;
}

App *App::theApp()
{
    return (App*)qApp;
}

QSettings *App::getSettings()
{
    return settings;
}
