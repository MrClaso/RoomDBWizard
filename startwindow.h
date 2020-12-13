#ifndef STARTWINDOW_H
#define STARTWINDOW_H
#include "tablewindow.h"
#include "ui_tablewindow.h"

#include <QDialog>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

    Ui::StartWindow *startUi;
    QString dir;

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_pushButton_2_clicked();

private:

    TableWindow *tableDialog;
    std::ofstream myfile;
    std::fstream iofile;
    std::string package_as_path;
    std::string package;
    bool path_calculated;

    void calculate_path();
};
#endif // STARTWINDOW_H
