#ifndef LESSON24_GLOBAL_H
#define LESSON24_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON24_LIB
# define LESSON24_EXPORT Q_DECL_EXPORT
#else
# define LESSON24_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON24_GLOBAL_H
