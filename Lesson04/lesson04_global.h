#ifndef LESSON04_GLOBAL_H
#define LESSON04_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON04_LIB
# define LESSON04_EXPORT Q_DECL_EXPORT
#else
# define LESSON04_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON04_GLOBAL_H
