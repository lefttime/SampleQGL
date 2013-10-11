#ifndef LESSON09_GLOBAL_H
#define LESSON09_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON09_LIB
# define LESSON09_EXPORT Q_DECL_EXPORT
#else
# define LESSON09_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON09_GLOBAL_H
