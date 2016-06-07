#include "generator/element/qrsqlelement.h"

#include "entity/qrsqlconfig.h"

USING_NS_QRORM;

QrSqlElement::QrSqlElement(int _index) : index(_index) { }

void QrSqlElement::setColumn(const QString & column)
{
   listColumns.clear();
   listColumns.append(column);
   updateKeys();
}

void QrSqlElement::setColumns(const QStringList & columns)
{
   listColumns.clear();
   listColumns = columns;
   updateKeys();
}

void QrSqlElement::setValue(const QVariant & val)
{
   listValues.clear();
   listValues.append(val);
}

void QrSqlElement::setValues(const QVariantList & values)
{
   listValues.clear();
   listValues = values;
}

void QrSqlElement::clone(QrSqlElement * other)
{
   if (! other) { return; }
   listColumns = other->listColumns;
   listValues = other->listValues;
   updateKeys();
}

void QrSqlElement::updateKeys()
{
   listKeys.clear();
   for (int idx = 0; idx < listColumns.count(); idx++)
   {
      QString column = listColumns.at(idx);
      QString key = column.replace(".", "_") + "_" + QString::number(index) + "_" + QString::number(idx);
      if (QrSqlConfig::getInstance ()->getPlaceholderStyle () == QrSqlConfig::ph_style_question_mark) {
          key = "?";
      }else if (QrSqlConfig::getInstance ()->getPlaceholderStyle() == QrSqlConfig::ph_style_at_name) {
          key = QString("@") + key;
      }else {
          key = QString(":") + key;
      }
      listKeys.append(key);
   }
}
