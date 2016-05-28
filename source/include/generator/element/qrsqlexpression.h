﻿#ifndef QRSQLEXPRESSION_H
#define QRSQLEXPRESSION_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

namespace Qters {

namespace QrOrm {

/*!
 * \brief SQL element to build a SQL expression (WHERE, AND, OR, etc.)
 */
class QRORMSHARED_EXPORT QrSqlExpression: public QrSqlElement
{
public:
    enum ExpressionType { where, and_, or_, open_parenthesis, close_parenthesis };

public:
    QrSqlExpression();
    QrSqlExpression(int _index, QrSqlExpression::ExpressionType _type);

protected:
    QrSqlExpression::ExpressionType type;

    // SqlElement interface
public:
    virtual QString toString() const;
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLEXPRESSION_H
