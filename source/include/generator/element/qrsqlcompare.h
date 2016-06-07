#ifndef QRSQLCOMPARE_H
#define QRSQLCOMPARE_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

/*!
 * \brief SQL element to compare value (==, <, >, <=, >=, LIKE, NOT LIKE, etc.)
 */
class QRORMSHARED_EXPORT QrSqlCompare: public QrSqlElement
{
public:
    enum CompareType { is_equal_to, is_not_equal_to, is_greater_than,
                is_greater_than_or_equal_to, is_less_than, is_less_than_or_equal_to,
                like, not_like, starts_with, ends_with, contains_string };

public:
    QrSqlCompare();
    QrSqlCompare(int _index, QrSqlCompare::CompareType _type);

    // QrSqlElement interface
public:
    virtual QString toString() const;

protected:
    QrSqlCompare::CompareType type;

};

NS_QRORM_END

#endif // QRSQLCOMPARE_H
