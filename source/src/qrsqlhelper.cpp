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
#include "generator/qrcreatesql.h"

USING_NS_QRORM;

QSqlError QrSqlHelper::call_query(QrSqlQuery &query, QSqlDatabase *database /* = nullptr */)
{
    QSqlError dbError;
    if (dbError.isValid()) {
        return dbError;
    }

    QSqlQuery qQuery = QSqlQuery(*database);
    qQuery.setForwardOnly(true);

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
    //  set is print sql query statement or not
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
    qDebug() << "check database " << dbPath;
    if (! QrCommon::QrFiler::fileExists (dbPath)) {
        qDebug() << "database is not exist";
        return false;
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

    qDebug() << "open database...";
    bool success = false;
    if (newDatabase.open()) {
        success = true;
    } else {
        qDebug() << "Database create fail:" << newDatabase.lastError().text();
    }

    newDatabase.close();

    return success;
}

bool QrSqlHelper::makesureTableExist(QrSqlTable *table, QrSqlDatabase *database)
{
    QrCreateSql createSql;
    auto error = QrSqlHelper::call_query(createSql.setTable(table).getSqlQuery(), &database->getDatabase());
    if (error.isValid()) {
        qWarning() << "could't create " << table->tableName() << ", " << error.text();
        return false;
    }

    return true;
}
