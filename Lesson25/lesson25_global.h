#ifndef LESSON25_GLOBAL_H
#define LESSON25_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON25_LIB
# define LESSON25_EXPORT Q_DECL_EXPORT
#else
# define LESSON25_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON25_GLOBAL_H
