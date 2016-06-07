#ifndef QRSQLIN_H
#define QRSQLIN_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

class QRORMSHARED_EXPORT QrSqlIn : public QrSqlElement
{
public:
    enum InType { in, not_in, in_select, not_in_select };

public:
    QrSqlIn();
    QrSqlIn(int _index, QrSqlIn::InType _type);

    // QrSqlElement interface
public:
    virtual QString toString() const;

protected:
    QrSqlIn::InType type;
};

NS_QRORM_END

#endif // QRSQLIN_H
