#ifndef QRSQLELEMENTTEMP_H
#define QRSQLELEMENTTEMP_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

/*!
 * \brief temporary SQL element (need to be cloned to be used)
 */
class QRORMSHARED_EXPORT QrSqlElementTemp: public QrSqlElement
{
public:
    QrSqlElementTemp();

    // QrSqlElement interface
public:
    virtual QString toString() const;
};

NS_QRORM_END

#endif // QRSQLELEMENTTEMP_H
