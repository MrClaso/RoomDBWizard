#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSpacerItem>
#include <iostream>
#include <fstream>

namespace Ui {
class TableWindow;
}

class TableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = nullptr);
    ~TableWindow();
    QString tableName, dir;
    std::string package_as_path;
    std::string package;

    void setData(QString dBaseName);


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TableWindow *ui;

    QString dBaseName;
    QString comboBoxOption1String = "String";
    QString comboBoxOption2String = "boolean";
    QString comboBoxOption3String = "int";

    struct columnStruct {

        QCheckBox *del;
        QLineEdit *name;
        QComboBox *type;
        QCheckBox *primary;
        QCheckBox *unique;

    };
    columnStruct column;
    QList<columnStruct> columnList;

};

#endif // TABLEWINDOW_H
