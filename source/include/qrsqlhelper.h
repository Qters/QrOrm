#ifndef QRSQLHELPER_H
#define QRSQLHELPER_H

#include <QtSql/qsqlerror.h>

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtCore/qdatetime.h>

#include "qrorm_global.h"

namespace Qters {

namespace QrOrm {

class QrSqlDatabase;
class QrSqlQuery;
class QrSqlTable;
class QrSelectSql;
class QrInsertSql;
class QrUpdateSql;
class QrDeleteSql;

class QRORMSHARED_EXPORT QrSqlHelper {
public:
    /*!
      * call_query function can be used to call a custom SQL query or a stored procedure
      *
      * Here is an example of code using call_query function :
      *     //  QrSqlQuery query("CALL MyStoredProc(:param1, :param2)");
      *     //  query.bind(":param1", "myValue1");
      *     //  query.bind(":param2", myValue2, QSql::InOut);
      *
      *     QrSelectSql selectSql;
      *     selectSql.setTable (&t_stock);
      *     QrSqlQuery query = selectSql.columns("stkid", "market").where ("stktype").isEqualTo ("0").limit (2).getSqlQuery ();
      *
      *     QSqlError daoError = call_query(query);
      *     //  QVariant newValue = query.boundValue(":param2");
      *     query.dumpSqlResult();
      *
      *     QrDbResultsGuard<TestQrTable> dbObjs;
      *     QList<TestQrTable*> results = dbObjs.fetchResultsBySqlQuery (query);
      *     Q_FOREACH(TestQrTable* result, results){
      *         TestQrTable::dumpValues (result);
      *     }
      */
    static QSqlError call_query(QrSqlQuery &query, QSqlDatabase *database = nullptr);
    /*!
      *
      */
    static bool makesureDbExist(QrSqlDatabase *database);
};

//template<typename T>
//static inline QSqlError fetch_all(const QrSqlQuery &query, T &t)
//{
//    contaniner.clear ();
//    contaniner.append ();
//    return QSqlError();
//}

}   //  namespace QrOrm

}   //  namespace Qters


#endif // QRSQLHELPER_H

