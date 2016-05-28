#ifndef QRSELECTSQL_H
#define QRSELECTSQL_H

#include "generator/qrsqlgenerator.h"

namespace Qters {

namespace QrOrm {

/*!
 * QrSqlTable table;
 * bool suc = false;
 *
 * suc = QrSelectSql().setTable(&table).columns("c1","c2").where("c3").isEqualTo(v3).and_("c4").isGreaterThan(v4).orderAsc(c5, c6)
 * => select c1, c2 from table where c3=v3 and c4>=v4 order by c5, c6 asc;
 *
 * suc = QrSelectSql().setTable(&table).where("c1").isEqualTo(v1).and_("c2").isEqualTo(v2);
 * => select * from c1=v1 and c2=v2;
 *
 * suc => QRSelectSql().setTable(&table).columns("c1", "sum(c2)").groupby("c3", "c4").distinct();
 * => select distinct c1, sum(c2) from table group by c3, c4
 */
class QRORMSHARED_EXPORT QrSelectSql : public QrSqlGenerator
{
public:
    virtual ~QrSelectSql() = default;

    // QrSqlGenerator interface
public:
    virtual QString getSqlStatement();
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSELECTSQL_H
