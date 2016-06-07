#include "entity/qrsqldatabaseerror.h"

#include <QtCore/qdebug.h>
#include <QtSql/qsqlerror.h>

USING_NS_QRORM;

void QrSqlDatabaseError::displayLastError(const QSqlDatabase &db, const QString &description)
{
    QString sLastError = QrSqlDatabaseError::formatLastError(db);
    if (description.isEmpty()) {
        qDebug() << sLastError;
    } else {
        qDebug() << description << "\n" << sLastError;
    }
}

QString QrSqlDatabaseError::formatLastError(const QSqlDatabase &db)
{
    QString sLastError;

    if (-1 != db.lastError().number() ) {
        sLastError += QString("Error number '") + QString::number(db.lastError().number()) + QString("' : ");
    }
    if (! db.lastError().text().isEmpty()) {
        sLastError += db.lastError().text();
    } else {
        sLastError += "<no error description>";
    }

    return sLastError;
}
