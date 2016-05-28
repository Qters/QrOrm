**database structure**
```c++
class tst_db : public Qters::QrOrm::QrSqlDatabase
{
public:
    static tst_db* instance() {
		static tst_db* instance = new tst_db();
		return instance;
	}
	
private:
    tst_db() : QrSqlDatabase() {
		static QrSqlDatabaseParams param;
		param.driverName = "QSQLITE";
		param.databaseName = "tst_db.db";
		setParams (param);
	}
public:
    virtual ~tst_db() = default;
};
```


**table structure**
```c++
class tst_table : public Qters::QrOrm::QrSqlTable
{
public:
    Q_OBJECT
    Q_PROPERTY(QString key READ getKey WRITE setKey)
    Q_PROPERTY(QString value READ getValue WRITE setValue)
    Q_PROPERTY(double price READ getPrice WRITE setPrice)

public:
    virtual QString tableName() const { return "tst_table"; }

public:
    double getPrice() const { return price; }
    void setPrice(double value) { price = value; }

    QString getKey() const { return key; }
    void setKey(const QString &value) { key = value; }

    QString getValue() const { return value; }
    void setValue(const QString &value) { this->value = value; }

private:
    QString key;
    QString value;
    double price;
};
```

**create database**
```c++
QrSqlHelper::makesureDbExist(tst_db::instance())
```

**get database**
```c++
auto database = tst_db::instance()->getDatabase();
```

**create table**
```c++
tst_table tableStructure;
QrCreateSql createSql;
QrSqlHelper::call_query(
	createSql.setTable(&tableStructure).getSqlQuery(),
	&database);
```
	
**insert**
```c++
tst_table rowRecord;
rowRecord.setKey("2");
rowRecord.setValue("first");
rowRecord.setPrice(1.1);
QrInsertSql insertSql;
QrSqlHelper::call_query(
   insertSql.setTable(&rowRecord).getSqlQuery(),
   &database);
```
   
**select**
```c++
tst_table selectTable;
QrSelectSql selectSql;
auto query = 
	selectSql.setTable(&selectTable)
	.columns("*")
	.where("key").isEqualTo("2")
	.limit(2).getSqlQuery();
QrSqlHelper::call_query(query, &database);

qDebug() << "\nsql results:";
query.dumpSqlResult();

qDebug() << "\nobject reflection results:";
QrDbResultsGuard<tst_table> dbObjs;
Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
	result->dumpValues();
}
```

**update**
```c++
tst_table updateTable;
QrUpdateSql updateSql;
QrSqlHelper::call_query(
	updateSql.setTable(&updateTable)
	.colvals(qMakePair<QString, QVariant>("value", "update"))
	.where("key").isEqualTo("3").getSqlQuery(),
	&database);
```

**delete** 
```c++
tst_table deleteTable;
QrDeleteSql deleteSql;
QrSqlHelper::call_query(
	deleteSql.setTable(&deleteTable)
	.where("key").isEqualTo("2")
	.and_("value").isEqualTo("second").getSqlQuery(),
	&database);
```
