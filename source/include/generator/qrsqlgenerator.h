#ifndef QRSQLGENERATOR_H
#define QRSQLGENERATOR_H

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>
#include <QtCore/qsharedpointer.h>

#include "qrglobal.h"
#include "qrorm_global.h"
#include "entity/qrsqlquery.h"
#include "generator/element/qrsqlin.h"
#include "generator/element/qrsqlsort.h"
#include "generator/element/qrsqlisnull.h"
#include "generator/element/qrsqlelement.h"
#include "generator/element/qrsqlcompare.h"
#include "generator/element/qrsqlisbetween.h"
#include "generator/element/qrsqlexpression.h"

NS_QRORM_BEGIN

class QrSqlTable;
class QrSqlGeneratorPrivate;

/*!
 * \brief
 * condition's part:
 * 1. what's condition: where like.
 *
 * 2. how to use:
 *  xxxsql.where("sex").isEqualTo("female")
 *          .and_("age").isGreaterThan(38)
 *          .or_("last_name").isNotEqualTo("Dupont")
 *          .or_("first_name").like("Alfred")
 *          .and_OpenParenthesis("id").isLessThanOrEqualTo(999)
 *          .and_("birth_date").isBetween(queryDT1, queryDT2)
 *          .closeParenthesis()
 *          .or_("id").in(50, 999, 11, 23, 78945)
 *          .and_("is_deleted").isNotNull()
 *          .orderAsc("last_name", "first_name", "sex")
 *          .limit(50, 150)
 *
 * 3. functions to generator sql statement:
 *  where (QString)
 *  and_ (QString)
 *  or_ (QString)
 *  where_OpenParenthesis (QString)
 *  and_OpenParenthesis (QString)
 *  or_OpenParenthesis (QString)
 *  openParenthesis ()
 *  closeParenthesis ()
 *
 *  isEqualTo (QVariant)
 *  isNotEqualTo (QVariant)
 *  isGreaterThan (QVariant)
 *  isGreaterThanOrEqualTo (QVariant)
 *  isLessThan (QVariant)
 *  isLessThanOrEqualTo (QVariant)
 *
 *  isBetween (QVariant,QVariant)
 *  isNotBetween (QVariant,QVariant)
 *
 *  orderAsc (QString...)
 *  orderDesc (QString...)
 *  groupBy (QString...)
 *  in (QVariant...)
 *  notIn (QVariant...)
 *
 * 4. functions to get attribute or value:
 * getCondition()
 * distinct()
 *
 * base info part:
 * 1. what's base: like columns, values, colvals(column and value) functions in select, insert and update sql.
 *
 * 2. how to use:
 *  xxxsql.values("v1","v2","v3");
 *  xxxsql.columns("c1","c2","c3").values("v1","v2","v3");
 *  xxxsql.colvals(<"c1","v1">,<"c2","v2">,<"c3","v3">);
 *
 * 3. functions to generator sql statement:
 *  colvals(QPair<QString, QVariant>...)
 *  columns(String...)
 *  values(QVarient...)
 *
 */
class QRORMSHARED_EXPORT QrSqlGenerator
{
    QR_DECLARE_PRIVATE(QrSqlGenerator)

public:
    static bool isFilterProperty(const QString& propertyName) ;

public:
    QrSqlGenerator();
    virtual ~QrSqlGenerator() = default;

    //  ColVals
public:
    typedef QPair<QString, QVariant> ColVal;
    typedef QList<ColVal> QrColValList;

public:
    QrSqlGenerator & setTable(QrSqlTable *value);
    virtual QrSqlQuery getSqlQuery();

    //  to generate sql conditions's statement
public:
    virtual QrSqlGenerator &distinctize();

    virtual QrSqlGenerator &where(const QString & column);
    virtual QrSqlGenerator &and_(const QString & column);
    virtual QrSqlGenerator &or_(const QString & column);
    virtual QrSqlGenerator &where_OpenParenthesis(const QString & column);
    virtual QrSqlGenerator &and_OpenParenthesis(const QString & column);
    virtual QrSqlGenerator &or_OpenParenthesis(const QString & column);
    virtual QrSqlGenerator &openParenthesis();
    virtual QrSqlGenerator &closeParenthesis();

    virtual QrSqlGenerator &limit(int rowsCount, int startRow = 0);

    virtual QrSqlGenerator &like(const QString & val);
    virtual QrSqlGenerator &notLike(const QString & val);
    virtual QrSqlGenerator &startsWith(const QString & val);
    virtual QrSqlGenerator &endsWith(const QString & val);
    virtual QrSqlGenerator &containsString(const QString & val);

    virtual QrSqlGenerator &isEqualTo(const QVariant & val);
    virtual QrSqlGenerator &isNotEqualTo(const QVariant & val);
    virtual QrSqlGenerator &isGreaterThan(const QVariant & val);
    virtual QrSqlGenerator &isGreaterThanOrEqualTo(const QVariant & val);
    virtual QrSqlGenerator &isLessThan(const QVariant & val);
    virtual QrSqlGenerator &isLessThanOrEqualTo(const QVariant & val);

