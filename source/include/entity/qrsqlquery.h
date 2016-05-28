#ifndef QRSQLQUERY_H
#define QRSQLQUERY_H

#include <Qtcore/qvariant.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qmap.h>
#include <QtCore/qsharedpointer.h>
#include <QtSql/qsqldatabase.h>

#include "qrorm_global.h"


namespace Qters {

namespace QrOrm {

/*!
 * \brief define a user SQL query added to default SQL query builded
 */
/*!
 * Here is an example with <i>qx::QxSqlQuery</i> class writing manually a SQL query :
 * Build a SQL query to fetch only 'author' of type 'female'
 *      QrSqlQuery query("WHERE author.sex = :sex");
 *      query.bind(":sex", author::female);
 *      QSqlError daoError = call_query(query);
 *      query.dumpSqlResult();
 *
 * If the stored procedure returns a resultset, you can iterate over
 * each rows and fields using the following methods (after calling call_query()function) :
 *      long sqlResultRowCount() const;
 *      long sqlResultColumnCount() const;
 *      QVariant sqlResultAt(long row, long column) const;
 *      QVector<QVariant> sqlResultAt (long row);
 *      QVector<QString> columnsOfSqlResult() const;
 *      const QVector<QVector<QVariant> >& sqlResultValues() const;
 *      void dumpSqlResult() const;
 *
 */
class QRORMSHARED_EXPORT QrSqlQuery
{
public:
    QrSqlQuery(const QString& _queryStatement);

protected:
    /*!
     * \brief Type of Sql Result.
     */
    struct QrSqlResult{
        QHash<QString, int> positionByColumnName;
        QVector< QVector<QVariant> > values;
    };

private:
    /*!
     * \brief Type of bind value
     */
    typedef QPair<QVariant, QSql::ParamType> BindElem;
    typedef QString BindElemName;
    typedef QPair< BindElemName, BindElem > BindValue;
    typedef QList< BindValue > BindValues;

public:
    QString query();
    QrSqlQuery& query(const QString& _queryStatement);

    /*!
     * \brief Add a placeholder to be bound to value in the sql statement.
     *
     *  To get an output value parameter (must be pass as QSql::Out or QSql::InOut)
     *  returned by a stored procedure, just call the following method :
     *  QVariant QrSqlQuery::boundValue(const QString & sKey) const
     */
    QrSqlQuery& bind(const QVariant& value, QSql::ParamType paramType = QSql::In);
    QrSqlQuery& bind(const QString& name, const QVariant& value, QSql::ParamType paramType = QSql::In);

    /*!
     * \brief Returns the value for the placeholder.
     */
    QVariant boundValue(const QString & name) const;
    QVariant boundValue(int position) const;

    /*!
     * \brief Set the placeholder placeholder to be bound to value val in the sql statement.
     */
    void resolve(QSqlQuery & query) const;
    /*!
     * \brief Parse the returned value for the placeholders
     */
    void resolveOutput(QSqlQuery & query, bool _fetchSqlResult);

    /*!
     * \brief To iterate over all resultset
     */
    long sqlResultRowCount() const;
    long sqlResultColumnCount() const;
    QVariant sqlResultAt(long row, long column) const;
    QVector<QVariant> sqlResultAt (long row);
    QVector<QString> columnsOfSqlResult() const;
    const QVector<QVector<QVariant> >& sqlResultValues() const;
    void dumpSqlResult() const;


private:
    bool isEmpty() const;
    void verifyQuery() const;
    void fetchSqlResult(QSqlQuery & query);
    void addBindValue(const QString &name, const QVariant &value, QSql::ParamType paramType);


protected:
    QString queryStatement; //  query SQL with place-holder
    BindValues bindValues;  //  bind value in this array
    QSharedPointer<QrSqlResult> sqlResult;  //  all results returned

private:
    QList<BindElemName>  bindElemNames;

};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLQUERY_H
