#ifndef QKIRAUTAUUTILS_GLOBAL_H
#define QKIRAUTAUUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QKIRAUTAUUTILS_LIBRARY)
#  define QKIRAUTAUUTILS_EXPORT Q_DECL_EXPORT
#else
#  define QKIRAUTAUUTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // QKIRAUTAUUTILS_GLOBAL_H