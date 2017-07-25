#ifndef TST_ORM_H
#define TST_ORM_H

#include "qrtestsuitefactory.h"

#include "entity/qrsqldatabase.h"
#include "entity/qrsqltable.h"

QT_BEGIN_NAMESPACE
class QSqlDatabase;
QT_END_NAMESPACE

class tst_db : public Qters::QrOrm::QrSqlDatabase
{
private:
    tst_db();
public:
    virtual ~tst_db() = default;
public:
    static tst_db* instance();
};

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
    double getPrice() const;
    void setPrice(double value);

    QString getKey() const;
    void setKey(const QString &value);

    QString getValue() const;
    void setValue(const QString &value);

private:
    QString key;
    QString value;
    double price;
};

class TESTSUITE(tst_orm) : public QObject
{
    Q_OBJECT

private slots:
    void go();

private:
    void autoCreateDatabase();
    void createTable(QSqlDatabase *database);
    void insert(QSqlDatabase *database);
    void select(QSqlDatabase *database);
    void update(QSqlDatabase *database);
    void _delete(QSqlDatabase *database);
    void checkError(QSqlError error);
    void insertRow(tst_table *table, QSqlDatabase *database);
};

#endif // TST_ORM_H
