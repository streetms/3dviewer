#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QSettings>
class App : public QApplication
{
public:
    App(int& argc, char** argv,const QString& organizationName,const QString& applicationName);
    ~App();
    static App *theApp();
    QSettings *getSettings();
private:
    QSettings* settings;
};

#endif // APP_H
