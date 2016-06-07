#ifndef QRINSERTSQL_H
#define QRINSERTSQL_H

#include "generator/qrsqlgenerator.h"

NS_QRORM_BEGIN

/*!
 * QrSqlTable table;
 * bool suc = false;
 *
 * suc = QrInsertSql().setTable(&table).values("v1","v2","v3");
 * => insert into table values(v1, v2, v3);
 * *
 * suc = QrInsertSql().setTable(&table).columns("c1","c2","c3").values("v1","v2","v3");
 * suc = QrInsertSql().setTable(&table).colvals(<"c1","v1">,<"c2","v2">,<"c3","v3">);
 * => insert into table (c1,c2,c3) values (v1,v2,v3)
 *
 * if you want to insert all member variable values of object, that do like that:
 * suc = QrInsertSql().setTable(&table)
 * => insert into table (c1,...,cn) values(v1,...,vn)
 *
 */
class QRORMSHARED_EXPORT QrInsertSql : public QrSqlGenerator
{
public:
    virtual ~QrInsertSql() = default;

    // QrSqlGenerator interface
protected:
    virtual QString getSqlStatement();
};

NS_QRORM_END

#endif // QRINSERTSQL_H
