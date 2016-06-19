#include "generator/element/qrsqlsort.h"

USING_NS_QRORM;

QrSqlSort::QrSqlSort()
    : QrSqlElement(0), type(QrSqlSort::order_asc){}

QrSqlSort::QrSqlSort(int _index, QrSqlSort::SortType _type)
    : QrSqlElement(_index), type(_type){}

QString QrSqlSort::toString() const
{
    QString statement;

    switch (type) {
    case order_asc:     statement = "order by "; break;
    case order_desc:    statement = "order by "; break;
    case group_by:      statement = "group by "; break;
    default:        Q_ASSERT(false);    break;
    }

    QString column;
    for( int idx=0; idx<listColumns.count (); ++idx){
        statement += ((0 == idx) ? QString("") : QString(", "));
        column = listColumns.at (idx);
        Q_ASSERT(! column.isEmpty ());
        switch (type) {
        case order_asc:     statement += column + " asc";   break;
        case order_desc:    statement += column + " desc";  break;
        case group_by:      statement += column;            break;
        default:        Q_ASSERT(false);    break;
        }
    }

    return statement;
}

