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
    std::string dataBaseStr, DataBaseStr, tableNameStr, TableNameStr;
    std::string TableToViewStr, tableToViewStr;
    bool path_calculated, ok, showTable;
    QList<ColumnPaket> columnPaketList;

    struct TableStruct {
        QString tableName;
        QList<ColumnPaket> columnPaketList;
        QCheckBox *makeTable;
    } table;
    QList<TableStruct> tableList;

    QList<TableStruct>::iterator it;
    //    QList<QHBoxLayout*> layoutList;

    bool f1();
    bool f2();
    bool f3();
    bool f5();
    bool f4();
    bool f6();
    bool f7();
    bool f8();
    bool calculate_path();
};
#endif // STARTWINDOW_H
