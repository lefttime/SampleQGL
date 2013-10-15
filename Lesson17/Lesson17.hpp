#ifndef LESSON17_HPP
#define LESSON17_HPP

#include "lesson17_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON17_EXPORT Lesson17 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson17( QWidget* parent=0 );
  ~Lesson17();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

private:

  class Lesson17Private;
  QScopedPointer<Lesson17Private>         _pd;
};

#endif // LESSON17_HPP