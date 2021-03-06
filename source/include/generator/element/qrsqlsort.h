﻿#ifndef QRSQLSORT_H
#define QRSQLSORT_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

NS_QRORM_BEGIN

/*!
 * \brief SQL element to sort or to group list of elements fetched from database (ORDER BY, GROUP BY)
 */
class QRORMSHARED_EXPORT QrSqlSort : public QrSqlElement
{
public:
    enum SortType { order_asc, order_desc, group_by };

public:
    QrSqlSort();
    QrSqlSort(int _index, QrSqlSort::SortType _type);

    // QrSqlElement interface
public:
    virtual QString toString() const;

protected:
   QrSqlSort::SortType type;
};

NS_QRORM_END

#endif // QRSQLSORT_H
