#include "generator/qrupdatesql.h"

#include <QtCore/qdebug.h>

#include "entity/qrsqltable.h"

USING_NS_QRORM;

QString QrUpdateSql::getSqlStatement()
{
    QString condition = getCondition();
    if (condition.isEmpty ()) {
        Q_ASSERT("condition is empty, would be update all data in table!!");
        return "";  //  stop update all, if want, append 1=1 or others
    }

    Q_ASSERT(!getTable()->tableName().isEmpty());

    QStringList columns_ = columns ();
    QVariantList values_ = firstValues ();
    Q_ASSERT(columns_.count () == values_.count () );

    if (columns_.isEmpty ()
            || values_.isEmpty ()) {
        qDebug() << "columns or value is empty.";
        return "";
    }

    QString statement = "UPDATE " + getTable()->tableName() + " SET ";
    for (int idx = 0; idx < columns_.count (); ++idx) {
        statement += (0==idx) ? "" : ", ";
        statement += columns_.at (idx) + " = '" + values_.at (idx).toString () + "'";
    }

    statement += condition + ";";

    return statement;
}
