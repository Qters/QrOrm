#include "generator/element/qrsqllimit.h"

#include "entity/qrsqlconfig.h"

USING_NS_QRORM;

QrSqlLimit::QrSqlLimit()
    : QrSqlElement(0) {}

QrSqlLimit::QrSqlLimit(int _index)
    : QrSqlElement(_index) {}

QString QrSqlLimit::toString() const
{
    return QString("LIMIT %1 OFFSET %2").arg (getRowsCount ()).arg (getStartRow ());
}

int QrSqlLimit::getStartRow() const
{
    Q_ASSERT(listValues.count() == 2);
    return ((listValues.count() > 0) ? listValues.at(0).toInt() : 0);
}

int QrSqlLimit::getRowsCount() const
{
    Q_ASSERT(listValues.count() == 2);
    return ((listValues.count() > 1) ? listValues.at(1).toInt() : 0);
}

int QrSqlLimit::getMaxRow() const
{
    Q_ASSERT(listValues.count() == 2);
    return ((listValues.count() > 1) ? (listValues.at(0).toInt() + listValues.at(1).toInt()) : 0);
}

QString QrSqlLimit::getStartRow_ParamKey() const
{
    QString startRow("offset_start_row");
    startRow += "_" + QString::number(index) + "_0";
    if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_question_mark) {
        startRow = "?";
    }else if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_at_name) {
        startRow = "@" + startRow;
    }else {
        startRow = ":" + startRow;
    }
    return startRow;
}

QString QrSqlLimit::getRowsCount_ParamKey() const
{
    QString rowsCount("limit_rows_count");
    rowsCount += "_" + QString::number(index) + "_0";
    if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_question_mark) {
        rowsCount = "?";
    }else if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_at_name) {
        rowsCount = "@" + rowsCount;
    }else {
        rowsCount = ":" + rowsCount;
    }
    return rowsCount;
}

QString QrSqlLimit::getMaxRow_ParamKey() const
{
    QString maxRow("offset_max_row");
    maxRow += "_" + QString::number(index) + "_0";
    if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_question_mark) {
        maxRow = "?";
    }else if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_at_name) {
        maxRow = "@" + maxRow;
    }else {
        maxRow = ":" + maxRow;
    }
    return maxRow;
}
