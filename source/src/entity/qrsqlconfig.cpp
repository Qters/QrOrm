#include "entity/qrsqlconfig.h"


using namespace Qters::QrOrm;

QR_SINGLETON_IMPLEMENT(QrSqlConfig)

QrSqlConfig::QrSqlConfig()
    : Qters::QrCommon::QrSingleton<QrSqlConfig>("qrsqlconfig")
{
#ifdef QT_DEBUG
    setTraceSqlQuery(true);
#else
    setTraceSqlQuery(false);
#endif
}

QrSqlConfig::placeholder_style QrSqlConfig::getPlaceholderStyle()
{
    return placeholderStyle;
}

void QrSqlConfig::setPlaceholderStyle(const placeholder_style &value)
{
    placeholderStyle = value;
}

bool QrSqlConfig::getTraceSqlQuery()
{
    return traceSqlQuery;
}

void QrSqlConfig::setTraceSqlQuery(bool value)
{
    traceSqlQuery = value;
}
