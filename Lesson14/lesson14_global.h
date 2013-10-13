#ifndef LESSON14_GLOBAL_H
#define LESSON14_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON14_LIB
# define LESSON14_EXPORT Q_DECL_EXPORT
#else
# define LESSON14_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON14_GLOBAL_H
