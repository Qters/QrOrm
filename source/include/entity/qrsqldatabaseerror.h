#ifndef QRSQLDATABASEERROR_H
#define QRSQLDATABASEERROR_H

#include <QtSql/qsqldatabase.h>

#include "qrorm_global.h"

NS_QRORM_BEGIN

/*!
 * \brief show last error of database
 */
class QrSqlDatabaseError
{
public:
    static void displayLastError(const QSqlDatabase &db, const QString &description);
private:
    static QString formatLastError(const QSqlDatabase &db);
};

NS_QRORM_END

#endif // QRSQLDATABASEERROR_H
