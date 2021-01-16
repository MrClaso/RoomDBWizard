#ifndef COLUMNPAKET_H
#define COLUMNPAKET_H
#include <QString>
#include <QVariant>

class ColumnPaket
{
public:
public:
    QString colName;
    QVariant colType;

    std::string toUpper();
    ColumnPaket();
};

#endif // COLUMNPAKET_H
