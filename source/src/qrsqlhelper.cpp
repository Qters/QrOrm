#include "qrsqlhelper.h"

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qdebug.h>
#include <QtCore/qdir.h>
#include <QtWidgets/qapplication.h>

#include "auxiliary/qrfiler.h"

#include "entity/qrsqlquery.h"
#include "entity/qrsqldatabase.h"
#include "entity/qrsqlconfig.h"
#include "entity/qrsqltable.h"
#include "generator/qrselectsql.h"
#include "generator/qrinsertsql.h"
#include "generator/qrupdatesql.h"
#include "generator/qrdeletesql.h"

USING_NS_QRORM;

QSqlError QrSqlHelper::call_query(QrSqlQuery &query, QSqlDatabase *database /* = nullptr */)
{
    QSqlError dbError;
    if (dbError.isValid()) {
        return dbError;
    }

    //  set is print sql query statement or not
    QSqlQuery qQuery = QSqlQuery(*database);
    qQuery.setForwardOnly (true);

    QTime timeQuery;
    timeQuery.start ();
    qQuery.prepare (query.query ());
    query.resolve(qQuery);

    if (! qQuery.exec ()) {
        qDebug() << "query exec fail, " << query.query ();
        return qQuery.lastError ();
    }
    query.resolveOutput(qQuery, true);

    int ms = timeQuery.elapsed ();
    if (QrSqlConfig::getInstance ()->getTraceSqlQuery ()) {
        qDebug() << "custom sql query "<< "(" <<ms << " ms) : " << query.query ()
                 << " by " << database;
    }

    return QSqlError();
}

bool QrSqlHelper::makesureDbExist(QrSqlDatabase *database)
{
    if (nullptr == database) {
        qDebug() << "database is nullptr";
        return false;
    }

    const QString dbPath = database->getDatabasePath();
    if (QrCommon::QrFiler::fileExists (dbPath)) {
        return true;
    }

    QDir dbDir(database->getParams().folder);
    if (! dbDir.exists()) {
        QString parentFolder = QApplication::applicationDirPath ();
        if (parentFolder.isEmpty()) {
            parentFolder = ".";
        }
        QDir().mkdir( parentFolder + "/" + database->getParams().folder);
    }

    QSqlDatabase newDatabase = QSqlDatabase::addDatabase("QSQLITE");
    newDatabase.setDatabaseName(dbPath);

    bool success = false;
    if (newDatabase.open()) {
        success = true;
    } else {
        qDebug() << "Database create fail:" << newDatabase.lastError().text();
    }

    newDatabase.close();

    return success;
}
