#include "entity/qrsqldatabase.h"

#include <QtCore/qdebug.h>
#include <QtCore/qthread.h>
#include <QtCore/quuid.h>
#include <QtWidgets/qapplication.h>
#include <QtSql/qsqlerror.h>

#include "auxiliary/qrconverter.h"
#include "auxiliary/qrispointer.h"
#include "auxiliary/qrfiler.h"

#include "entity/qrsqldatabaseerror.h"

USING_NS_QRORM;
USING_NS_QRCOMMON;

QSqlDatabase QrSqlDatabase::null = QSqlDatabase();

QSqlDatabase QrSqlDatabase::createDatabase(QSqlError &dbError)
{
    QString connectionName_ = connectionName();
    dbError = QSqlError();

    dbFileIsCreated = false;
    qDebug() << "create database:" << getDatabasePath () << "," << connectionName_;
    if (! QrFiler::fileExists (getDatabasePath ())) {
//        qDebug() << "database path is not exist:" << getDatabasePath ();
//        dbError = QSqlError("'database file is not exist!'", "", QSqlError::ConnectionError);
//        Q_ASSERT(false);
//        return QrSqlDatabase::null;
        dbFileIsCreated = true;
        qDebug() << "database file is not exist, ready to creating...";
    }

    const QrSqlDatabaseParams &params = getParams ();
    Q_ASSERT(!params.driverName.isEmpty () && !params.databaseName.isEmpty ());
    QSqlDatabase db = QSqlDatabase::addDatabase (params.driverName, connectionName_);
    db.setConnectOptions (params.connectOptions);
    db.setDatabaseName (getDatabasePath ());
    db.setUserName (params.username);
    db.setPassword (params.password);
    db.setHostName (params.hostname);
    if (-1 != params.port){
        db.setPort (params.port);
    }

    if (! db.open ()) {
        qDebug() << "fail to open database";
        QrSqlDatabaseError::displayLastError (db, "unable to open connection to database");
        dbError = db.lastError ();
        if (!dbError.isValid ()) {
            dbError = QSqlError("'unable to open connection to database'", "", QSqlError::UnknownError);
        }
        QSqlDatabase::removeDatabase (connectionName_);
        return QrSqlDatabase::null;
    }

    Qt::HANDLE curThreadIdHandle = QThread::currentThreadId ();
    listDbByThread.insert (curThreadIdHandle, connectionName_);

    QString curThreadId = QrStringCvter<Qt::HANDLE, QrIsPointer<Qt::HANDLE>::value>::toString (curThreadIdHandle);
    qDebug() << "create new database connection of " << params.databaseName
             << "in thread " << curThreadId << " with key " << connectionName_;

    return QSqlDatabase::database(connectionName_);
}

const QrSqlDatabaseParams& QrSqlDatabase::getParams() const
{
    return params;
}

void QrSqlDatabase::setParams(const QrSqlDatabaseParams &value)
{
    params = value;
}

QString QrSqlDatabase::connectionName()
{
    return params.databaseName +
            QrStringCvter<Qt::HANDLE, QrIsPointer<Qt::HANDLE>::value>::toString (QThread::currentThreadId ());
}

void QrSqlDatabase::callAfterSuccessCreateDatabase()
{

}

QString QrSqlDatabase::getDatabasePath() const
{
    QString root = QApplication::applicationDirPath ();
    if (root.isEmpty()) {
        root = ".";
    }
    return  root + "/" + params.folder +
            "/" + params.databaseName;
}

QSqlDatabase QrSqlDatabase::getDatabase()
{
    QSqlError dbError;
    Q_UNUSED(dbError);
    return getDatabase(dbError);
}

QSqlDatabase QrSqlDatabase::getDatabaseCloned()
{
    QSqlError dbError;
    Q_UNUSED(dbError);
    QString connectionName = QUuid::createUuid ().toString ();
    return QSqlDatabase::cloneDatabase (getDatabase (dbError), connectionName);
}

QSqlDatabase QrSqlDatabase::getDatabase(QSqlError &dbError)
{
    return getDatabaseByCurThreadId(dbError);
}

QSqlDatabase QrSqlDatabase::getDatabaseByCurThreadId(QSqlError &dbError)
{
//    QMutexLocker locker(&mutexDb);
    mutexDb.lock();
    dbError = QSqlError();

    Qt::HANDLE curThreadIdHandle = QThread::currentThreadId ();
    if (! curThreadIdHandle) {
        qDebug() << "unable to find current thread id";
        dbError = QSqlError("'unable to find current thread id'", "", QSqlError::UnknownError);
        Q_ASSERT(false);
        mutexDb.unlock();
        return QrSqlDatabase::null;
    }

    if (! listDbByThread.contains (curThreadIdHandle)) {
        auto db = createDatabase (dbError);
        mutexDb.unlock();
        if(dbFileIsCreated) {
            callAfterSuccessCreateDatabase();
        }
        return db;
    }

    QString connectionName = listDbByThread.value (curThreadIdHandle);
    if (! QSqlDatabase::contains (connectionName)) {
        auto db = createDatabase (dbError);
        mutexDb.unlock();
        if(dbFileIsCreated) {
            callAfterSuccessCreateDatabase();
        }
        return db;
    }

    auto db = QSqlDatabase::database (connectionName);
    mutexDb.unlock();
    return db;
}
