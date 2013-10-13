#ifndef LESSON20_GLOBAL_H
#define LESSON20_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON20_LIB
# define LESSON20_EXPORT Q_DECL_EXPORT
#else
# define LESSON20_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON20_GLOBAL_H