    virtual QrSqlGenerator &isBetween(const QVariant & val1, const QVariant & val2);
    virtual QrSqlGenerator &isNotBetween(const QVariant & val1, const QVariant & val2);

    virtual QrSqlGenerator &orderAsc(const QStringList & columns);
    virtual QrSqlGenerator &orderAsc(const QString & col1);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
    virtual QrSqlGenerator &orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

    virtual QrSqlGenerator &orderDesc(const QStringList & columns);
    virtual QrSqlGenerator &orderDesc(const QString & col1);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
    virtual QrSqlGenerator &orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

    virtual QrSqlGenerator &groupBy(const QStringList &columns);
    virtual QrSqlGenerator &groupBy(const QString & col1);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
    virtual QrSqlGenerator &groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

    virtual QrSqlGenerator &in(const QVariantList & values);
    virtual QrSqlGenerator &in(const QVariant & val1);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
    virtual QrSqlGenerator &in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

    virtual QrSqlGenerator &notIn(const QVariantList & values);
    virtual QrSqlGenerator &notIn(const QVariant & val1);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
    virtual QrSqlGenerator &notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

    //  to generate sql base's statement
public:
    /*!
     * \brief   ColVals
     * for sql generator interface like :
     *
     * insert.colvals(<c1,v1>)
     * insert.colvals(<c1,v1>,<c2,v2>)
     * => insert into table (c1,c2,c3) values (v1,v2,v3)
     * ...
     *
     * update.colvals(<c1,v1>)
     * update.colvals(<c1,v1>,<c2,v2>)
     * => update table set c1=v1, c2=v2;
     * ...
     *
     * and so on..
     */
    QrSqlGenerator &colvals(const QrColValList& listColvals_);
    QrSqlGenerator &colvals(const ColVal &colval1);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7, const ColVal &colval8);
    QrSqlGenerator &colvals(const ColVal &colval1, const ColVal &colval2, const ColVal &colval3, const ColVal &colval4, const ColVal &colval5, const ColVal &colval6, const ColVal &colval7, const ColVal &colval8, const ColVal &colva9);

    /*!
     * \brief   Columns
     * for sql generator interface like :
     *
     * insert.columns(c1)
     * insert.columns(c1,c2)
     * ...
     *
     * update.columns(c1)
     * update.columns(c1,c2)
     * ...
     *
     * and so on..
     */
    QrSqlGenerator &columns(const QStringList& listColumns);
    QrSqlGenerator &columns(const QString &column1);
    QrSqlGenerator &columns(const QString &column1, const QString &column2);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7, const QString &column8);
    QrSqlGenerator &columns(const QString &column1, const QString &column2, const QString &column3, const QString &column4, const QString &column5, const QString &column6, const QString &column7, const QString &column8, const QString &column9);

    /*!
     * \brief   Values
     * for sql generator interface like :
     *
     * insert.values(v1)
     * insert.values(v1,v2)
     * ...
     *
     * update.values(v1)
     * update.values(v1,v2)
     * ...
     *
     * and so on..
     */
    QrSqlGenerator &values(const QVariantList& listValues_);
    QrSqlGenerator &values(const QVariant &value1);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7, const QVariant &value8);
    QrSqlGenerator &values(const QVariant &value1, const QVariant &value2, const QVariant &value3, const QVariant &value4, const QVariant &value5, const QVariant &value6, const QVariant &value7, const QVariant &value8, const QVariant &value9);

    //  condition's function
protected:
    bool distinct () const ;
    QString getCondition();

    //  base's function
protected:
    //  ColVals
    QPair<QStringList, QVariantList> colvalsSperate(const QrSqlGenerator::QrColValList &colvals_) const;
    QPair<QString, QString> colvalsToString(const QrSqlGenerator::QrColValList& colvals) const;
    //  Columns
    const QStringList& columns() const;
    QString columnsToString(const QStringList& values) const;
    //  Values
    const QVariantList& firstValues() const;
    const QVector<QVariantList>& values() const;
    QString valuesToString(const QVariantList& values) const;

    //  extra part
protected:
    /**
     * @brief create sql statement for select, insert, update, delete
     * @return  sql statement
     */
    virtual QString getSqlStatement() = 0 ;
    QrSqlTable *getTable() const;

    //  condition's function
private:
    QrSqlGenerator &addSqlExpression(const QString & column, QrSqlExpression::ExpressionType type);
    QrSqlGenerator &addSqlCompare(const QVariant & val, QrSqlCompare::CompareType type);
    QrSqlGenerator &addSqlSort(const QStringList & columns, QrSqlSort::SortType type);
    QrSqlGenerator &addSqlIn(const QVariantList & values, QrSqlIn::InType type);
    QrSqlGenerator &addSqlIsNull(QrSqlIsNull::NullType type);
    QrSqlGenerator &addSqlIsBetween(const QVariant & val1, const QVariant & val2, QrSqlIsBetween::BetweenType type);
};

NS_QRORM_END

#endif // QRSQLGENERATOR_H
