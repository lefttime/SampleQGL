#ifndef LESSON23_GLOBAL_H
#define LESSON23_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON23_LIB
# define LESSON23_EXPORT Q_DECL_EXPORT
#else
# define LESSON23_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON23_GLOBAL_H
