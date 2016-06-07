#ifndef QRDELETESQL_H
#define QRDELETESQL_H

#include "generator/qrsqlgenerator.h"

NS_QRORM_BEGIN

/*!
 * QrSqlTable table;
 * bool suc = false;
 *
 * suc = QrDeleteSql().setTable(&table).where("c1").isEqualTo(v1).and_("c2").isEqualTo(v2);
 * => delete from table where c1=v1 and c2=v2;
 */
class QRORMSHARED_EXPORT QrDeleteSql : public QrSqlGenerator
{
public:
    virtual ~QrDeleteSql() = default;

    // QrSqlGenerator interface
protected:
    virtual QString getSqlStatement() ;
};

NS_QRORM_END

#endif // QRDELETESQL_H
