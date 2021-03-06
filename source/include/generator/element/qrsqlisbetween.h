﻿#ifndef QRSQLISBETWEEN_H
#define QRSQLISBETWEEN_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

/*!
 * \brief SQL element to verify if a value is included into 2 other values
 */
class QRORMSHARED_EXPORT QrSqlIsBetween: public QrSqlElement
{
public:
    enum BetweenType { is_between, is_not_between };

public:
    QrSqlIsBetween();
    QrSqlIsBetween(int _index, QrSqlIsBetween::BetweenType _type);

    // QrSqlElement interface
public:
    virtual QString toString() const;

protected:
    QrSqlIsBetween::BetweenType type;
};

NS_QRORM_END

#endif // QRSQLISBETWEEN_H
