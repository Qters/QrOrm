#include "generator/element/qrsqlemptytext.h"

using namespace Qters::QrOrm;

QrSqlEmptyText::QrSqlEmptyText()
    : QrSqlElement(0) {}

QrSqlEmptyText::QrSqlEmptyText(int _index)
    : QrSqlElement(_index) {}

QString QrSqlEmptyText::toString() const
{
    return ((listValues.count() > 0) ? listValues.at(0).toString() : QString(""));
}
