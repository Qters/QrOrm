#include "entity/qrsqlquery.h"

#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>
#include <QtCore/qdebug.h>

#include "entity/qrsqldatabase.h"
#include "entity/qrsqlconfig.h"

USING_NS_QRORM;

QrSqlQuery::QrSqlQuery(const QString& _queryStatement)
    : queryStatement(_queryStatement)
{

}

QString QrSqlQuery::query()
{
    return queryStatement;
}

QrSqlQuery &QrSqlQuery::query(const QString &_queryStatement)
{
    if (_queryStatement.isEmpty ()) {
        Q_ASSERT(false);
    }
    queryStatement = _queryStatement;

    return (*this);
}

QrSqlQuery &QrSqlQuery::bind(const QVariant &value, QSql::ParamType paramType)
{
    verifyQuery ();

    QString name = QString::number (bindValues.count () + 1);
    addBindValue(name, value, paramType);

    return (*this);
}

QrSqlQuery &QrSqlQuery::bind(const QString &name, const QVariant &value, QSql::ParamType paramType)
{
    verifyQuery ();

    if (name.isEmpty ()
            || bindElemNames.contains (name)
            || ! queryStatement.contains (name) ) {
        Q_ASSERT(false);
        return (*this);
    }

    addBindValue(name, value, paramType);

    return (*this);
}

QVariant QrSqlQuery::boundValue(const QString &name) const
{
    if (name.isEmpty ()
            ||  ! bindElemNames.contains (name)) {
        Q_ASSERT(false);
        return QVariant();
    }
    return bindValues[bindElemNames.indexOf (name)].second.first;
}

QVariant QrSqlQuery::boundValue(int position) const
{
    if (position < 0
            || position >= bindElemNames.count ()) {
        Q_ASSERT(false);
        return QVariant();
    }
    return bindValues[position].second.first;
}

void QrSqlQuery::resolve(QSqlQuery &query) const
{
    verifyQuery ();

    bool bindByName = QrSqlConfig::getInstance ()->getPlaceholderStyle ()
            != QrSqlConfig::placeholder_style::ph_style_question_mark;
    QListIterator<BindValue> iter(bindValues);
    while(iter.hasNext ()){
        const BindValue& bindValue = iter.next ();
        const BindElem& bindValueElem = bindValue.second;
        if (bindByName) {
            query.bindValue (bindValue.first, bindValueElem.first, bindValueElem.second);
        } else {
            query.addBindValue (bindValueElem.first, bindValueElem.second);
        }
    }
}

void QrSqlQuery::resolveOutput(QSqlQuery &query, bool _fetchSqlResult)
{
    bool bindByName = QrSqlConfig::getInstance ()->getPlaceholderStyle ()
            != QrSqlConfig::placeholder_style::ph_style_question_mark;
    for (int idx = 0; idx < bindValues.count (); ++idx) {
        BindValue &value = bindValues[idx];
        if (QSql::In == value.second.second) {
            continue;
        }
        //  overwritten with data from the database after the exec() call
        value.second.first = bindByName ? query.boundValue (value.first) : query.boundValue (idx);
    }
    if (_fetchSqlResult) {
        fetchSqlResult(query);
    }
}

long QrSqlQuery::sqlResultRowCount() const
{
    if (sqlResult.isNull ()) {
        return 0;
    }
    return sqlResult.data ()->values.count();
}

long QrSqlQuery::sqlResultColumnCount() const
{
    if (sqlResult.isNull ()) {
        return 0;
    }
    return sqlResult.data ()->positionByColumnName.count();
}

QVariant QrSqlQuery::sqlResultAt(long row, long column) const
{
    if (sqlResult.isNull ()
            ||  row < 0 || row >= sqlResult.data ()->values.count()
            ||  column < 0 || column >= sqlResult.data ()->positionByColumnName.count()) {
        return QVariant();
    }
    return sqlResult.data ()->values.at(row).at(column);
}

QVector<QVariant> QrSqlQuery::sqlResultAt(long row)
{
    if (sqlResult.isNull ()
            || row < 0 || row >= sqlResult.data ()->values.count()) {
        return QVector<QVariant>();
    }
    return sqlResult.data ()->values.at(row);
}

void QrSqlQuery::dumpSqlResult() const
{
    if (sqlResult.isNull ()) {
        return;
    }

    qDebug() << "start dump sql result " << queryStatement;

    QString columns("#");
    Q_FOREACH(QString column, this->columnsOfSqlResult ()){
        columns += "|" + column;
    }
    qDebug() << columns;

    QString output;
    for (long row = 0; row < sqlResult.data ()->values.count(); row++)
    {
       output = QString::number(row);
       for (long col = 0; col < sqlResult.data ()->positionByColumnName.count(); col++)
       {
           output += "|" + sqlResult.data ()->values.at(row).at(col).toString();
       }
       qDebug() << output;
    }
    qDebug() << "end dump sql result";
}

QVector<QString> QrSqlQuery::columnsOfSqlResult() const
{
    if (sqlResult.isNull () ) {
        return QVector<QString>();
    }

    QVector<QString> columns(sqlResult.data ()->positionByColumnName.count());
    QHashIterator<QString, int> iter(sqlResult.data ()->positionByColumnName);
    while(iter.hasNext ()) {
        iter.next ();
        columns[iter.value ()] = iter.key ();
    }
    return columns;
}

bool QrSqlQuery::isEmpty() const
{
    return queryStatement.isEmpty ();
}

void QrSqlQuery::verifyQuery() const
{
    if (! queryStatement.isEmpty ()) {
        return;
    }

    qDebug() << "invalid SQL query";
    Q_ASSERT(false);
}

void QrSqlQuery::fetchSqlResult(QSqlQuery &query)
{
    sqlResult.reset (new QrSqlResult());
    if (query.size () > 0) {
        sqlResult.data ()->values.reserve(query.size ());
    }

    bool check = true;
    while (query.next ()) {
        //  positionByColumnName(columns) of returned sqlresult
        if (check) {
            check = false;
            QSqlRecord record = query.record ();
            sqlResult.data ()->positionByColumnName.reserve(record.count ());
            for (int idx = 0; idx < record.count (); ++idx) {
                sqlResult.data ()->positionByColumnName.insert(record.fieldName (idx), idx);
            }
            Q_ASSERT(record.count () == sqlResult.data ()->positionByColumnName.count());
        }

        //  values of returned sqlresult
        QVector<QVariant> values;
        values.reserve (sqlResult.data ()->positionByColumnName.count());
        for (long idx = 0; idx < sqlResult.data ()->positionByColumnName.count(); ++idx) {
            values.append (query.value (idx));
        }
        Q_ASSERT(values.count () == sqlResult.data ()->positionByColumnName.count());
        sqlResult.data ()->values.append(values);
    }
}

void QrSqlQuery::addBindValue(const QString &name, const QVariant &value, QSql::ParamType paramType)
{
    bindElemNames.push_back (name);
    bindValues.push_back (BindValue(name, BindElem(value, paramType)));
}

const QVector<QVector<QVariant> >& QrSqlQuery::sqlResultValues() const
{
    return sqlResult.data ()->values;
}
