#ifndef LESSON26_GLOBAL_H
#define LESSON26_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON26_LIB
# define LESSON26_EXPORT Q_DECL_EXPORT
#else
# define LESSON26_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON26_GLOBAL_H
