#include "startwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.setStyleSheet("QLineEdit {border: 2px solid gray;border-radius: 3px;selection-background-color: darkgray;}");
    w.show();
    return a.exec();
}
