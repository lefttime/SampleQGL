#ifndef LESSON18_GLOBAL_H
#define LESSON18_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON18_LIB
# define LESSON18_EXPORT Q_DECL_EXPORT
#else
# define LESSON18_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON18_GLOBAL_H
