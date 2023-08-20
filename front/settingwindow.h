#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void on_setBackgroundColorButton_clicked();

private:
    Ui::SettingWindow *ui;
signals:
    void updateColor(QString color);
};

#endif // SETTINGWINDOW_H
