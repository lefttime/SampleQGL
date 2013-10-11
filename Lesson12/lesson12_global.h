#ifndef LESSON12_GLOBAL_H
#define LESSON12_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LESSON12_LIB
# define LESSON12_EXPORT Q_DECL_EXPORT
#else
# define LESSON12_EXPORT Q_DECL_IMPORT
#endif

#endif // LESSON12_GLOBAL_H
