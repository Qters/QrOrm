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

    if (! QrFiler::fileExists (getDatabasePath ())) {
        dbError = QSqlError("'database file is not exist!'", "", QSqlError::ConnectionError);
        Q_ASSERT(false);
        return QrSqlDatabase::null;
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

void QrSqlDatabase::setFolderPath(const QString &folderPath)
{
    params.folder = folderPath;
}

QString QrSqlDatabase::connectionName() const
{
    return params.databaseName +
            QrStringCvter<Qt::HANDLE, QrIsPointer<Qt::HANDLE>::value>::toString (QThread::currentThreadId ());
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
    QMutexLocker locker(&mutexDb);
    dbError = QSqlError();

    Qt::HANDLE curThreadIdHandle = QThread::currentThreadId ();
    if (! curThreadIdHandle) {
        qDebug() << "unable to find current thread id";
        dbError = QSqlError("'unable to find current thread id'", "", QSqlError::UnknownError);
        Q_ASSERT(false);
        return QrSqlDatabase::null;
    }

    if (! listDbByThread.contains (curThreadIdHandle)) {
        return createDatabase (dbError);
    }

    QString connectionName = listDbByThread.value (curThreadIdHandle);
    if (! QSqlDatabase::contains (connectionName)) {
        return createDatabase (dbError);
    }

    return QSqlDatabase::database (connectionName);
}
