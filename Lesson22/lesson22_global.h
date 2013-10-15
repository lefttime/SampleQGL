#ifndef LESSON22_GLOBAL_H
#define LESSON22_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON22_LIB
# define LESSON22_EXPORT Q_DECL_EXPORT
#else
# define LESSON22_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON22_GLOBAL_H
