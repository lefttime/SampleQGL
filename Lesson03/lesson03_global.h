#ifndef LESSON03_GLOBAL_H
#define LESSON03_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON03_LIB
# define LESSON03_EXPORT Q_DECL_EXPORT
#else
# define LESSON03_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON03_GLOBAL_H
