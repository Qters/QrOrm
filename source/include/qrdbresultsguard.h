#ifndef QRDbResultsGuard_H
#define QRDbResultsGuard_H

#include <QtCore/qlist.h>
#include <QtCore/qscopedpointer.h>

#include "entity/qrsqlquery.h"

NS_QRORM_BEGIN

/*!
 *
 *  Use this class to make sure object will be release after use GetResultsBySqlQuery
 *  class type need to be sonclass of QrSQLTable
 */
template <typename CLASS_NAME>
class QrDbResultsGuard{
public:
    virtual ~QrDbResultsGuard();

public:
    QList<CLASS_NAME *> fetchResultsBySqlQuery(const QrSqlQuery& query);

private:
    void setResult(CLASS_NAME *result, const QString& columnName, const QVariant& value, const QList<QString>& propNames);

private:
    QList<CLASS_NAME *> container;
};

NS_QRORM_END

#include "qrdbresultsguard.inl"

#endif // QRDbResultsGuard_H
