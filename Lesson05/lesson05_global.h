#ifndef LESSON05_GLOBAL_H
#define LESSON05_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON05_LIB
# define LESSON05_EXPORT Q_DECL_EXPORT
#else
# define LESSON05_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON05_GLOBAL_H
