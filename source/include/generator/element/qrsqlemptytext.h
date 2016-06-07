#ifndef QRSQLEMPTYTEXT_H
#define QRSQLEMPTYTEXT_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

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

NS_QRORM_END

#endif // QRSQLEMPTYTEXT_H
