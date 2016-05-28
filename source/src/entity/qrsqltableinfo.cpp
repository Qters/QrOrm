#include "entity/qrsqltableinfo.h"

using namespace Qters::QrOrm;

bool QrSqlTableInfo::getPk() const
{
    return pk;
}

void QrSqlTableInfo::setPk(bool value)
{
    pk = value;
}

QVariant QrSqlTableInfo::getDfltValue() const
{
    return dfltValue;
}

void QrSqlTableInfo::setDfltValue(const QVariant &value)
{
    dfltValue = value;
}

bool QrSqlTableInfo::getNotnull() const
{
    return notnull;
}

void QrSqlTableInfo::setNotnull(bool value)
{
    notnull = value;
}

QString QrSqlTableInfo::getType() const
{
    return type;
}

void QrSqlTableInfo::setType(const QString &value)
{
    type = value;
}

QString QrSqlTableInfo::getName() const
{
    return name;
}

void QrSqlTableInfo::setName(const QString &value)
{
    name = value;
}

int QrSqlTableInfo::getCid() const
{
    return cid;
}

void QrSqlTableInfo::setCid(int value)
{
    cid = value;
}
