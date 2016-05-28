#ifndef QRORM_GLOBAL_H
#define QRORM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRORM_LIBRARY)
#  define QRORMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRORMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QRORM_GLOBAL_H
