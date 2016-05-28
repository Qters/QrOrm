#ifndef QRSQLDATABASEERROR_H
#define QRSQLDATABASEERROR_H

#include <QtSql/qsqldatabase.h>

namespace Qters {

namespace QrOrm {

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

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLDATABASEERROR_H
