#include "generator/qrinsertsql.h"

#include <QtCore/qmetaobject.h>
#include <QtCore/qdebug.h>

#include "entity/qrsqltable.h"

USING_NS_QRORM;

QString QrInsertSql::getSqlStatement()
{
    Q_ASSERT(!getTable()->tableName().isEmpty());

    QStringList columns_ = columns ();
    QVariantList values_ = firstValues ();

    if (columns_.isEmpty () && values_.isEmpty ()) {    //  insert values in all member variable
        int propCount = getTable()->metaObject ()->propertyCount ();
        for (int propIdx=0; propIdx<propCount; ++propIdx) {
            auto metaPropName = getTable()->metaObject ()->property(propIdx).name();
            if (QrSqlGenerator::isFilterProperty(getTable(), QString(metaPropName))) {
                continue;
            }
            columns_.push_back (QString(metaPropName));
            values_.push_back (getTable ()->property(metaPropName));
        }
    }

    if (values_.isEmpty ()) {
        qDebug() << "values is empty.";
        return "";
    }

    QString sql =  "INSERT INTO " + getTable()->tableName() + " ";
    if (! columns_.isEmpty()) {
        sql += columnsToString (columns_);
    }
    sql += " VALUES " + valuesToString (values_);

    const QVector<QVariantList> &moreValues = values ();
    for (int valIdx = 1; valIdx < moreValues.count (); ++valIdx) {
        sql += ", " + valuesToString (moreValues.at (valIdx));
    }

    sql += ";";

    return sql;
}
