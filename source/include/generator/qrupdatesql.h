#ifndef QRUPDATESQL_H
#define QRUPDATESQL_H

#include "generator/qrsqlgenerator.h"

NS_QRORM_BEGIN

/*!
 * QrSqlTable table;
 * bool suc = false;
 *
 * suc = QrUpdateSql().setTable(&table).columns("c1","c2","c3").values("v1","v2","v3").where(QString("c4=$1 and c5=$2").arg(v4).arg(v5));
 * suc = QrUpdateSql().setTable(&table).colvals(<"c1","v1">,<"c2","v2">,<"c3","v3">).where(QString("c4=$1 and c5=$2").arg(v4).arg(v5));
 * => update table set c1=v1, c2=v2, c3=v3 where c4=v4 and c5=v5;
 */
class QRORMSHARED_EXPORT QrUpdateSql : public QrSqlGenerator
{
public:
    virtual ~QrUpdateSql() = default;

    // QrSqlGenerator interface
protected:
    virtual QString getSqlStatement();
};

NS_QRORM_END

#endif // QRUPDATESQL_H
