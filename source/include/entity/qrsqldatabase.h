#ifndef QRSQLDATABASE_H
#define QRSQLDATABASE_H

#include <QtSql/qsqldatabase.h>
#include <QtCore/qhash.h>

#include "qrorm_global.h"
#include "singleton/qrsingleton.h"

namespace Qters {

namespace QrOrm {

/*!
 * \brief define all parameters to connect to database
 */
class QRORMSHARED_EXPORT QrSqlDatabaseParams{
public:
    QrSqlDatabaseParams():port(-1){}

public:
    int port;
    QString driverName;
    QString connectOptions;
    QString folder;
    QString databaseName;
    QString username;
    QString password;
    QString hostname;
};

/*!
 * \brief retrieve a valid connection of database by thread (this class is a singleton and is thread-safe)
 */
class QRORMSHARED_EXPORT QrSqlDatabase
{
public:
    QSqlDatabase getDatabase();
    QSqlDatabase getDatabaseCloned();
    QString getDatabasePath() const;

    const QrSqlDatabaseParams& getParams() const;
    void setParams(const QrSqlDatabaseParams &value);

protected:
    QrSqlDatabase() = default;
    virtual ~QrSqlDatabase() = default;

protected:
    virtual QString connectionName() const;

private:
    QSqlDatabase getDatabase(QSqlError & dbError);

private:
    QSqlDatabase getDatabaseByCurThreadId(QSqlError &dbError);
    QSqlDatabase createDatabase(QSqlError &dbError);

private:
    QMutex mutexDb;     //  Mutex => 'QrSqlDatabase' is thread-safe
    QHash<Qt::HANDLE, QString> listDbByThread;  //  collection of databases connexions by thread id
    QrSqlDatabaseParams params;

private:
    static QSqlDatabase null;   //  null object
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLDATABASE_H
