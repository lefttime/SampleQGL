#ifndef LESSON16_GLOBAL_H
#define LESSON16_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON16_LIB
# define LESSON16_EXPORT Q_DECL_EXPORT
#else
# define LESSON16_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON16_GLOBAL_H
