#ifndef QRSQLLIMIT_H
#define QRSQLLIMIT_H

#include "qrorm_global.h"
#include "generator/element/qrsqlelement.h"

namespace Qters {

namespace QrOrm {

class QRORMSHARED_EXPORT QrSqlLimit : public QrSqlElement
{
public:
    QrSqlLimit();
    QrSqlLimit(int _index);

public:
    int getStartRow() const;
    int getRowsCount() const;
    int getMaxRow() const;

    QString getStartRow_ParamKey() const;
    QString getRowsCount_ParamKey() const;
    QString getMaxRow_ParamKey() const;

    // QrSqlElement interface
public:
    virtual QString toString() const;
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLLIMIT_H
