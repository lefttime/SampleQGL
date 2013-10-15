#ifndef LESSON13_HPP
#define LESSON13_HPP

#include "lesson13_global.h"
#include "../GuiLib/GLWidget.hpp"

class LESSON13_EXPORT Lesson13 : public GLWidget
{
  Q_OBJECT;

public:

  Lesson13( QWidget* parent=0 );
  ~Lesson13();

protected:

  void initializeGL();
  void paintGL();

  void idleFunc();

private:

  class Lesson13Private;
  QScopedPointer<Lesson13Private>         _pd;
};

#endif // LESSON13_HPP