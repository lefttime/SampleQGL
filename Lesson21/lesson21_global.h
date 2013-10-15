#ifndef LESSON21_GLOBAL_H
#define LESSON21_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON21_LIB
# define LESSON21_EXPORT Q_DECL_EXPORT
#else
# define LESSON21_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON21_GLOBAL_H
