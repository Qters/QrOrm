#include "generator/element/qrsqlexpression.h"

USING_NS_QRORM;

QrSqlExpression::QrSqlExpression()
    : QrSqlElement(0), type(QrSqlExpression::where) { }

QrSqlExpression::QrSqlExpression(int _index, QrSqlExpression::ExpressionType _type)
    : QrSqlElement(_index), type(_type) { }

QString QrSqlExpression::toString() const
{
    QString statement;

    switch (type) {
    case where: statement = "WHERE"; break;
    case and_:  statement = "AND";   break;
    case or_:   statement = "OR";    break;
    case open_parenthesis:      statement = "(";    break;
    case close_parenthesis:     statement = ")";    break;
    default: Q_ASSERT(false);   break;
    }

    return statement;
}
