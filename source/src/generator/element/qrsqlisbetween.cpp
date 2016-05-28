#include "generator/element/qrsqlisbetween.h"

#include "entity/qrsqlconfig.h"

using namespace Qters::QrOrm;

QrSqlIsBetween::QrSqlIsBetween()
    : QrSqlElement(0), type(is_between) {}

QrSqlIsBetween::QrSqlIsBetween(int _index, QrSqlIsBetween::BetweenType _type)
    : QrSqlElement(_index), type(_type){}

QString QrSqlIsBetween::toString() const
{
    Q_ASSERT((listColumns.count() == 1) && (listKeys.count() == 1));
    QString statement, column(listColumns.at(0)), key(listKeys.at(0));
    Q_ASSERT(! column.isEmpty() && ! key.isEmpty());
    bool bQuestionMark = (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_question_mark);
    QString sKey1(bQuestionMark ? QString("?") : (key + "_1"));
    QString sKey2(bQuestionMark ? QString("?") : (key + "_2"));

    switch (type)
    {
       case is_between:       statement = column + " BETWEEN " + sKey1 + " AND " + sKey2;        break;
       case is_not_between:   statement = column + " NOT BETWEEN " + sKey1 + " AND " + sKey2;    break;
       default:                Q_ASSERT(false);
    }

    return statement;
}

