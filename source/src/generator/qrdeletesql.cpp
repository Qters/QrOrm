#include "generator/qrdeletesql.h"

#include "entity/qrsqltable.h"

USING_NS_QRORM;

QString QrDeleteSql::getSqlStatement()
{
    Q_ASSERT(!getTable()->tableName().isEmpty());

    QString condition = getCondition();
    if (condition.isEmpty ()) {
        Q_ASSERT("condition is empty, would be erase all data in table!!");
        return "";  //  stop erase all, if want, append 1=1 or others
    }

    return  "DELETE FROM " + getTable()->tableName() + condition;
}
