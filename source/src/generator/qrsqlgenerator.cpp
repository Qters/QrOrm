#include "generator/qrsqlgenerator.h"

#include <QtCore/qdebug.h>

#include "entity/qrsqltable.h"
#include "entity/qrsqlquery.h"
#include "generator/element/qrsqllimit.h"
#include "generator/element/qrsqlemptytext.h"
#include "generator/element/qrsqlelementtemp.h"

namespace Qters {

namespace QrOrm {

class QrSqlGeneratorPrivate {
public:
    QrSqlGeneratorPrivate()
        : isDistinct(false), sqlElementIndex(0), parenthesisCount(0) {}

public:
    static QVariantList emptyValues;

public:
    //  member variables of conditon
    bool isDistinct;    //  Replace SELECT by SELECT DISTINCT in SQL query
    int sqlElementIndex;    //  Current index of SQL element
    int parenthesisCount;   //  Current parenthesis count
    QSharedPointer<QrSqlElement>    sqlElementTemp;      // Temporary SQL element
    QList< QSharedPointer<QrSqlElement> >   listSqlElement; //  List of all SQL elements to build SQL query

    //  member variables of base
    QrSqlGenerator::QrColValList listColvals;     //  List of pair of column and value
    QStringList listColumns;     //  List of pair of column
    QVector<QVariantList> listValueses;     //  List of pair of value

    //  member variables of extra
    QrSqlTable *sqlTable;  //  table data class
};

}   //  namespace QrOrm

}   //  namespace Qters

using namespace Qters::QrOrm;

QVariantList QrSqlGeneratorPrivate::emptyValues = QVariantList();

QrSqlGenerator::QrSqlGenerator()
    :d_ptr(new QrSqlGeneratorPrivate)
{

}

QString QrSqlGenerator::getCondition()
{
    Q_D(QrSqlGenerator);
    QString statement = " ";
    if (d->listSqlElement.count () <= 0 ) {
        return statement;
    }

    while (d->parenthesisCount>0) {
        closeParenthesis ();
    }

    for (int idx = 0; idx < d->listSqlElement.count (); ++idx) {
        statement += d->listSqlElement.at (idx).data ()->toString() + " ";
    }

    return statement;
}

bool QrSqlGenerator::distinct() const
{
    Q_D(const QrSqlGenerator);
    return d->isDistinct;
}

QrSqlGenerator &QrSqlGenerator::distinctize()
{
    Q_D(QrSqlGenerator);
    d->isDistinct = true;
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::where(const QString & column)
{
    return addSqlExpression(column, QrSqlExpression::where);
}

QrSqlGenerator &QrSqlGenerator::where_OpenParenthesis(const QString & column)
{
    where(column);
    return openParenthesis();
}

QrSqlGenerator &QrSqlGenerator::and_(const QString & column)
{
    return addSqlExpression(column, QrSqlExpression::and_);
}

QrSqlGenerator &QrSqlGenerator::and_OpenParenthesis(const QString & column)
{
    and_(column);
    return openParenthesis();
}

QrSqlGenerator &QrSqlGenerator::or_(const QString & column)
{
    return addSqlExpression(column, QrSqlExpression::or_);
}

QrSqlGenerator &QrSqlGenerator::or_OpenParenthesis(const QString & column)
{
    or_(column);
    return openParenthesis();
}

QrSqlGenerator &QrSqlGenerator::openParenthesis()
{
    Q_D(QrSqlGenerator);
    QSharedPointer<QrSqlExpression> p;
    p.reset(new QrSqlExpression(d->sqlElementIndex++, QrSqlExpression::open_parenthesis));
    d->listSqlElement.append(p);
    d->parenthesisCount++;
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::closeParenthesis()
{
    Q_D(QrSqlGenerator);
    if (d->parenthesisCount <= 0) {
        return (* this);
    }
    QSharedPointer<QrSqlExpression> p;
    p.reset(new QrSqlExpression(d->sqlElementIndex++, QrSqlExpression::close_parenthesis));
    d->listSqlElement.append(p);
    d->parenthesisCount--;
    d->sqlElementTemp.reset();
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::limit(int rowsCount, int startRow)
{
    Q_D(QrSqlGenerator);
    QSharedPointer<QrSqlLimit> p;
    p.reset(new QrSqlLimit(d->sqlElementIndex++));
    p->setValues(QVariantList() << QVariant(startRow) << QVariant(rowsCount));
    d->listSqlElement.append(p);
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::like(const QString & val)
{
   return addSqlCompare(QVariant(val), QrSqlCompare::like);
}

QrSqlGenerator &QrSqlGenerator::notLike(const QString & val)
{
   return addSqlCompare(QVariant(val), QrSqlCompare::not_like);
}

QrSqlGenerator &QrSqlGenerator::startsWith(const QString & val)
{
   return addSqlCompare(QVariant(val), QrSqlCompare::starts_with);
}

QrSqlGenerator &QrSqlGenerator::endsWith(const QString & val)
{
   return addSqlCompare(QVariant(val), QrSqlCompare::ends_with);
}

QrSqlGenerator &QrSqlGenerator::containsString(const QString & val)
{
   return addSqlCompare(QVariant(val), QrSqlCompare::contains_string);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QStringList & columns)
{
    return addSqlSort(columns, QrSqlSort::order_asc);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QStringList & columns)
{
    return addSqlSort(columns, QrSqlSort::order_desc);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariantList & values)
{
    return addSqlIn(values, QrSqlIn::in);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QStringList &columns)
{
    return addSqlSort(columns, QrSqlSort::group_by);
}

QrSqlGenerator &QrSqlGenerator::isEqualTo(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_equal_to);
}

QrSqlGenerator &QrSqlGenerator::isNotEqualTo(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_not_equal_to);
}

QrSqlGenerator &QrSqlGenerator::isGreaterThan(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_greater_than);
}

QrSqlGenerator &QrSqlGenerator::isGreaterThanOrEqualTo(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_greater_than_or_equal_to);
}

