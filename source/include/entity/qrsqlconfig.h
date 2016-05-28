#ifndef QRSQLCONFIG_H
#define QRSQLCONFIG_H

#include "qrorm_global.h"
#include "singleton/qrsingleton.h"

namespace Qters {

namespace QrOrm {

class QRORMSHARED_EXPORT QrSqlConfig : public QrCommon::QrSingleton<QrOrm::QrSqlConfig> {
    QR_SINGLETON_DEFINE(QrSqlConfig)
public:
    /*!
     * \brief QSqlQuery placeholder style
     *  Qr Orm Library provides 3 styles to write SQL parameters.
     *  This style can be modified for a project using the following method QrSqlDatabase::getInstance()->setSqlPlaceHolderStyle():
     *      ph_style_2_point_name :     "WHERE author.sex = :sex" (default style) ;
     *      ph_style_at_name :          "WHERE author.sex = @sex" ;
     *      ph_style_question_mark :    "WHERE author.sex = ?".
     */
    enum placeholder_style{ ph_style_question_mark, ph_style_2_point_name, ph_style_at_name };

private:
    QrSqlConfig();
    virtual ~QrSqlConfig() = default;

public:
    bool getTraceSqlQuery() ;
    void setTraceSqlQuery(bool value);

    placeholder_style getPlaceholderStyle() ;
    void setPlaceholderStyle(const placeholder_style &value);

private:
    bool traceSqlQuery; //  Trace each sql query executed
    placeholder_style placeholderStyle; //  Place holder style to build sql query
};

}   //  namespace QrOrm

}   //  namespace Qters

#endif // QRSQLCONFIG_H
