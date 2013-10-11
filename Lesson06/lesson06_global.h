#ifndef LESSON06_GLOBAL_H
#define LESSON06_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON06_LIB
# define LESSON06_EXPORT Q_DECL_EXPORT
#else
# define LESSON06_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON06_GLOBAL_H
