#ifndef QRSQLELEMENT_H
#define QRSQLELEMENT_H

#include <QtCore/qstringlist.h>
#include <QtCore/qvariant.h>

#include "qrorm_global.h"

NS_QRORM_BEGIN

/*!
 * common interface for all SQL elements to build SQL query
 */
class QRORMSHARED_EXPORT QrSqlElement {
public:
    QrSqlElement(int _index);

public:
    virtual QString toString() const = 0;
    virtual void clone(QrSqlElement * other);

public:
    void setColumn(const QString & column);
    void setColumns(const QStringList & columns);
    void setValue(const QVariant & val);
    void setValues(const QVariantList & values);

protected:
    void updateKeys();

protected:
    int index;  //    Index of SQL element to build unique string
    QStringList listColumns;         // List of columns associated to SQL element
    QStringList listKeys;            // List of keys associated to SQL element
    QList<QVariant> listValues;      // List of values associated to SQL element
};

NS_QRORM_END

#endif // QRSQLELEMENT_H
