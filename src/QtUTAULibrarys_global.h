#ifndef QTUTAULIBRARYS_GLOBAL_H
#define QTUTAULIBRARYS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTUTAULIBRARYS_LIBRARY)
#  define QTUTAULIBRARYS_EXPORT Q_DECL_EXPORT
#else
#  define QTUTAULIBRARYS_EXPORT Q_DECL_IMPORT
#endif

#endif // QTUTAULIBRARYS_GLOBAL_H
