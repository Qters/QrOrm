#include "generator/qrselectsql.h"

#include "entity/qrsqltable.h"

USING_NS_QRORM;

QString QrSelectSql::getSqlStatement()
{
    Q_ASSERT(!getTable()->tableName().isEmpty());

    QString statement = "SELECT ";
    statement += (distinct () ? "DISTINCT " : "" );
    if (columns().isEmpty()) {
        statement += "* ";
    } else {
        for (int idx = 0; idx < columns ().count(); ++idx) {
            statement += (0==idx) ? "" : ", ";
            statement += columns ().at(idx);
        }
    }
    statement += " FROM " + getTable()->tableName();

    QString condition = getCondition();
    if (!condition.isEmpty ()) {
        statement += condition;
    }

    return statement+";";
}
