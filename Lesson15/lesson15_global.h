#ifndef LESSON15_GLOBAL_H
#define LESSON15_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON15_LIB
# define LESSON15_EXPORT Q_DECL_EXPORT
#else
# define LESSON15_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON15_GLOBAL_H
