#ifndef QRDbResultsGuard_INL
#define QRDbResultsGuard_INL

#include <QtCore/qvector.h>
#include <QtCore/qvariant.h>
#include <QtCore/qdebug.h>
#include <QtCore/qmetaobject.h>

#include "entity/qrsqlquery.h"

using namespace Qters::QrOrm;

template <typename CLASS_NAME>
QrDbResultsGuard<CLASS_NAME>::~QrDbResultsGuard(){
    Q_FOREACH(CLASS_NAME * obj, container){
        delete obj;
        obj = nullptr;
    }
}

template <typename CLASS_NAME>
QList<CLASS_NAME *> QrDbResultsGuard<CLASS_NAME>::fetchResultsBySqlQuery(const QrSqlQuery &query){
    QVector<QString> columns = query.columnsOfSqlResult() ;
    const QVector<QVector<QVariant> >& valueses = query.sqlResultValues() ;

    QScopedPointer<CLASS_NAME> tempObj(new CLASS_NAME());
    QList<CLASS_NAME*> results;
    if (valueses.isEmpty () || columns.isEmpty ()) {
        qDebug() << "empty dbset: " << tempObj->metaObject ()->className ();;
        return results;
    }

    QStringList propNames;
    int propCount = tempObj->metaObject ()->propertyCount ();
    for (int propIdx=0; propIdx<propCount; ++propIdx) {
        QMetaProperty metaproperty = tempObj->metaObject ()->property(propIdx);
        const char *name = metaproperty.name();
        propNames.push_back (QString(name));
    }

    Q_FOREACH(QVector<QVariant> values, valueses){
        CLASS_NAME *result = new CLASS_NAME();
        Q_ASSERT(columns.count () == values.count ());

        int colIdx=0;
        for (; colIdx < columns.count (); ++colIdx) {
            setResult(result, columns.at (colIdx), values.at (colIdx), propNames);
        }
        if (columns.count() < values.count()) {
            for (int valIdx = colIdx; valIdx < values.count(); ++valIdx) {
                QString fackColName = QString("unknown%1").arg (valIdx-colIdx+1);
                qDebug() << "unkonwn values: " << values.at (valIdx);
                setResult(result, fackColName, values.at (valIdx), propNames);
            }
        }
        results.push_back (result);
    }
    container.append (results);
    return results;
}

template <typename CLASS_NAME>
void QrDbResultsGuard<CLASS_NAME>::setResult(CLASS_NAME *result, const QString& columnName,
                                             const QVariant& value, const QList<QString>& propNames)
{
    if ( propNames.contains (columnName) ){
        result->setProperty (columnName.toStdString ().c_str (), value);
    }else {
        result->addCustomizedDBVals (columnName.toStdString ().c_str (), value);
    }
}



#endif  //  QRDbResultsGuard_INL
