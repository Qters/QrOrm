#ifndef QRCREATESQL_H
#define QRCREATESQL_H

#include "generator/qrsqlgenerator.h"

namespace Qters {

namespace QrOrm {

/*!
 * \brief PRIMARY KEY was setting by QrSqlTable::pkIdName(), it would be auto increment
 */
class QRORMSHARED_EXPORT QrCreateSql : public QrSqlGenerator
{
public:
    virtual ~QrCreateSql() = default;

    // QrSqlGenerator interface
protected:
    virtual QString getSqlStatement() ;

private:
    QString getVariantType(const QVariant &variant) const;
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRCREATESQL_H
