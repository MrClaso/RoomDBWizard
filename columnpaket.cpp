#include "columnpaket.h"

ColumnPaket::ColumnPaket()
{

}

std::string ColumnPaket::toUpper(){

    std::string colNameStr, ColNameStr;
    colNameStr = colName.toStdString();
    ColNameStr = colNameStr;
    ColNameStr[0] = toupper(colNameStr[0]);

    return ColNameStr;
};
