#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include "general.h"
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

private:
    Ui::TableWindow *ui;

    QCheckBox *checkBoxDelete;
    QLineEdit *lEColumnName;
    QComboBox *comboBoxType;
    QCheckBox *checkBoxPrimary, *checkBoxAI, *checkBoxIndex;
    QCheckBox *checkBoxUniqe;
    QHBoxLayout *hL;

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
        QCheckBox *AI;
        QCheckBox *index;

    };
    columnStruct column;
    QList<columnStruct> columnList;

    ColumnPaket columnPaket;


public:
    explicit TableWindow(QWidget *parent = nullptr);
    ~TableWindow();
    QString tableName, dir;
    std::string package_as_path;
    std::string package;

    QList<ColumnPaket> columnPaketList;

    void setData(QString dBaseName);


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


};

#endif // TABLEWINDOW_H