QrSqlGenerator &QrSqlGenerator::isLessThan(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_less_than);
}

QrSqlGenerator &QrSqlGenerator::isLessThanOrEqualTo(const QVariant & val)
{
    return addSqlCompare(val, QrSqlCompare::is_less_than_or_equal_to);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariantList & values)
{
    return addSqlIn(values, QrSqlIn::not_in);
}

QrSqlGenerator &QrSqlGenerator::addSqlExpression(const QString & column, QrSqlExpression::ExpressionType type)
{
    Q_D(QrSqlGenerator);
    QSharedPointer<QrSqlExpression> p;
    p.reset(new QrSqlExpression(d->sqlElementIndex++, type));
    d->listSqlElement.append(p);

    d->sqlElementTemp.reset(new QrSqlElementTemp());
    d->sqlElementTemp->setColumn(column);
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::addSqlCompare(const QVariant & val, QrSqlCompare::CompareType type)
{
    Q_D(QrSqlGenerator);
    if (! d->sqlElementTemp) {
        qDebug() << "invalid SQL query, need a column name";
        Q_ASSERT(false);
        return (* this);
    }

    QSharedPointer<QrSqlCompare> p;
    p.reset(new QrSqlCompare(d->sqlElementIndex++, type));
    p->clone(d->sqlElementTemp.data ());
    p->setValue(val);

    d->listSqlElement.append(p);
    d->sqlElementTemp.reset();
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::addSqlSort(const QStringList & columns, QrSqlSort::SortType type)
{
    Q_D(QrSqlGenerator);
    QSharedPointer<QrSqlSort> p;
    p.reset(new QrSqlSort(d->sqlElementIndex++, type));
    p->setColumns(columns);
    d->listSqlElement.append(p);
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::addSqlIn(const QVariantList & values, QrSqlIn::InType type)
{
    Q_D(QrSqlGenerator);
    if (! d->sqlElementTemp) {
        qDebug() << "invalid SQL query, need a column name";
        Q_ASSERT(false);
        return (* this);
    }

    QSharedPointer<QrSqlIn> p;
    p.reset(new QrSqlIn(d->sqlElementIndex++, type));
    p->clone(d->sqlElementTemp.data());
    p->setValues(values);

    d->listSqlElement.append(p);
    d->sqlElementTemp.reset();
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::addSqlIsNull(QrSqlIsNull::NullType type)
{
    Q_D(QrSqlGenerator);
    if (! d->sqlElementTemp) {
        qDebug() << "invalid SQL query, need a column name";
        Q_ASSERT(false);
        return (* this);
    }

    QSharedPointer<QrSqlIsNull> p;
    p.reset(new QrSqlIsNull(d->sqlElementIndex++, type));
    p->clone(d->sqlElementTemp.data());

    d->listSqlElement.append(p);
    d->sqlElementTemp.reset();
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::addSqlIsBetween(const QVariant & val1, const QVariant & val2, QrSqlIsBetween::BetweenType type)
{
    Q_D(QrSqlGenerator);
    if (! d->sqlElementTemp) {
        qDebug() << "invalid SQL query, need a column name";
        Q_ASSERT(false);
        return (* this);
    }

    QSharedPointer<QrSqlIsBetween> p;
    p.reset(new QrSqlIsBetween(d->sqlElementIndex++, type));
    p->clone(d->sqlElementTemp.data());
    p->setValues(QVariantList() << val1 << val2);

    d->listSqlElement.append(p);
    d->sqlElementTemp.reset();
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::isBetween(const QVariant & val1, const QVariant & val2)
{
   return addSqlIsBetween(val1, val2, QrSqlIsBetween::is_between);
}

QrSqlGenerator &QrSqlGenerator::isNotBetween(const QVariant & val1, const QVariant & val2)
{
   return addSqlIsBetween(val1, val2, QrSqlIsBetween::is_not_between);
}

///////////////////////////////
QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1)
{
    return orderAsc(QStringList() << col1);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2)
{
    return orderAsc(QStringList() << col1 << col2);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3)
{
    return orderAsc(QStringList() << col1 << col2 << col3);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QrSqlGenerator &QrSqlGenerator::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
    return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1)
{
    return orderDesc(QStringList() << col1);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2)
{
    return orderDesc(QStringList() << col1 << col2);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3)
{
    return orderDesc(QStringList() << col1 << col2 << col3);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QrSqlGenerator &QrSqlGenerator::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
    return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1)
{
    return groupBy(QStringList() << col1);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2)
{
    return groupBy(QStringList() << col1 << col2);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3)
{
    return groupBy(QStringList() << col1 << col2 << col3);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QrSqlGenerator &QrSqlGenerator::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
    return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1)
{
    return in(QVariantList() << val1);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2)
{
    return in(QVariantList() << val1 << val2);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3)
{
    return in(QVariantList() << val1 << val2 << val3);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4)
{
    return in(QVariantList() << val1 << val2 << val3 << val4);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5)
{
    return in(QVariantList() << val1 << val2 << val3 << val4 << val5);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6)
{
    return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7)
{
    return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8)
{
    return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8);
}

QrSqlGenerator &QrSqlGenerator::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9)
{
    return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8 << val9);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1)
{
    return notIn(QVariantList() << val1);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2)
{
    return notIn(QVariantList() << val1 << val2);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3)
{
    return notIn(QVariantList() << val1 << val2 << val3);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8);
}

QrSqlGenerator &QrSqlGenerator::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9)
{
    return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8 << val9);
}

