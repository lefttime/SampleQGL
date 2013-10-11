#ifndef LESSON01_GLOBAL_H
#define LESSON01_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON01_LIB
# define LESSON01_EXPORT Q_DECL_EXPORT
#else
# define LESSON01_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON01_GLOBAL_H
