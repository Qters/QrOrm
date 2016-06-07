#ifndef QRSQLTABLE_H
#define QRSQLTABLE_H

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qpair.h>
#include <QtCore/qvariant.h>

#include "qrorm_global.h"

NS_QRORM_BEGIN

/*!
 *  table in database, would be use in table generator to generate sql statement,
 *  every table entity shoube be extend this class.
 */
class QRORMSHARED_EXPORT QrSqlTable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(long pk_id READ getPkId WRITE setPkId)

public:
    static QString pkIdName();

public:
    /*!
     * \brief dump all member values of object
     */
    virtual void dumpValues();

public:
    virtual QString tableName() const = 0;

public:
    virtual void addCustomizedDBVals(const QPair<QString, QVariant>& selfval);
    virtual void addCustomizedDBVals(const QString& selfkey, const QVariant& selfval);
    const QList<QPair<QString, QVariant> >& getCustomizedVals() const;

    virtual long getPkId() const final;
    virtual void setPkId(long value) final;

protected:
    long pk_id;

private:
    QList<QPair<QString, QVariant> > customizedDbVals;  //  user customized values in sql query, no exist in db table, such as "count(*), col1 + col2, and so on ...
};

NS_QRORM_END

#endif // QRSQLTABLE_H