QPair<QStringList, QVariantList> QrSqlGenerator::colvalsSperate(const QrSqlGenerator::QrColValList &colvals_) const
{
    QStringList columns;
    QVariantList values;
    QrSqlGenerator::QrColValList colvals = colvals_;
    while(!colvals.empty ()) {
        QrSqlGenerator::ColVal colval = colvals.front ();
        columns.push_back (colval.first);
        values.push_back (colval.second);
        colvals.pop_front ();
    }
    Q_ASSERT(columns.count () == values.count () );

    return QPair<QStringList, QVariantList>(columns, values);
}

QPair<QString, QString> QrSqlGenerator::colvalsToString(const QrSqlGenerator::QrColValList &colvals_) const
{
    if (colvals_.empty ()) {
        return QPair<QString, QString>("", "");
    }

    auto colval_pair = colvalsSperate(colvals_);
    QStringList columns = colval_pair.first;
    QVariantList values = colval_pair.second;

    QString colsStatement, valsStatement;
    for (int idx = 0; idx < columns.count (); ++idx) {
        colsStatement += (0==idx) ? "(" : ", ";
        colsStatement += columns.at(idx);
    }
    if (!columns.empty ()) {
        colsStatement += ")";
    }

    for (int idx = 0; idx < values.count (); ++idx) {
        valsStatement += (0==idx) ? "(" : ", ";
        valsStatement += values.at(idx).toString ();
    }
    valsStatement += ")";

    return QPair<QString, QString>(colsStatement, valsStatement);
}

QrSqlGenerator &QrSqlGenerator::colvals(const QrColValList &listColvals)
{
    Q_D(QrSqlGenerator);
    d->listColvals = listColvals;

    auto colvals_pair = colvalsSperate (listColvals);

    d->listColumns.append(colvals_pair.first);
    d->listValueses.push_back(colvals_pair.second);

    return (* this);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1)
{
    return colvals(QrColValList() << colval1);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2)
{
    return colvals(QrColValList() << colval1 << colval2);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4 << colval5);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4 << colval5 << colval6);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4 << colval5 << colval6 << colval7);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7, const ColVal &colval8)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4 << colval5 << colval6 << colval7 << colval8);
}

