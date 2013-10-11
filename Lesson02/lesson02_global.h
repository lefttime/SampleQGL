#ifndef LESSON02_GLOBAL_H
#define LESSON02_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON02_LIB
# define LESSON02_EXPORT Q_DECL_EXPORT
#else
# define LESSON02_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON02_GLOBAL_H
