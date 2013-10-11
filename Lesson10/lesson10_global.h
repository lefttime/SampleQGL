#ifndef LESSON10_GLOBAL_H
#define LESSON10_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON10_LIB
# define LESSON10_EXPORT Q_DECL_EXPORT
#else
# define LESSON10_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON10_GLOBAL_H
