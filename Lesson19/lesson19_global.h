#ifndef LESSON19_GLOBAL_H
#define LESSON19_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON19_LIB
# define LESSON19_EXPORT Q_DECL_EXPORT
#else
# define LESSON19_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON19_GLOBAL_H
