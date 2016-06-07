#include "generator/element/qrsqlemptytext.h"

USING_NS_QRORM;

QrSqlEmptyText::QrSqlEmptyText()
    : QrSqlElement(0) {}

QrSqlEmptyText::QrSqlEmptyText(int _index)
    : QrSqlElement(_index) {}

QString QrSqlEmptyText::toString() const
{
    return ((listValues.count() > 0) ? listValues.at(0).toString() : QString(""));
}
