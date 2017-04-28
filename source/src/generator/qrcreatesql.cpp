#include "generator/qrcreatesql.h"

#include <QtCore/qmetaobject.h>
#include <QtCore/qdebug.h>

#include "entity/qrsqltable.h"

USING_NS_QRORM;

QString QrCreateSql::getSqlStatement()
{
    const QString tableName = getTable()->tableName();
    if (tableName.isEmpty()) {
        Q_ASSERT(false);
        return "";
    }

    QString createSql = "CREATE TABLE " + getTable()->tableName() +
            "( " + getTable()->pkIdName() + " INTEGER PRIMARY KEY AUTOINCREMENT, ";

    auto metaObject = getTable()->metaObject ();
    int count = metaObject->propertyCount ();
    for (int propertyIdx = 0; propertyIdx < count; ++propertyIdx) {
        QMetaProperty metaproperty = metaObject->property(propertyIdx);
        const QString metaPropName = QString(metaproperty.name());
        if (QrSqlGenerator::isFilterProperty(getTable(), metaPropName)) {
            continue;
        }
        createSql += metaPropName + " " + getVariantType(metaproperty.type());
        if (propertyIdx != count-1) {
            createSql += ", ";
        }
    }

    createSql += ");";

    return createSql;
}

QString QrCreateSql::getVariantType(const QVariant& variant) const {
    switch (variant.type ()) {
    case QVariant::ByteArray:
        return "BLOB";
    case QVariant::Bool:
    case QVariant::Int:
        return "INTEGER";
    case QVariant::Double:
    case QVariant::LongLong:
        return "BIGINT";
    case QVariant::UInt:
    case QVariant::ULongLong:
        return "UNSIGNED BIG INT";
    }

    return "TEXT";
}
