#ifndef LESSON07_GLOBAL_H
#define LESSON07_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON07_LIB
# define LESSON07_EXPORT Q_DECL_EXPORT
#else
# define LESSON07_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON07_GLOBAL_H
