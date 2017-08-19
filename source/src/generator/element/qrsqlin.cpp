#include "generator/element/qrsqlin.h"

#include "entity/qrsqlconfig.h"

USING_NS_QRORM;

QrSqlIn::QrSqlIn()
    : QrSqlElement(0), type(in) {}

QrSqlIn::QrSqlIn(int _index, QrSqlIn::InType _type)
    : QrSqlElement(_index), type(_type){}

QString QrSqlIn::toString() const
{
    Q_ASSERT(1 == listColumns.count() && 1 == listKeys.count() && listValues.count() >= 1);
    QString statement, column(listColumns.at(0)), key(listKeys.at(0));
//    bool questionMark = (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_question_mark);
    Q_ASSERT(! column.isEmpty() && ! key.isEmpty());

    switch (type)
    {
       case in:               statement = column + " IN (";        break;
       case not_in:           statement = column + " NOT IN (";    break;
       case in_select:        statement = column + " IN (";        break;
       case not_in_select:    statement = column + " NOT IN (";    break;
       default:                Q_ASSERT(false);
    }

    for (int i = 0; i < listValues.count(); i++)
    {
        //       if ((type == in_select) || (type == not_in_select)) {
        statement += listValues.at(i).toString() + ",";
//        continue;
        //       }
        //       QString currKey = (questionMark ? QString("?") : (key + QString("_") + QString::number(i)));
        //       statement += ((i == 0) ? QString("") : QString(", "));
        //       statement += currKey;
    }
    statement.chop(1);

    statement += QString(")");
    return statement;
}

