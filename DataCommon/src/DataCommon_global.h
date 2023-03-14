#ifndef DATACOMMON_GLOBAL_H
#define DATACOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATACOMMON_LIBRARY)
#  define DATACOMMON_EXPORT Q_DECL_EXPORT
#else
#  define DATACOMMON_EXPORT Q_DECL_IMPORT
#endif

#endif // DATACOMMON_GLOBAL_H
