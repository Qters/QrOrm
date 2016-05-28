#include "generator/element/qrsqlisnull.h"

using namespace Qters::QrOrm;

QrSqlIsNull::QrSqlIsNull()
    : QrSqlElement(0), type(QrSqlIsNull::is_null) { }

QrSqlIsNull::QrSqlIsNull(int _index, QrSqlIsNull::NullType _type)
    : QrSqlElement(_index), type(_type) { }

QString QrSqlIsNull::toString() const
{
    Q_ASSERT(listColumns.count() == 1);
    QString statement, column(listColumns.at(0));
    Q_ASSERT(! column.isEmpty());

    switch (type)
    {
       case is_null:       statement = column + " IS NULL";        break;
       case is_not_null:   statement = column + " IS NOT NULL";    break;
       default:             Q_ASSERT(false);
    }

    return statement;
}