QrSqlGenerator &QrSqlGenerator::colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7, const ColVal &colval8, const ColVal &colval9)
{
    return colvals(QrColValList() << colval1 << colval2 << colval3 << colval4 << colval5 << colval6 << colval7 << colval8 << colval9);
}

const QStringList &QrSqlGenerator::columns() const
{
    Q_D(const QrSqlGenerator);
    return d->listColumns;
}

QString QrSqlGenerator::columnsToString(const QStringList &values) const
{
    QString statement;
    if (values.empty ()) {
        return statement;
    }

    statement += "(";
    for (int idx = 0; idx < values.count (); ++idx) {
        statement += (0==idx) ? "" : ", ";
        statement += values.at(idx);
    }
    statement += ")";

    return statement;
}

QrSqlGenerator &QrSqlGenerator::columns(const QStringList &listColumns)
{
    Q_D(QrSqlGenerator);
    d->listColumns = listColumns;
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1)
{
    return columns(QStringList() << column1);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2)
{
    return columns(QStringList() << column1 << column2);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3)
{
    return columns(QStringList() << column1 << column2 << column3);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4)
{
    return columns(QStringList() << column1 << column2 << column3 << column4);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5)
{
    return columns(QStringList() << column1 << column2 << column3 << column4 << column5);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6)
{
    return columns(QStringList() << column1 << column2 << column3 << column4 << column5 << column6);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7)
{
    return columns(QStringList() << column1 << column2 << column3 << column4 << column5 << column6 << column7);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7, const QString &column8)
{
    return columns(QStringList() << column1 << column2 << column3 << column4 << column5 << column6 << column7 << column8);
}

QrSqlGenerator &QrSqlGenerator::columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7, const QString &column8, const QString &column9)
{
    return columns(QStringList() << column1 << column2 << column3 << column4 << column5 << column6 << column7 << column8 << column9);
}

const QVector<QVariantList> &QrSqlGenerator::values() const
{
    Q_D(const QrSqlGenerator);
    return d->listValueses;
}

const QVariantList &QrSqlGenerator::firstValues() const
{
    Q_D(const QrSqlGenerator);
    if (d->listValueses.isEmpty ()) {
        return QrSqlGeneratorPrivate::emptyValues;
    }
    return d->listValueses.first ();
}

QString QrSqlGenerator::valuesToString(const QVariantList &values) const
{
    QString statement;
    if (values.empty ()) {
        return statement;
    }

    statement += "(";
    for (int idx = 0; idx < values.count (); ++idx) {
        statement += (0==idx) ? "" : ", ";
        statement += "'" + values.at(idx).toString () + "'";
    }
    statement += ")";

    return statement;
}

QrSqlGenerator &QrSqlGenerator::values(const QVariantList &listValues)
{
    Q_D(QrSqlGenerator);
    d->listValueses.push_back (listValues);
    return (* this);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1)
{
    return values(QVariantList() << value1);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2)
{
    return values(QVariantList() << value1 << value2);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3)
{
    return values(QVariantList() << value1 << value2 << value3);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4)
{
    return values(QVariantList() << value1 << value2 << value3 << value4);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5)
{
    return values(QVariantList() << value1 << value2 << value3 << value4 << value5);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6)
{
    return values(QVariantList() << value1 << value2 << value3 << value4 << value5 << value6);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7)
{
    return values(QVariantList() << value1 << value2 << value3 << value4 << value5 << value6 << value7);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7, const QVariant &value8)
{
    return values(QVariantList() << value1 << value2 << value3 << value4 << value5 << value6 << value7 << value8);
}

QrSqlGenerator &QrSqlGenerator::values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7, const QVariant &value8, const QVariant &value9)
{
    return values(QVariantList() << value1 << value2 << value3 << value4 << value5 << value6 << value7 << value8 << value9);
}

QrSqlGenerator &QrSqlGenerator::setTable(QrSqlTable *value)
{
    Q_D(QrSqlGenerator);
    d->sqlTable = value;
    return (* this);
}

bool QrSqlGenerator::isFilterProperty(const QString &propertyName)  {
    return QrSqlTable::pkIdName() == propertyName
            || "objectName" == propertyName ;
}

QrSqlQuery QrSqlGenerator::getSqlQuery()
{
    return QrSqlQuery(getSqlStatement());
}

QrSqlTable *QrSqlGenerator::getTable() const
{
    Q_D(const QrSqlGenerator);
    return d->sqlTable;
}
