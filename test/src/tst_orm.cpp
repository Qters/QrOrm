#include "tst_orm.h"

#include "qrsqlhelper.h"
#include "generator/qrcreatesql.h"
#include "generator/qrselectsql.h"
#include "generator/qrinsertsql.h"
#include "generator/qrupdatesql.h"
#include "generator/qrdeletesql.h"
#include "qrdbresultsguard.h"
#include "entity/qrsqlconfig.h"

USING_NS_QRORM;

tst_db::tst_db()
    : QrSqlDatabase()
{
    static QrSqlDatabaseParams param;
    param.driverName = "QSQLITE";
    param.databaseName = "tst_db.db";
    setParams (param);
}

tst_db *tst_db::instance()
{
    static tst_db* instance = new tst_db();
    return instance;
}

void tst_orm::go()
{
    QrSqlConfig::getInstance()->setTraceSqlQuery(true);
    autoCreateDatabase();

    auto database = tst_db::instance()->getDatabase();

    createTable(&database);
    insert(&database);
    select(&database);
    update(&database);
    _delete(&database);
}

void tst_orm::autoCreateDatabase()
{
    Q_ASSERT(QrSqlHelper::makesureDbExist(tst_db::instance()));
}

void tst_orm::createTable(QSqlDatabase *database)
{
    tst_table table;

    QrCreateSql createSql;
    checkError(QrSqlHelper::call_query(
                   createSql.setTable(&table).getSqlQuery(),
                   database));
}

void tst_orm::insert(QSqlDatabase *database)
{
    tst_table firstRecord;
    firstRecord.setKey("2");
    firstRecord.setValue("first");
    firstRecord.setPrice(1.1);

    tst_table secondRecord;
    secondRecord.setKey("2");
    secondRecord.setValue("second");
    secondRecord.setPrice(2.2);

    tst_table thirdRecord;
    thirdRecord.setKey("3");
    thirdRecord.setValue("third");
    thirdRecord.setPrice(3.3);

    insertRow(&firstRecord, database);
    insertRow(&secondRecord, database);
    insertRow(&thirdRecord, database);
}

void tst_orm::select(QSqlDatabase *database)
{
    tst_table table;
    QrSelectSql select;
    auto query = select.setTable(&table)
            .columns("*")
            .where("key").isEqualTo("2")
            .limit(2).getSqlQuery();
    checkError(QrSqlHelper::call_query(query, database));

    qDebug() << "\nsql results:";
    query.dumpSqlResult();

    qDebug() << "\nobject reflection results:";
    QrDbResultsGuard<tst_table> dbObjs;
    Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
        result->dumpValues();
    }
}

void tst_orm::update(QSqlDatabase *database)
{
    tst_table table;

    QrUpdateSql update;
    checkError(QrSqlHelper::call_query(
                update.setTable(&table)
                .colvals(qMakePair<QString, QVariant>("value", "update"))
                .where("key").isEqualTo("3").getSqlQuery(),
                database));
}

void tst_orm::_delete(QSqlDatabase *database)
{
    tst_table table;

    QrDeleteSql _delete;
    checkError(QrSqlHelper::call_query(
                _delete.setTable(&table)
                .where("key").isEqualTo("2")
                .and_("value").isEqualTo("second").getSqlQuery(),
                database));
}

void tst_orm::insertRow(tst_table *table, QSqlDatabase *database)
{
    QrInsertSql insert;
    checkError(QrSqlHelper::call_query(
                   insert.setTable(table)
                   .getSqlQuery(),
                   database));
}

void tst_orm::checkError(QSqlError error)
{
    if (error.isValid()) {
        qDebug() <<  error.text();
        Q_ASSERT(false);
    }
}

double tst_table::getPrice() const
{
    return price;
}

void tst_table::setPrice(double value)
{
    price = value;
}

QString tst_table::getKey() const
{
    return key;
}

void tst_table::setKey(const QString &value)
{
    key = value;
}

QString tst_table::getValue() const
{
    return value;
}

void tst_table::setValue(const QString &value)
{
    this->value = value;
}
