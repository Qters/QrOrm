#ifndef QRSQLELEMENTTEMP_H
#define QRSQLELEMENTTEMP_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

namespace Qters {

namespace QrOrm {

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

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLELEMENTTEMP_H
