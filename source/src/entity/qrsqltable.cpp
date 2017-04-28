#include "entity/qrsqltable.h"

#include <QtCore/qmetaobject.h>
#include <QtCore/qdebug.h>
#include "generator/qrsqlgenerator.h"

USING_NS_QRORM;

void QrSqlTable::dumpValues() {
    int count = this->metaObject ()->propertyCount ();
    qDebug() << this->metaObject ()->className () << "values : ";
    for (int idx = 0; idx < count; ++idx) {
        QMetaProperty metaproperty = this->metaObject ()->property(idx);
        const char *name = metaproperty.name();
        if (QrSqlGenerator::isFilterProperty(this, QString(name))) {
            continue;
        }
        QVariant value = this->property(name);
        qDebug() << "name:" << name << ", value:" << value;
    }

    const QList<QPair<QString, QVariant> >& customizedVals = this->getCustomizedVals();
    if (customizedVals.isEmpty()) {
        return;
    }
    qDebug() << "customized value : ";
    for (int cusIdx = 0; cusIdx < customizedVals.count (); ++cusIdx) {
        const QPair<QString, QVariant>& customizedVal = customizedVals.at (cusIdx);
        qDebug() << "name:" << customizedVal.first << ", value:" << customizedVal.second.toString();
    }
}

void QrSqlTable::addCustomizedDBVals(const QPair<QString, QVariant> &selfval){
    customizedDbVals.push_back (selfval);
}

void QrSqlTable::addCustomizedDBVals(const QString &selfkey, const QVariant &selfval){
    customizedDbVals.push_back (qMakePair(selfkey, selfval));
}

const QList<QPair<QString, QVariant> >& QrSqlTable::getCustomizedVals() const
{
    return customizedDbVals;
}

long QrSqlTable::getPkId() const
{
    return pk_id;
}

void QrSqlTable::setPkId(long value)
{
    pk_id = value;
}

QString QrSqlTable::pkIdName() const
{
    return "pk_id";
}
