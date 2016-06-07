#ifndef QRORM_GLOBAL_H
#define QRORM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRORM_LIBRARY)
#  define QRORMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRORMSHARED_EXPORT Q_DECL_IMPORT
#endif

//  qrorm namespace
#define NS_QRORM_BEGIN \
    namespace Qters { \
    namespace QrOrm {
#define NS_QRORM_END \
    } \
    }
#define USING_NS_QRORM    using namespace Qters::QrOrm
#define NS_QRORM  ::Qters::QrOrm

#endif // QRORM_GLOBAL_H
