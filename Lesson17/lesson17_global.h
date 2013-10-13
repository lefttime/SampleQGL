#ifndef LESSON17_GLOBAL_H
#define LESSON17_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON17_LIB
# define LESSON17_EXPORT Q_DECL_EXPORT
#else
# define LESSON17_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON17_GLOBAL_H
