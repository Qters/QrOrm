#ifndef QRSQLISNULL_H
#define QRSQLISNULL_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

/*!
 * \brief SQL element to verify if a value is null or not null (IS NULL, IS NOT NULL)
 */
class QRORMSHARED_EXPORT QrSqlIsNull : public QrSqlElement
{
public:
    enum NullType { is_null, is_not_null };

public:
    QrSqlIsNull();
    QrSqlIsNull(int _index, QrSqlIsNull::NullType _type);

    // QrSqlElement interface
public:
    virtual QString toString() const;

protected:
    QrSqlIsNull::NullType type;
};

NS_QRORM_END

#endif // QRSQLISNULL_H
