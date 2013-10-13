#ifndef LESSON13_GLOBAL_H
#define LESSON13_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON13_LIB
# define LESSON13_EXPORT Q_DECL_EXPORT
#else
# define LESSON13_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON13_GLOBAL_H
