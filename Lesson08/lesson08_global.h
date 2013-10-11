#ifndef LESSON08_GLOBAL_H
#define LESSON08_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON08_LIB
# define LESSON08_EXPORT Q_DECL_EXPORT
#else
# define LESSON08_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON08_GLOBAL_H
