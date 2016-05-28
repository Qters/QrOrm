#ifndef QRSQLTABLEINFO_H
#define QRSQLTABLEINFO_H

#include "qrorm_global.h"
#include "entity/qrsqltable.h"

namespace Qters {

namespace QrOrm {

/*!
 * \brief PRAGMA table_info('testTable');
 */

class QRORMSHARED_EXPORT QrSqlTableInfo : public QrSqlTable
{
public:
    Q_OBJECT
    Q_PROPERTY(int cid READ getCid WRITE setCid)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString type READ getType WRITE setType)
    Q_PROPERTY(bool notnull READ getNotnull WRITE setNotnull)
    Q_PROPERTY(QVariant dfltValue READ getDfltValue WRITE setDfltValue)
    Q_PROPERTY(bool pk READ getPk WRITE setPk)


public:
    QrSqlTableInfo() = default;

public:
    virtual QString tableName() const { return "table_info"; }

    bool getPk() const;
    void setPk(bool value);

    QVariant getDfltValue() const;
    void setDfltValue(const QVariant &value);

    bool getNotnull() const;
    void setNotnull(bool value);

    QString getType() const;
    void setType(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getCid() const;
    void setCid(int value);

private:
    int cid	;
    QString name;
    QString type;
    bool notnull;
    QVariant dfltValue;
    bool pk;

};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLTABLEINFO_H
