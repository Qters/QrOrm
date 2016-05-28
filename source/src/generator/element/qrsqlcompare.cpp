#include "generator/element/qrsqlcompare.h"

using namespace Qters::QrOrm;

QrSqlCompare::QrSqlCompare() : QrSqlElement(0), type(is_equal_to){}

QrSqlCompare::QrSqlCompare(int _index, QrSqlCompare::CompareType _type) : QrSqlElement(_index), type(_type){}

QString QrSqlCompare::toString() const
{
    Q_ASSERT(1 == listColumns.count () && 1 == listValues.count ());
    QString statement, column(listColumns.at (0)), value(listValues.at (0).toString ());
    Q_ASSERT(! column.isEmpty () && !value.isEmpty ());

    switch (type) {
    case is_equal_to:   statement = column + " = '" + value + "'";   break;
    case is_not_equal_to:   statement = column + " <> '" + value + "'";  break;
    case is_greater_than:   statement = column + " > '" + value + "'";  break;
    case is_greater_than_or_equal_to:   statement = column + " >= '" + value + "'";  break;
    case is_less_than:   statement = column + " < '" + value + "'";  break;
    case is_less_than_or_equal_to:   statement = column + " <= '" + value + "'";  break;
    case like:   statement = column + " LIKE '" + value + "'";  break;
    case not_like:   statement = column + " NOT LIKE '" + value + "'";  break;
    case starts_with:   statement = column + " LIKE '" + value + "'";  break;
    case ends_with:   statement = column + " LIKE '" + value + "'";  break;
    case contains_string:   statement = column + " LIKE '" + value + "'";  break;
    default:    Q_ASSERT(false);    break;
    }

    return statement;
}
