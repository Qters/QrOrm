#ifndef QRSQLEMPTYTEXT_H
#define QRSQLEMPTYTEXT_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

namespace Qters {

namespace QrOrm {

/*!
 * \brief  possibility to add empty text to SQL query
 */
class QRORMSHARED_EXPORT QrSqlEmptyText: public QrSqlElement
{
public:
    QrSqlEmptyText();
    QrSqlEmptyText(int _index);

    // QrSqlElement interface
public:
    virtual QString toString() const;
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLEMPTYTEXT_H
