#ifndef LESSON11_GLOBAL_H
#define LESSON11_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON11_LIB
# define LESSON11_EXPORT Q_DECL_EXPORT
#else
# define LESSON11_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON11_GLOBAL_H
